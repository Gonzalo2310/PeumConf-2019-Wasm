#include <emscripten/emscripten.h>


int main() {
    emscripten_run_script( "allReady()" );
    return 1;
}

extern "C" {

int limits(int js_number) {
    return js_number > 100 ? js_number - 100 : js_number;
}

}

// emcc main.cpp -o index.js -s EXPORTED_FUNCTIONS=['_main','_limits'] -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] -Oz -s WASM=1
