@echo on
setlocal EnableDelayedExpansion
REM (debug mode: echoing commands to help locate parsing error)
REM build_wasm.cmd
REM Clean build script: build hanoi.c -> hanoi.js + hanoi.wasm using local emsdk or emcc on PATH.

REM Move to script directory
pushd %~dp0

REM Prefer using a local emsdk if present, otherwise try global C:\emsdk
set EMSDK_QUIET=1
if exist "emsdk\emsdk_env.bat" (
  call "emsdk\emsdk_env.bat"
) else if exist "C:\emsdk\emsdk_env.bat" (
  call "C:\emsdk\emsdk_env.bat"
) else (
  REM no emsdk initializer found; we'll try to use emcc from PATH
  echo Note: no emsdk initializer found locally or at C:\emsdk. Will try emcc from PATH.
)

REM Verify emcc is available now
where emcc >nul 2>nul
if errorlevel 1 (
  echo ERROR: emcc not found on PATH. Please run emsdk_env.bat (local or C:\emsdk) or add emcc to PATH.
  popd
  exit /b 1
)

echo emcc available:
emcc --version
echo Building hanoi.c -> hanoi.js/hanoi.wasm

emcc "hanoi.c" -O2 -s WASM=1 -s EXPORTED_FUNCTIONS="['_run_hanoi','_get_move_from','_get_move_to']" -s EXPORTED_RUNTIME_METHODS="['cwrap']" -o "hanoi.js"

if errorlevel 1 (
  echo Build failed with error %errorlevel%.
  popd
  exit /b %errorlevel%
)

echo Build succeeded. Files: hanoi.js hanoi.wasm
popd
exit /b 0
