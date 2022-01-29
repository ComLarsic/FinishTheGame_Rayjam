#!/bin/bash
emcmake cmake -B web_build -S . -DPLATFORM=Web
cmake --build web_build
cp web_build/RayJam.js bin/RayJam.js
cp web_build/RayJam.wasm bin/RayJam.wasm
cp web_build/RayJam.data bin/RayJam.data
cp web_build/RayJam.wasm bin/RayJam.wasm