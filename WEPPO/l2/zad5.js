const person = {
    name: "Jan",

    introduceYourself: function() {
        console.log(`Cześć, nazywam się ${this.name}.`);
    },

    _age: 20,

    get age() {
        return this._age;
    },
    set age(newAge) {
        if (typeof newAge === "number" && newAge > 0) {
            this._age = newAge;
        } else {
            console.log("Podaj prawidłowy wiek.");
        }
    }
}

person.introduceYourself(); // Cześć, nazywam się Jan.
console.log(person.age); // 20
person.age = 21;
console.log(person.age); // 21
person.age = -5; // Podaj prawidłowy wiek.

const car = {
    make: "Honda"
}

car.model = "Accord"
console.log(car.model) // Accord

car.describe = function() {
    console.log(`To jest ${this.make} ${this.model}.`);
}

car.describe() // To jest Honda Accord.

Object.defineProperty(car, "yearOfProduction", {
    get: function() {
        return this._yearOfProduction
    },
    set: function(newYear) {
        if (typeof newYear === 'number' && newYear > 1885) {
            this._yearOfProduction = newYear
        }
        else {
            console.log('Podaj prawidłowy rok produkcji.')
        }
    },
})

car.yearOfProduction = 2020;
console.log(car.yearOfProduction); // 2020
car.yearOfProduction = 1800; // Podaj prawidłowy rok produkcji.

// Dodawanie Pól i Metod
//     Można dodawać za pomocą bezpośredniego przypisania:
//     Pole: obiekt.nowePole = wartość
//     Metoda: obiekt.nowaMetoda = function() { /* ... */ }
//
// Dodawanie Właściwości z Akcesorami get i set
//     Musi być dodane za pomocą Object.defineProperty lub podobnych metod:
//     Właściwość z akcesorami get i set: Nie można dodać takich właściwości poprzez bezpośrednie przypisanie
//     (np. obiekt.nowyGetterSetter = ...), ponieważ wymaga to definiowania funkcji get i set, co jest możliwe 
//     tylko poprzez Object.defineProperty lub Object.defineProperties.
