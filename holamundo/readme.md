# WebAssembly básico con C / C++ 

## Hola Mundo

Este ejemplo es super básico: 

Solo hay una linea de código (y el return) que muestra un mensaje de salida.

El mensaje se muestra en la consola para lo cual no es necesario escribir ni una sola linea de js. 

Código C:

```c
int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

Linea de compilación: 

```bash
emcc main.cpp -o index.js -s WASM=1
```

