// Ghidra headless post-script for executables disassembled with ledisasm.py.
//
// It imports the routine/variable names and calling conventions found by ledisasm (the .sym file),
// teaches Ghidra the Watcom register calling convention (__watcall: eax, edx, ebx, ecx, then stack,
// callee cleans the stack), and writes the decompiler output of every routine to C files.
//
// Usage (see tools/lede.sh for a wrapper):
//   analyzeHeadless <projdir> <projname> -import program.elf -scriptPath tools/ghidra \
//       -postScript LEDecompile.java <outdir> <program.sym> [split_bytes] -deleteProject
//
// Output: <outdir>/decomp_<addr>.c files, each covering roughly split_bytes of code (default 0x8000),
// plus <outdir>/prototypes.h with the signatures recovered by the decompiler.
//
//@category mzretools
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.database.SpecExtension;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class LEDecompile extends GhidraScript {

    static final String WATCALL =
        "<prototype name=\"__watcall\" extrapop=\"unknown\" stackshift=\"4\">\n" +
        "  <input>\n" +
        "    <pentry minsize=\"1\" maxsize=\"4\"><register name=\"EAX\"/></pentry>\n" +
        "    <pentry minsize=\"1\" maxsize=\"4\"><register name=\"EDX\"/></pentry>\n" +
        "    <pentry minsize=\"1\" maxsize=\"4\"><register name=\"EBX\"/></pentry>\n" +
        "    <pentry minsize=\"1\" maxsize=\"4\"><register name=\"ECX\"/></pentry>\n" +
        "    <pentry minsize=\"1\" maxsize=\"500\" align=\"4\"><addr offset=\"4\" space=\"stack\"/></pentry>\n" +
        "  </input>\n" +
        "  <output>\n" +
        "    <pentry minsize=\"4\" maxsize=\"10\" metatype=\"float\"><register name=\"ST0\"/></pentry>\n" +
        "    <pentry minsize=\"1\" maxsize=\"4\"><register name=\"EAX\"/></pentry>\n" +
        "    <pentry minsize=\"5\" maxsize=\"8\"><addr space=\"join\" piece1=\"EDX\" piece2=\"EAX\"/></pentry>\n" +
        "  </output>\n" +
        "  <unaffected>\n" +
        "    <register name=\"ESP\"/><register name=\"EBP\"/><register name=\"ESI\"/><register name=\"EDI\"/>\n" +
        "    <register name=\"EBX\"/><register name=\"ECX\"/><register name=\"EDX\"/>\n" +
        "    <register name=\"DF\"/>\n" +
        "  </unaffected>\n" +
        "  <killedbycall><register name=\"EAX\"/></killedbycall>\n" +
        "</prototype>\n";

    // for assembly helpers which take arguments on the stack, remove them and preserve all registers,
    // like the Watcom stack check routine __CHK (push framesize; call __CHK)
    static final String REGSAFE =
        "<prototype name=\"__regsafe\" extrapop=\"unknown\" stackshift=\"4\">\n" +
        "  <input>\n" +
        "    <pentry minsize=\"1\" maxsize=\"500\" align=\"4\"><addr offset=\"4\" space=\"stack\"/></pentry>\n" +
        "  </input>\n" +
        "  <output>\n" +
        "    <pentry minsize=\"1\" maxsize=\"4\"><register name=\"EAX\"/></pentry>\n" +
        "  </output>\n" +
        "  <unaffected>\n" +
        "    <register name=\"ESP\"/><register name=\"EBP\"/><register name=\"ESI\"/><register name=\"EDI\"/>\n" +
        "    <register name=\"EBX\"/><register name=\"ECX\"/><register name=\"EDX\"/><register name=\"EAX\"/>\n" +
        "    <register name=\"DF\"/>\n" +
        "  </unaffected>\n" +
        "</prototype>\n";

    static class Sym {
        long addr; String kind; String name; long size; String extra; boolean noreturn;
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            printerr("usage: LEDecompile.java <outdir> <symbols.sym> [split_bytes]");
            return;
        }
        File outDir = new File(args[0]);
        outDir.mkdirs();
        long split = args.length > 2 ? Long.decode(args[2]) : 0x8000;

        // register the Watcom calling conventions with this program
        try {
            SpecExtension ext = new SpecExtension(currentProgram);
            ext.addReplaceCompilerSpecExtension(WATCALL, monitor);
            ext.addReplaceCompilerSpecExtension(REGSAFE, monitor);
            println("Added __watcall and __regsafe prototypes");
        } catch (Exception e) {
            printerr("Unable to add __watcall prototype: " + e);
        }

        List<Sym> syms = readSymbols(new File(args[1]));
        FunctionManager fm = currentProgram.getFunctionManager();
        SymbolTable st = currentProgram.getSymbolTable();
        int created = 0, renamed = 0, conv = 0;
        for (Sym s : syms) {
            Address a = toAddr(s.addr);
            if (s.kind.equals("func")) {
                Function f = fm.getFunctionAt(a);
                if (f == null) {
                    disassemble(a);
                    f = createFunction(a, s.name);
                    if (f == null) continue;
                    created++;
                }
                if (!f.getName().equals(s.name)) {
                    f.setName(s.name, SourceType.USER_DEFINED);
                    renamed++;
                }
                if (s.extra != null && !s.extra.isEmpty()) {
                    try {
                        f.setCallingConvention(s.extra);
                        if (s.extra.equals("__regsafe")) {
                            // returns nothing, so the value of eax survives the call in the caller
                            f.setReturnType(ghidra.program.model.data.VoidDataType.dataType, SourceType.USER_DEFINED);
                            f.setSignatureSource(SourceType.USER_DEFINED);
                        }
                        conv++;
                    } catch (Exception e) {
                        printerr("calling convention " + s.extra + " at " + a + ": " + e.getMessage());
                    }
                }
                if (s.noreturn) f.setNoReturn(true);
            } else {
                Symbol prim = st.getPrimarySymbol(a);
                if (prim == null || !prim.getName().equals(s.name)) {
                    try {
                        createLabel(a, s.name, true, SourceType.USER_DEFINED);
                    } catch (Exception e) {
                        // name clash, ignore
                    }
                }
            }
        }
        println(String.format("Functions: %d created, %d renamed, %d conventions set", created, renamed, conv));

        DecompInterface di = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        di.setOptions(opts);
        di.toggleCCode(true);
        di.toggleSyntaxTree(false);
        di.setSimplificationStyle("decompile");
        if (!di.openProgram(currentProgram)) {
            printerr("Decompiler failed to open program: " + di.getLastMessage());
            return;
        }

        Map<Long, Sym> byAddr = new HashMap<>();
        for (Sym s : syms) if (s.kind.equals("func")) byAddr.put(s.addr, s);

        PrintWriter types = new PrintWriter(new File(outDir, "ghidra_types.h"));
        types.println("// Basic types used by the Ghidra decompiler output");
        types.println("#pragma once");
        types.println("typedef unsigned char undefined; typedef unsigned char undefined1; typedef unsigned short undefined2;");
        types.println("typedef unsigned int undefined3; typedef unsigned int undefined4; typedef unsigned long long undefined6;");
        types.println("typedef unsigned long long undefined8; typedef unsigned char byte; typedef unsigned short ushort;");
        types.println("typedef unsigned int uint; typedef unsigned int uint3; typedef unsigned long long ulonglong;");
        types.println("typedef long long longlong; typedef unsigned char uchar; typedef int int3; typedef void code;");
        types.println("typedef unsigned char bool; typedef unsigned short word; typedef unsigned int dword;");
        types.println("#define __watcall  /* Watcom register calling convention: eax, edx, ebx, ecx, stack */");
        types.println("#define __regsafe  /* stack arguments, all registers preserved */");
        types.close();

        PrintWriter out = null;
        PrintWriter protos = new PrintWriter(new File(outDir, "prototypes.h"));
        protos.println("// Function prototypes recovered by the Ghidra decompiler from " + currentProgram.getName());
        protos.println("// __watcall: Watcom register convention, arguments in eax, edx, ebx, ecx, then stack");
        protos.println("#pragma once");
        protos.println("#include \"ghidra_types.h\"");
        protos.println();
        long chunkStart = -1;
        int done = 0, failed = 0;
        int total = fm.getFunctionCount();
        for (Function f : fm.getFunctions(true)) {
            if (monitor.isCancelled()) break;
            long entry = f.getEntryPoint().getOffset();
            if (out == null || entry - chunkStart >= split) {
                if (out != null) out.close();
                chunkStart = entry;
                out = new PrintWriter(new File(outDir, String.format("decomp_%06x.c", entry)));
                out.println("// Decompiled by Ghidra from " + currentProgram.getName() + " (via ledisasm ELF export)");
                out.println("// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.");
                out.println("#include \"prototypes.h\"");
                out.println();
            }
            Sym s = byAddr.get(entry);
            out.println("// " + "=".repeat(96));
            out.println(String.format("// %s @ 0x%x%s%s", f.getName(), entry,
                s != null ? " [" + s.extra + "]" : "", f.hasNoReturn() ? " noreturn" : ""));
            out.println("// " + "=".repeat(96));
            DecompileResults res = di.decompileFunction(f, 120, monitor);
            if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) {
                out.println(res.getDecompiledFunction().getC());
                String sig = res.getDecompiledFunction().getSignature();
                if (sig != null) protos.println(sig.trim() + (sig.trim().endsWith(";") ? "" : ";"));
            } else {
                failed++;
                out.println("// decompilation failed: " + (res != null ? res.getErrorMessage() : "null result"));
                out.println();
            }
            done++;
            if (done % 100 == 0) println(String.format("Decompiled %d/%d functions (%d failed)", done, total, failed));
        }
        if (out != null) out.close();
        protos.close();
        di.dispose();
        println(String.format("Decompiled %d functions, %d failed, output in %s", done, failed, outDir));
    }

    List<Sym> readSymbols(File f) throws Exception {
        List<Sym> list = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(f))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.isEmpty() || line.startsWith("#")) continue;
                String[] p = line.split("\t");
                if (p.length < 4) continue;
                Sym s = new Sym();
                s.addr = Long.parseLong(p[0], 16);
                s.kind = p[1];
                s.name = p[2];
                s.size = Long.parseLong(p[3]);
                s.extra = p.length > 4 ? p[4] : "";
                s.noreturn = p.length > 5 && p[5].equals("noreturn");
                list.add(s);
            }
        }
        return list;
    }
}
