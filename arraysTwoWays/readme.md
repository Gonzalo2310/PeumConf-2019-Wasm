# WebAssembly básico con C / C++ 

## Arrays de doble camino

En este ejemplo trabajaremos con arrays que son modificados por js y por C alternativamente. Enviaremos y recibiremos datos que podremos manipular. El código original se puede encontrar aquí: https://medium.com/@tdeniffel/c-to-webassembly-pass-and-arrays-to-c-86e0cb0464f5

Explicación de código en C 

Función no exportada:

```c
int intcmp(const void *aa, const void *bb)
{
    const int *a = (int *)aa, *b = (int *)bb;
    return (*a < *b) ? -1 : (*a > *b);
}
```

Simplemente es para ordenar de mayor a menor un array de valores enteros, y no se exporta porque es usada internamente por otra función que si se exporta.

Funciones exportadas:

```c
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
```

La primer función sobrescribe los valores del array recibido cambiado por sus valores al cuadrado.

La segunda función usa `qsort`y la función no exportada para ordenar de mayor a menor los valores del array

Código en JS

```javascript
const list_number = Array(1000000)
  let time = new Date();
  for(i=0; i < list_number.length; i++) {
    list_number[i] =getRandomInt(0, 100000)
  }
  function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min)) + min;
  }
  function _arrayToHeap(typedArray){
    const numBytes = typedArray.length * typedArray.BYTES_PER_ELEMENT;
    const ptr = Module._malloc(numBytes);
    const heapBytes = new Uint8Array(Module.HEAPU8.buffer, ptr, numBytes);
    heapBytes.set(new Uint8Array(typedArray.buffer));
    return heapBytes;
  }

  function _freeArray(heapBytes){
    Module._free(heapBytes.byteOffset);
  }

  const square = function(arr){
    const heapBytes = _arrayToHeap(arr);
    time = new Date();
    console.log(time.getHours() + ":" + time.getMinutes() + ":" + time.getSeconds() + ':' + time.getMilliseconds());
    Module.ccall('squareInt', 'null',['number','number'], [heapBytes.byteOffset, arr.length]);
    const res = new arr.constructor(heapBytes.buffer, heapBytes.byteOffset, arr.length);
    _freeArray(heapBytes);
    return res;
  };

  const ascending = function(arr) {
    const heapBytes = _arrayToHeap(arr);
    Module.ccall('order_ascending', 'null',['number','number'], [heapBytes.byteOffset, arr.length]);
    const res = new arr.constructor(heapBytes.buffer, heapBytes.byteOffset, arr.length);
    _freeArray(heapBytes);
    return res;
  }
  function allReady() {
    const typedArray = new Int32Array(list_number);
    time = new Date();
    console.log(time.getHours() + ":" + time.getMinutes() + ":" + time.getSeconds() + ':' + time.getMilliseconds());
    console.log(list_number)
    time = new Date();
    console.log(time.getHours() + ":" + time.getMinutes() + ":" + time.getSeconds() + ':' + time.getMilliseconds());
    console.log(square(typedArray));
    time = new Date();
    console.log(time.getHours() + ":" + time.getMinutes() + ":" + time.getSeconds() + ':' + time.getMilliseconds());
    console.log(ascending(typedArray))
    time = new Date();
    console.log(time.getHours() + ":" + time.getMinutes() + ":" + time.getSeconds() + ':' + time.getMilliseconds());
    console.log(list_number.sort((a, b) => a - b))
    time = new Date();
    console.log(time.getHours() + ":" + time.getMinutes() + ":" + time.getSeconds() + ':' + time.getMilliseconds());
  }
```

Vamos paso a paso:

Primero definimos un array vacío de 1000000 espacios

Luego asignamos la fecha y hora actual a la variable time. Es poco relevante esta asignación ya que necesitamos los minutos y segundos para medir los tiempos de trabajo y la variable al no ser reactiva necesita reasignacion antes de ser usada, pero al definirla con let aquí le estamos dando un scope global

Luego recorremos el array y le asignamos valores al azar entre 0 y 100000 usando la función getRandomInt.

_arrayToHeap es una función que recibe una array js y guarda punteros a los valores en un espacio de memoria asignado. Los punteros se generan con [Uint8Array](https://developer.mozilla.org/es/docs/Web/JavaScript/Referencia/Objetos_globales/Uint8Array) 

_freeArray es una función para liberar la memoria una vez que ya no se necesite. Ambos conceptos se explican en el ejemplo de WebAssembly: Array. Contenido de este repositorio

square recibe un array js. Lo convierte a punteros con la función descrita antes, actualiza la variable de tiempo, muestra H:M:S:d actuales y usa la función de C squareInt para procesar el array.

Crea un nuevo array desde el buffer de memoria con el resultado devuelto y libera la memoria asignada. 

Devuelve el nuevo array.

ascending recibe un array js, Lo convierte a punteros con la función descrita antes, usa la función order_ascending de C, crea un nuevo array con el resultado, libera la memoria y devuelve el nuevo array

allReady creamos un nuevo array de punteros con [Int32Array](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Int32Array) y conteniendo los valores de list_numbers

Durante todo el proceso renovamos el valor de time y mostramos en console.log la hora, minutos, segundos y décimas.

Todos los resultados se muestran en console.log() 

Orden de las llamadas de función:

Se muestra directamente el contenido de list_numbers

Se muestra el resultado de square (usando la función de C)

Se muestra el resultado de ascending (usando la función de C)

Se muestra el resultado de list_numbers ordenado por js

En cada proceso se saca el tiempo para hacer una comparativa "ruda" de las demoras.

El código de compilación: 

```bash
emcc main.cpp -o index.js -s EXPORTED_FUNCTIONS=['_main','_squareInt','_order_ascending','_free','_malloc'] -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap']  -s WASM=1 -Oz
```

Todos los parámetros han sido explicados en los ejemplos anteriores (Parámetros y arrays)