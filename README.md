# Hanoi Web — quick run & build notes

This folder contains a small Tower of Hanoi demo with a WASM backend (optional) and a simple frontend.

Quick run (recommended)
- Start a simple static server and open the page. Example using Python (port 8000):

  ```powershell
  cd 'c:\Users\deepa\Desktop\GAURI\gitdemo\DSAmini\hanoi_web'
  python -m http.server 8000
  # then open http://localhost:8000/front.html?n=4 in your browser
  ```

- If you prefer a convenience script that regenerates `moves.json`, starts a server and opens the page, you may have an older `run_all.cmd` in this folder. Note that some of the helper scripts were removed in the "minimal deploy" cleanup — see the Tidying section.

What the page does
- `front.html` tries to load the prebuilt WASM module (`hanoi.js` / `hanoi.wasm`) and call the compiled C functions (from `algo.c`) to compute the moves at runtime.
- If the WASM module is missing or fails, the page falls back to using `moves.json` (precomputed moves) and animates those moves.
- You can pass `?n=<N>` in the URL to choose the number of disks (e.g. `front.html?n=5`).

Regenerate `moves.json` manually
- Using the compiled generator (fast):
  ```powershell
  cd 'c:\Users\deepa\Desktop\GAURI\gitdemo\DSAmini\hanoi_web'
  .\generate_moves.exe 5   # generates moves.json for n=5
  ```

- Or compile & run the C source (if you changed it):
  ```powershell
  gcc generate_moves.c -O2 -o generate_moves.exe
  .\generate_moves.exe 6
  ```

Rebuild the WASM (only if you want to recompile `hanoi.c`)
- This project may include a local `emsdk/`. I added `build_wasm.cmd` to make rebuilding on Windows easier — it calls the local `emsdk\emsdk_env.bat` if present and then runs `emcc`.
- Recommended: run the batch (it uses the emsdk environment and `emcc`):
  ```powershell
  cd 'c:\Users\deepa\Desktop\GAURI\gitdemo\DSAmini\hanoi_web'
  cmd /c build_wasm.cmd
  ```

Notes:
- If `emsdk/` is not present, add emscripten to your PATH and the script will still attempt to run `emcc`.
- PowerShell execution policy may block emsdk PowerShell scripts. Running the CMD batch avoids that. Alternatively you can temporarily bypass policy for the session:
  ```powershell
  Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass -Force
  ```

Notes & troubleshooting
- If the browser shows errors related to loading `hanoi.wasm` make sure you're serving files over HTTP (the local server started by `run_all.cmd` does this). Opening `front.html` via `file://` will often break wasm or fetch.
- PowerShell execution policy may block the emsdk PowerShell scripts (you can either run `build_wasm.cmd` with `cmd /c` or temporarily bypass the policy for the session: `Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass -Force`).
- If the page complains that no WASM and no `moves.json` were found, ensure the server is running and `moves.json` exists in this folder.

Tidying & deployment
- Minimal files required to deploy the demo (static host): `front.html`, `hanoi.js`, `hanoi.wasm` and optionally `moves.json`.
- If you do not plan to rebuild WASM locally, you can remove the `emsdk/` folder to shrink the repo.

If you want I can add a small README section explaining how to add a client-side JS generator so no backend/executable is needed — say the word and I’ll add it.

Note: I saw `moves.json` was modified manually after the last generator run; if you rely on a generated `moves.json`, regenerate it using `hanoi.exe` or `build_wasm.cmd` + the WASM path.
