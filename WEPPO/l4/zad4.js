var n = 1;

// liczba ma prototyp?
console.log( typeof Object.getPrototypeOf( n ) );

// można jej dopisać pole/funkcję?
n.foo = 'foo';
console.log( n.foo );

// javascript tworzy tymczasowy obiekt Number, który ma prototyp, jednak
// właściwość dodana do niego będzie usunięta od razu po wykonaniu operacji
// dlatego wynikiem jest undefined
