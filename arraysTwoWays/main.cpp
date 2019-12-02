#include <emscripten/emscripten.h>
#include <cstdlib>

int main() {
    emscripten_run_script( "allReady()" );
    return 1;
}
int intcmp(const void *aa, const void *bb)
{
    const int *a = (int *)aa, *b = (int *)bb;
    return (*a < *b) ? -1 : (*a > *b);
}
extern "C" {
int squareInt(int *arr, int length) {
    for (int i = 0; i <  length; i++) {
        arr[i] = arr[i] * arr[i];
    }
    return 0;
}

int order_ascending(int *arr, int length) {
    qsort(arr, length, sizeof(int), intcmp);
    return 0;
}

}

/**
 emcc main.cpp -o index.js -s EXPORTED_FUNCTIONS=['_main','_squareInt','_order_ascending','_free','_malloc'] -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']  -s WASM=1 -Oz
**/
