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
--
##Compile C to WASM

emcc hanoi.c -o hanoi.js -s EXPORTED_FUNCTIONS='["_run_hanoi","_get_move_from","_get_move_to"]' -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]'
