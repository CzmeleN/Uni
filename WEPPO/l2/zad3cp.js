console.log( (![]+[])[+[]] + (![]+[])[+!+[]] + ([![]]+[][[]])[+!+[]+[+[]]] + (![]+[])[!+[]+!+[]] );

console.log("\nGroup 1:")
console.log((![]+[])[+[]])

    console.log(![]) // → false
    console.log(false + []) // → 'false' (konkatenacja false i pustej tablicy)
    console.log(+[]) // → 0 (konwersja pustej tablicy na liczbę)
    console.log('false'[0]) // → 'f'

console.log("\nGroup 2:")
console.log((![]+[])[+!+[]])

    console.log(+[]) // → 0
    console.log(!+[]) // → !0 → true
    console.log(+!+[]) // → +true → 1
    console.log('false'[1]) // → 'a'

console.log("\nGroup 3:")
console.log(([![]]+[][[]])[+!+[]+[+[]]])

    console.log([![]]) // → [false]
    console.log([][[]]) // → [][''] → undefined
    console.log([false] + undefined) // → 'false' + 'undefined' → 'falseundefined'
    console.log(+!+[]) // → 1
    console.log([+[]]) // → [0]
    console.log(+!+[] + [+[]]) // → 1 + [0] → '10' (konkatenacja 1 i '0')
    console.log('falseundefined'[10]) // → 'i'

console.log("\nGroup 4:")
console.log((![]+[])[!+[]+!+[]])

    console.log(!+[]) // → true
    console.log(!+[] + !+[]) // → true + true → 2 (konwersja true na 1 i dodanie)
    console.log('false'[2]) // → 'l'
