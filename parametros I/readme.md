# WebAssembly con C / C ++ 

## Parámetros

Aquí podemos ver el ejemplo de una función con parámetros creada en WebAssembly y usada en js

El código en JS explica todas las posibilidades de como llamar una función con parámetros y ejemplos de uso. 

La funcionalidad es usando uno de esos ejemplos.

 En C / C ++ el código explicado: 

```c
int main() {
emscripten_run_script( "allReady()" );
return 1;
}
```

 La función emscipten_run_script esta integrada en la librería Emscipten.h y crea una función que es invocada cuando el js ha sido completamente cargado en el sistema.

Usaremos esa función en JS para evitar invocar código antes de que se cargue.

```c
extern "C" {
int limits(int js_number) {
return js_number > 100 ? js_number - 100 : js_number;
    }
}
```

Extern "C" encierra el código que deberá ser exportado.

Lo que integra es un forma común de C / C ++ de definir una función que devuelve un entero, que también pide un entero en el único parámetro y cuyo nombre es limits

Lo que la función hace es sencillo: Si el parámetro es mayor de 100 le resta 100 y lo devuelve. Si el parámetro es menor de 100 lo devuelve tal cual sin cambios. 

No es una función útil fuera del contexto del ejemplo.

El código JS explicado:

```javascript
function allReady() {

const element = document.getElementById('contenido')
const roll = _limits(150) // forma sencilla de llamar a la funcion con un parametro predefinido
const contentText = document.createTextNode(roll + '') // Uso directo
element.appendChild(contentText)
}
```
Aquí vemos el uso de allReady que hemos creado en el main de C para invocar a la función que hemos creado cuando este cargada en el sistema.

En el archivo index.html hay comentadas las diferentes maneras de invocar la función y ejemplos.

En este caso hemos usado la función de forma directa con un valor fijo y lo hemos agregado al DOM. El resultado en la web debería ser 50 (explicación del funcionamiento de la función mas arriba).

El compilador de emscripten seria asi:

```bash
emcc main.cpp -o index.js -s EXPORTED_FUNCTIONS=['_main','_limits'] -s EXTRA_EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] -Oz -s WASM=1
```
Compilamos el main.cpp. 
La salida es en el mismo directorio y se llama index.js
Exportamos explícitamente las funciones que nos interesan agregando guion bajo ( _ ) al nombre de la función.
Exportamos funcionalidades de EmScripten para llamar a la función desde  JS.
Usamos la máxima compresión (-Oz [para mas opciones en la pagina de Emscripten](https://emscripten.org/docs/tools_reference/emcc.html#emccdoc)) 
Generamos el archivo WASM




