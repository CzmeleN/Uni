typeof "Hello, World!"; // "string"
typeof 42;              // "number"
typeof true;            // "boolean"
typeof undefined;       // "undefined"
typeof { name: "Alice" }; // "object"
typeof null;            // "object" 
typeof function() {};   // "function"
typeof Symbol();        // "symbol"

const date = new Date();
console.log(date instanceof Date);       // true
console.log(date instanceof Object);     // true

const arr = [];
console.log(arr instanceof Array);       // true
console.log(arr instanceof Object);      // true

function Person(name) {
  this.name = name;
}
const alice = new Person("Alice");
console.log(alice instanceof Person);    // true
console.log(alice instanceof Object);    // true

const obj = {};
console.log(obj instanceof Object);      // true
console.log(obj instanceof Array);       // false

//
// Cecha                     typeof                                                instanceof
// Zakres zastosowania       Typów prymitywnych i funkcji oraz ogólnych obiektów   Tylko obiektów, sprawdza instancję konstruktora
// Zwracana wartość          "string" reprezentujący typ                           boolean (true/false)
// Sprawdzany typ            Typ prymitywny lub ogólny (np. "string", "object")    Konkretny konstruktor (np. Date, Array, Person)
// Przykładowe zastosowanie  Sprawdzanie typu zmiennych prymitywnych               Sprawdzanie dziedziczenia i instancji obiektów
// Obsługa funkcji           typeof zwraca "function"                              instanceof może sprawdzać, czy obiekt jest instancją Function
// Przykładowe ograniczenia  Nie rozróżnia między różnymi obiektami                Nie działa z prymitywnymi typami danych
//

