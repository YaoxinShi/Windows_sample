@echo off

@rem firstly run mouse.exe to get your target mouse position, e.g. <200,100>
@rem then run below bat

set index=0
:LOOP
set /a index=%index%+1
echo ===================== %index% ======================
timeout 5
mouse.exe 200 100
goto LOOP
