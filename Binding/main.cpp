#include <string>
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

using namespace emscripten;

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

// Binding code
EMSCRIPTEN_BINDINGS(my_class_example) {
    class_<PeumClass>("PeumClass")
            .constructor<int, std::string>()
            .function("incrementX", &PeumClass::incrementX)
            .function("restX", &PeumClass::restX)
            .property("x", &PeumClass::getX, &PeumClass::setX)
            .class_function("getStringFromInstance", &PeumClass::getStringFromInstance);
}

int main() {
    emscripten_run_script("allReady()");
    return 1;
}

// emcc --bind main.cpp -o index.js -s EXPORTED_FUNCTIONS=['_main']  -s WASM=1
