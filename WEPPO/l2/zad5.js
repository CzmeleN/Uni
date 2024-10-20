const osoba = {
    imie: "Jan",

    przedstawSie: function() {
        console.log(`Cześć, nazywam się ${this.imie}.`);
    },

    _wiek: 20,

    get wiek() {
        return this._wiek;
    },
    set wiek(nowyWiek) {
        if (typeof nowyWiek === "number" && nowyWiek > 0) {
            this._wiek = nowyWiek;
        } else {
            console.log("Podaj prawidłowy wiek.");
        }
    }
}

osoba.przedstawSie(); // Cześć, nazywam się Jan.
console.log(osoba.wiek); // 20
osoba.wiek = 21;
console.log(osoba.wiek); // 21
osoba.wiek = -5; // Podaj prawidłowy wiek.

const samochod = {
    marka: "Honda"
}

samochod.model = "Accord"
console.log(samochod.model) // Accord

samochod.opisz = function() {
    console.log(`To jest ${this.marka} ${this.model}.`);
}

samochod.opisz() // To jest Honda Accord.

Object.defineProperty(samochod, "rokProdukcji", {
    get: function() {
        return this._rokProdukcji
    },
    set: function(nowyRok) {
        if (typeof nowyRok === 'number' && nowyRok > 1885) { // Pierwszy samochód zbudowano w 1886
            this._rokProdukcji = nowyRok
        } else {
            console.log('Podaj prawidłowy rok produkcji.')
        }
    },
})

samochod.rokProdukcji = 2020;
console.log(samochod.rokProdukcji); // 2020
samochod.rokProdukcji = 1800; // Podaj prawidłowy rok produkcji.

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
