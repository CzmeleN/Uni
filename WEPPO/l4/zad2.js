var p = {
    name: 'jan'
};
var q = {
    surname: 'kowalski'
};
Object.setPrototypeOf(p, q);

console.log(p.name);
console.log(p.surname);


function isOwnProperty(obj, propName) {
    return obj.hasOwnProperty(propName);
}

console.log(isOwnProperty(p, 'name'));     // true
console.log(isOwnProperty(p, 'surname'));  // false

// pola/funkcje bezpośrednio w obiekcie
const ownProperties = Object.keys(p);
console.log(ownProperties);

const ownPropertyNames = Object.getOwnPropertyNames(p);
console.log(ownPropertyNames);

// pola/funcke w obiekcie i łańuchu prototypów
for (let prop in p) {
    console.log(prop);
}

// wszystkie, nie tylko enumerowalne
function getAllProperties(obj) {
    let props = new Set();
    while (obj != null) {
        Object.getOwnPropertyNames(obj).forEach(prop => props.add(prop));
        obj = Object.getPrototypeOf(obj);
    }
    return Array.from(props);
}
const allProps = getAllProperties(p);
console.log('All properties:', allProps);
