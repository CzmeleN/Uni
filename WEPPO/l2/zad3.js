console.log( (![]+[])[+[]] + (![]+[])[+!+[]] + ([![]]+[][[]])[+!+[]+[+[]]] + (![]+[])[!+[]+!+[]] );

// (![]+[])[+[]]
//
//     ![] → false
//     false + [] → 'false' (konkatenacja false i pustej tablicy)
//     +[] → 0 (konwersja pustej tablicy na liczbę)
//     'false'[0] → 'f'
//
// (![]+[])[+!+[]]
//
//     +[] → 0
//     !+[] → !0 → true
//     +!+[] → +true → 1
//     'false'[1] → 'a'
//
// ([![]]+[][[]])[+!+[]+[+[]]]
//
//     [![]] → [false]
//     [][[]] → [][''] → undefined
//     [false] + undefined → 'false' + 'undefined' → 'falseundefined'
//     +!+[] → 1
//     [+[]] → [0]
//     +!+[] + [+[]] → 1 + [0] → '10' (konkatenacja 1 i '0')
//     'falseundefined'[10] → 'i'
//
// (![]+[])[!+[]+!+[]]
//
//     !+[] → true
//     !+[] + !+[] → true + true → 2 (konwersja true na 1 i dodanie)
//     'false'[2] → 'l'
