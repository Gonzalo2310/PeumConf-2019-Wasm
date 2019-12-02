# WebAssembly básico con C / C++

## Arrays

Este es un ejemplo complejo que asignación de memoria al estilo de C pero en el uso de JS. Es un ejemplo tomado de la web: https://medium.com/@tdeniffel/c-to-webassembly-pass-and-arrays-to-c-86e0cb0464f5 ya que mi conocimiento de C no era tan amplio como para desarrollar este ejemplo por mi mismo.

Explicación de código: C / C++

Las función main y el uso de Extern "C" se explican en el ejemplo de Parámetros

```c
float sum_up(float *vals, int size) {
    float res = 0;
    for (int i = 0; i < size; i++)
        res += vals[i];
    return res;
}
```

Esta es una función sencilla que lo único que hace es sumar los valores de un array y devolver el total de la suma. Se esta asumiendo que todos los valores son floats. Los diferentes controles de tipo de contenido y demás es posible pero la idea se que este código sea lo mas sencillo sobre todo por la complejidad en js que este ejemplo conlleva.



Código Js: 

```javascript
function toFloatArr(arr) {
    const res = new Float32Array(arr.length)
    for (let i=0; i < arr.length; i++)
      res[i] = arr[i]
    return res
  }
  function transferToHeap(arr) {
    const floatArray = toFloatArr(arr)
    const heapSpace = Module._malloc(floatArray.length *
      floatArray.BYTES_PER_ELEMENT)
    Module.HEAPF32.set(floatArray, heapSpace >> 2)
    return heapSpace
  }
  function sumUp(arr) {
    let arrayOnHeap
    try {
      arrayOnHeap = transferToHeap(arr)
      return Module._sum_up(arrayOnHeap, arr.length)
    } finally {
      Module._free(arrayOnHeap)
    }
  }
  function allReady() {
    console.log(
      sumUp([1.0, 2.0, 3.0, 4.0, 5.0, 6.0])
    );
  }
```

La primer función (toFloatArr) recibe un array js y lo convierte con [Float32Array](https://developer.mozilla.org/es/docs/Web/JavaScript/Reference/Global_Objects/Float32Array) en un array de punteros Float de 32 bits y nos devuelve el resultado.

La segunda función (transferToHeap) recibe un array js. Usa la función anterior para obtener los punteros, reserva memoria ram usando el malloc de C, copia el contenido del array en ese espacio y devuelve el resultado.

La tercera función (sumUp) recibe un array js, obtiene el espacio en memoria con la función anterior y devuelve el resultado de nuestra función desarrollada en C enviado los datos en memoria y el tamaño del array. Devuelve el resultado y libera la memoria asignada (usando free de C)

allReady (explicado en el ejemplo de Parámetros) usa la función sumUp pasando un array js con valores float y mostrando el resultado devuelto en consola. En este caso la suma da 21.

Linea de compilación:

```bash
emcc main.cpp -o index.js -s EXPORTED_FUNCTIONS=['_main','_sum_up','_free','_malloc'] -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']  -s WASM=1 -Oz
```

La explicación de lo mas básico de los parámetros de emcc se explican en el ejemplo Parámetros.

Aquí se esta exportando explícitamente dos funciones de C que no usamos en el código de dicho lenguaje: malloc y free. Estas funciones sirven para reservar memoria y liberarla cuando ya no se usa.

Los demás puntos están explicados.

