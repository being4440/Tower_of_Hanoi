@echo off
REM run_all.cmd - regenerate moves.json, start a static server, and open front.html
REM Usage: run_all.cmd [N]

setlocal
set "N=%~1"
if "%N%"=="" set "N=4"

pushd %~dp0

echo Regenerating moves.json for n=%N%...
if exist hanoi.exe (
  echo Found hanoi.exe, running generator...
  .\hanoi.exe %N%
) else (
  echo hanoi.exe not found. Attempting to build native generator with gcc...
  where gcc >nul 2>nul
  if errorlevel 1 (
    echo gcc not found; skipping native generator. If you want moves.json generated, install gcc or build hanoi.exe manually.
  ) else (
    gcc hanoi.c -O2 -o hanoi.exe && .\hanoi.exe %N%
  )
)

echo Starting static HTTP server on port 8000 (new window)...
start "HanoiServer" cmd /k "cd /d %~dp0 && python -m http.server 8000"

echo Opening browser at http://127.0.0.1:8000/front.html?n=%N%
start "" "http://127.0.0.1:8000/front.html?n=%N%"

popd
endlocal
exit /b 0
