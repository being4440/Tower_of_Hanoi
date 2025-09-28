# Tower of Hanoi Web Visualizer

**Description:**  
This project implements the **Tower of Hanoi** algorithm in **C** (recursive, using data structures) and visualizes it in a browser using **WebAssembly (WASM)** with **HTML/JS**.  
Users can watch disks move between pegs step by step with smooth animations.
 --
## Features
- Recursive Tower of Hanoi algorithm implemented in **C**
- WebAssembly integration (`hanoi.wasm` + `hanoi.js`) for browser execution
- Interactive HTML/JS visualization with animated disks
- Adjustable number of disks
- Shows move-by-move solution

---

## Prerequisites
1. **C Compiler** (GCC / Clang)  
2. **Emscripten SDK** (for compiling C to WASM)  
   - [Install instructions](https://emscripten.org/docs/getting_started/downloads.html)  
3. **Python 3** (for running a local HTTP server)  
4. Web Browser (Chrome / Edge / Firefox)

---

## Setup Instructions

### 1. Install Emscripten
```bat
cd path\to\emsdk
emsdk install latest
emsdk activate latest
emsdk_env.bat
 ```
##Compile C to WASM
```bat
emcc hanoi.c -o hanoi.js -s EXPORTED_FUNCTIONS='["_run_hanoi","_get_move_from","_get_move_to"]' -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]
 ```

### 1. Install Emscripten

python -m http.server 8080

4. Open in Browser
Visit:
http://localhost:8080/front.html?n=4

n is the number of disks (adjustable)

Folder Structure
 ```
hanoi_web/
├─ hanoi.c           # C implementation of Tower of Hanoi
├─ hanoi.js          # WASM JS glue file
├─ hanoi.wasm        # Compiled WebAssembly module
├─ front.html        # HTML frontend with inline styles
├─ emsdk/            # Emscripten SDK (optional, for building WASM)
├─ build_wasm.cmd    # Optional build script
└─ run_all.cmd       # Optional run script
 ```

How it Works

C Logic: Calculates the sequence of moves recursively.
WebAssembly: Converts C code to browser-compatible module.
Frontend: Animates disks according to the move sequence using JavaScript and inline CSS.

Notes

Demonstrates data structures (stack, recursion) in C.
HTML/JS is used only for visualization; the algorithm is entirely in C.
Works on any modern browser with WASM support.

working  video 
https://drive.google.com/file/d/1eux7ZdM0QdmmR6MYU6CcdOu_XOoIwtPE/view?usp=sharing
