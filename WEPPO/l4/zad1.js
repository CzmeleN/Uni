function getLastProto(o) {
    var p = o;
    do {
        o = p;
        p = Object.getPrototypeOf(o);
    } while (p);
    return o;
}

const objLiteral = { a: 1 };
const array = [1, 2, 3];
function myFunction() {}
const date = new Date();
const objNullProto = Object.create(null);

const lastProtoObjLiteral = getLastProto(objLiteral);
const lastProtoArray = getLastProto(array);
const lastProtoFunction = getLastProto(myFunction);
const lastProtoDate = getLastProto(date);
const lastProtoNullProto = getLastProto(objNullProto);

console.log(lastProtoObjLiteral === lastProtoArray); // true
console.log(lastProtoObjLiteral === lastProtoFunction); // true
console.log(lastProtoObjLiteral === lastProtoDate); // true
console.log(lastProtoObjLiteral === lastProtoNullProto); // false

// obiekty z prototypem Object.prototype mają w swoim łańcuchu prot.
// na końcu Object.prototype, więc zbiegają do tego samego jednego obiektu
// obiekt z prototypem null ma prototyp null, więc zwróci sam obiekt
// i nie ma dalszego prototypu
