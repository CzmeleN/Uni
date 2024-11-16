// klucze w WeakMap są obiektami, a wartości przechowywane dopóki
// istnieje odniesienie do klucza
const privateMethods = new WeakMap();

function Foo() {
    function Qux() {
        console.log("Foo::Qux");
    }

    privateMethods.set(this, { Qux });
}

Foo.prototype.Bar = function() {
    const methods = privateMethods.get(this);

    if (methods && methods.Qux) {
        methods.Qux();
    }
    else {
        console.log("Prywatna metoda Qux nie jest dostępna.");
    }
};

var foo = new Foo();
foo.Bar(); // "Foo::Qux"

try {
    foo.Qux();
}
catch (error) {
    console.error(error); // TypeError: foo.Qux is not a function
}
