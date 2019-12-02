#include <iostream>

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}

// emcc main.cpp -o index.js -s WASM=1