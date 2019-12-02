# WebAssembly básico con C / C++ 

Este proyecto fue presentado en la **PEUMCONF 2019**. Se aceptan sugerencias y colaboraciones para mejorar el código pero el avance de WebAssembly sera en otro repositorio. 

Mis conocimientos de C / C++ son bastante limitados y seguramente el código en el repositorio es mejorable al 100%

Cada repositorio ya tiene el código compilado para que se pueda probar. Aunque el archivo principal sea un HTML en todos los casos necesita un servidor para ser levantados y que funcione el  WebAssembly.

Si se usa Apache, Nginx o similar es tan sencillo como llevar los archivos al localhost del ordenador o servidor.

Si se usa nodejs o similares se puede migrar el contenido de los html (solo importa el js en todos los casos, y solo el ejemplo parámetros usa el html pero se puede modificar)

Cada carpeta de cada  proyecto tiene un CMakeList.txt que se utilizar para compilar en C / C++ y deberá cambiarse la ubicación del emsdk a la que corresponda.

En cada carpeta del proyecto hay un readme.md especifico del caso. Se recomienda seguir el orden:

*holamundo / Parametros I / Arrays / ArraysTwoWays / Binding*

porque así se va de menos a mas y ademas los readme no repiten explicaciones dadas en otros ejemplos.



Este proyecto utiliza Emscripten para la compilación del código fuente y la generación del archivo js.

Como obtener, configurar y usar Emscripten de modo genérico se deben seguir las instrucciones de aquí:

[Emscripten](https://emscripten.org/docs/getting_started/downloads.html)



Carpetas: 

Sliders:  Sliders en un archivo .odp (libreoffice) y el mismo contenido en pdf. [Online](https://docs.google.com/presentation/d/1RErP39QH7Xj01XUmZUVHu8hgVh9TYBWWkiWS7sq-RQ8/edit?usp=sharing)

holamundo: El ejemplo mas sencillo. Hello world por consola.

Parámetros I: Ejemplo de como se pueden usar funciones con parámetros.

Arrays: Ejemplo del uso de arrays

ArraysTwoWays: Ejemplo de uso del Array y modificación tanto en js como en WebAssembly

Binding: Ejemplo de uso de objecto de C++ en Js.

