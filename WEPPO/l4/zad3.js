function Person(name, surname) {
    this.name = name;
    this.surname = surname;
}

Person.prototype.say = function() {
    return `${this.name} ${this.surname}`;
};

function Worker(name, surname, age) {
    Person.call(this, name, surname);
    this.age = age;
}

// poprawne dziedziczenie prototypów
Worker.prototype = Object.create(Person.prototype);
Worker.prototype.say = function() {

    return `${Person.prototype.say.call(this)} ${this.age}`;
};

const w = new Worker('tomasz', 'malinowski', 48);
console.log(w.say()); // "tomasz malinowski 48"

// nieprawidłowe 1. - nadpisanie metody say w Worker.prototype
// nadpisuje też Person.prototype, gdyż są tym samym obiektem
Worker.prototype = Person.prototype;
Worker.prototype.say = function() {
    return `${this.name} ${this.surname}, Age: ${this.age}`;
};

const person1 = new Person('Jan', 'Kowalski');
const worker1 = new Worker('Tomasz', 'Malinowski', 48);

console.log(person1.say()); // "Tomasz Malinowski, Age: 48"
console.log(worker1.say()); // "Tomasz Malinowski, Age: 48"

// nieprawidłowe 2. - prototyp Worker ma name i surname z
// zainicjalizowanymi wartościami dla wszystkich instancji Worker
// say odwołuje się do this.age, której nie ma w Worker.prototype
Worker.prototype = new Person('Default', 'User');
Worker.prototype.say = function() {
    return `${this.name} ${this.surname}, Age: ${this.age}`;
};

const person2 = new Person('Jan', 'Kowalski');
const worker2 = new Worker('Tomasz', 'Malinowski', 48);

console.log(person2.say()); // "Jan Kowalski"
console.log(worker2.say()); // "Tomasz Malinowski, Age: 48"
console.log(Worker.prototype.say()); // "Default User, Age: undefined"
