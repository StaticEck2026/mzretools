@echo off
rem Rebuild the ROM with SNASM68K (SN Systems).  asm68k.exe takes the same
rem command line.  Produces nhl98.bin, nhl98.sym (symbols) and nhl98.lst
rem (listing).  "-o ae-" disables automatic alignment so that the data
rem directives reproduce the original layout exactly.
snasm68k.exe -e -o ae- nhl98.asm, nhl98.bin, nhl98.sym, nhl98.lst
if errorlevel 1 goto :fail
if "%1"=="" goto :eof
fc /b "%1" nhl98.bin
goto :eof
:fail
echo assembly failed
