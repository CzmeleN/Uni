const car = {
    make: "Honda"
}

console.log(car.make)
console.log(car["make"])

// Różnice między . a []:
// Operator . może być używany tylko z nazwami kluczy, które są poprawnymi identyfikatorami w JavaScript (np. nie mogą zawierać myślników, nie mogą zaczynać się od liczby).
// Operator [] umożliwia dostęp do kluczy o dowolnych nazwach, w tym takich zawierających znaki specjalne, spacje, czy zaczynających się od liczb.
//
// Operator . wymaga statycznej nazwy klucza, znanej w czasie pisania kodu.
// Operator [] umożliwia użycie zmiennych lub wyrażeń jako nazwy klucza.

const obj = {}
obj[123] = "answer"

console.log(obj["123"])
console.log(obj[123])
console.log(Object.keys(obj)) // Klucz jest zawsze konwertowany na string

const obj = {}
const keyObj = { id: 1 }
const anotherKeyObj = { id: 2 }

obj[keyObj] = "Object Key 1"
obj[anotherKeyObj] = "Object Key 2"

console.log(obj[keyObj]) // Object Key 2
console.log(obj[anotherKeyObj]) // Object Key 2
console.log(Object.keys(obj)) // ['[object Object]']

// Liczby: Programista może myśleć, że klucz jest liczbą, ale JavaScript automatycznie konwertuje go na string.
// Ważne jest, aby pamiętać, że obj[42] i obj['42'] odnoszą się do tego samego klucza.
//
// Obiekty: Używając obiektów jako kluczy, programista musi zdawać sobie sprawę, że wszystkie obiekty
// zostaną skonwertowane na ten sam string ('[object Object]'), co może prowadzić do nieoczekiwanych zachowań.
// Aby używać obiektów jako unikalnych kluczy, można rozważyć użycie struktur danych takich jak Map,
// które pozwalają na użycie obiektów jako kluczy bez konwersji na string.

const arr = [10, 11]
arr["one"] = "Hello" 
arr["1"] = "Eleven"

console.log(arr[0]) // 10
console.log(arr["one"]) // Hello
console.log(arr[1]) // Eleven

// Kiedy używamy stringu jako klucza, JavaScript przechowuje tę właściwość w tablicy jako zwykłą właściwość obiektu,
// a nie jako element tablicy. W powyższym przykładzie arr['first'] jest oddzielną właściwością, a nie elementem tablicy.
// Ustawienie arr['1'] nadpisuje istniejący element na indeksie 1.

const arr = [1, 2, 3];

const keyObj = { key: "value" };
const anotherKeyObj = { key: "another" };

arr[keyObj] = "Object Key";
arr[anotherKeyObj] = "Another Object Key";

console.log(arr[keyObj]);            // Another Object Key
console.log(arr[anotherKeyObj]);     // Another Object Key
console.log(arr["[object Object]"]); // Another Object Key

console.log(arr.length);             // 3
console.log(arr);                    // [1, 2, 3, '[object Object]': 'Another Object Key']

// Podobnie jak w przypadku obiektów jako kluczy dla zwykłych obiektów, tablice również konwertują obiekty na string ('[object Object]').
// Oznacza to, że różne obiekty będą odnosić się do tego samego klucza '[object Object]', co może prowadzić do nadpisywania wartości.

const arr = [100, 200, 300];

arr["name"] = "MyArray";
arr["0x1"] = "Hex Key";

console.log(arr.name);   // MyArray
console.log(arr["0x1"]); // Hex Key
console.log(arr.length); // 3
console.log(arr);        // [100, 200, 300, name: "MyArray", '0x1': "Hex Key"]

// Dodawanie właściwości z kluczami niebędącymi liczbami dodaje je jako zwykłe właściwości obiektu tablicy,
// bez wpływu na length lub istniejące indeksy.

const arr = [1, 2, 3, 4, 5];
console.log(arr);          // [1, 2, 3, 4, 5]
console.log(arr.length);   // 5

arr.length = 3;
console.log(arr);          // [1, 2, 3]
console.log(arr.length);   // 3

arr.length = 5;
console.log(arr);          // [1, 2, 3, <2 empty items>]
console.log(arr.length);   // 5

console.log(arr[3]);       // undefined
console.log(arr[4]);       // undefined

// Ustawienie length na wartość mniejszą niż obecna liczba elementów:
// Elementy o indeksach równych lub większych niż nowa długość zostaną usunięte.
//
// Ustawienie length na wartość większą niż obecna liczba elementów:
// Tablica zostanie rozszerzona, a nowe elementy zostaną ustawione jako undefined.
