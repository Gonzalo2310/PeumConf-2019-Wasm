# WebAssembly básico con C / C++ 

## Binding

El concepto de binding es un poco confuso en según que ámbito. La expresión mas completa que encontré en español dice así: 

 *`Binding` como en `Language binding` se refiere a un código que permite a un lenguaje de programación usar código escrito en otro lenguaje, normalmente realizando un mapeo entre las funciones del código externo y funciones propias que quedan disponibles en el lenguaje de programación al que pertenecen las `bindings`.*

Que fue una respuesta del usuario `sanzante` en 2015 en los foros de [stackexchange en español](https://spanish.stackexchange.com/questions/15534/binding-en-castellano) 

La forma de bindear (enlazar, y aunque no sea completamente correcto usare esta expresión desde ahora.) de Emscripten es totalmente diferente a lo que hemos visto ahora.

También el proyecto es mas simple en el uso en js y casi todo el trabajo extra queda en el archivo C++.

Enlazaremos una clase de C++ con 2 propiedades y 5 métodos y crearemos los objetos con js.

Si han mirado los demás ejemplos verán que casi todo cambia aquí así que explicare cada cosa como si este ejemplo fuera único.

Código de la clase en C++

```c++
class PeumClass {
public:
    PeumClass(int x, std::string y)
            : x(x), y(y) {}

    void incrementX() {
        ++x;
    }

    long restX(int divisor) {
        return x%divisor;
    }

    int getX() const { return x; }

    void setX(int x_) { x = x_; }

    static std::string getStringFromInstance(const PeumClass &instance) {
        return instance.y;
    }

private:
    int x;
    std::string y;
};
```

No hay aquí nada que pueda parecer extraño para cualquier programador de C++ (o eso supongo) pero explicaremos un poco.

Hemos definido una clase PeumClass. En el constructor de la clase pedimos dos valores: 

X -> entero

Y->cadena de caracteres



Luego definimos incrementX que es un método que no devuelve nada ni recibe parámetros. Simplemente aumenta en 1 la propiedad X

Definimos restX que recibe un valor entero que sera el divisor y devuelve el resto de la división de la propiedad X / divisor.

getX no recibe parámetros y solo devuelve el estado actual de X

setX recibe un parámetro entero y le asigna a la propiedad X ese valor

getStringFromInstance  simplemente devuelve Y que es la cadena de caracteres que se creo en la instancia de la clase

Ahora veremos el proceso para crear el Binding (si han visto código de otros ejemplo y han comparado con este observaran que aquí no se esta usando extern "C")

Seguimos con el código en C++

```c++
EMSCRIPTEN_BINDINGS(my_class_example) {
    class_<PeumClass>("PeumClass")
            .constructor<int, std::string>()
            .function("incrementX", &PeumClass::incrementX)
            .function("restX", &PeumClass::restX)
            .property("x", &PeumClass::getX, &PeumClass::setX)
            .class_function("getStringFromInstance", &PeumClass::getStringFromInstance);
}
```

Es mas claro el código que la posible explicación linea a linea. Solo decir que estamos diciendo que partes del todo pueden ser enlazadas por js y definimos ámbito de cada una y el tipo relacionado

El código termina con:

```c++
int main() {
    emscripten_run_script("allReady()");
    return 1;
}
```

allReady es la función que se ejecutara cuando el código este completamente cargado en js. 

Código JS

```javascript
function allReady() {
    const instance = new Module.PeumClass(10, "Conferencia Peum 2020");
    console.log('valores originales: ')
    console.log({
      x: instance.x,
      texto: Module.PeumClass.getStringFromInstance(instance)
    })
    instance.incrementX()
    console.log('Despues del incrementX: ')
    console.log({
      x: instance.x,
      texto: Module.PeumClass.getStringFromInstance(instance)
    })
    instance.x = 20
    console.log('Despues de la asignacion: ')
    console.log({
      x: instance.x,
      texto: Module.PeumClass.getStringFromInstance(instance)
    })
    console.log('Resto de dividir X entre 3: ', instance.restX(3))
    instance.delete()

  }
```

Como dijimos antes ponemos todo dentro de la función allReady para asegurar de que lo que vamos a usar este disponible.

En la primer linea creamos el objeto instanciando la clase con los parámetros requeridos.

Los dos siguientes console.log son: el primero un mensaje y el segundo simplemente el contenido de las propiedades del objeto que deberían ser idénticas a la instancia ya que no hemos modificado nada.

Inmediatamente utilizamos incrementX

y volvemos a repetir el proceso anterior para mostrar el mensaje y las propiedades del objeto y comprobar si es verdad que X a aumentado en 1

Ahora cambiamos el valor de X asignando 20

y volvemos a comprobar las propiedades.

el ultimo console.log nos vale para obtener el resto de la división del valor X / 3

Al final eliminamos el objeto

La linea de comando para la compilación también tiene cambios respecto a los demás ejemplos:

```bash
emcc --bind main.cpp -o index.js -s EXPORTED_FUNCTIONS=['_main']  -s WASM=1
```

El --bind es para el enlazado 

main.cpp es nuestro archivo fuente

-o index.js para el archivo de salida

Las funciones exportadas en este caso es solo una `main` con el guion bajo ( _ ) delante del nombre de la función.

Y por ultimo le indicamos que cree el archivo wasm correspondiente