#include <emscripten/emscripten.h>


int main() {
    emscripten_run_script( "allReady()" );
    return 1;
}

extern "C" {

float sum_up(float *vals, int size) {
    float res = 0;
    for (int i = 0; i < size; i++)
        res += vals[i];
    return res;
}
}

/**
emcc main.cpp -o index.js -s EXPORTED_FUNCTIONS=['_main','_sum_up','_free','_malloc'] -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']  -s WASM=1 -Oz
**/
