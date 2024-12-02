function map<T, U>(a: T[], f: (t: T) => U): U[] {
    const result: U[] = [];
    for (let i = 0; i < a.length; i++) {
        result.push(f(a[i]));
    }
    return result;
}

function filter<T>(a: T[], f: (t: T) => boolean): T[] {
    const result: T[] = [];
    for (let i = 0; i < a.length; i++) {
        if (f(a[i])) {
            result.push(a[i]);
        }
    }
    return result;
}

function forEach<T>(a: T[], f: (t: T) => void): void {
    for (let i = 0; i < a.length; i++) {
        f(a[i]);
    }
}

const numbers = [1, 2, 3, 4, 5];

const squares = map(numbers, (n) => n * n);
console.log(squares);

const evenNumbers = filter(numbers, (n) => n % 2 === 0);
console.log(evenNumbers);

forEach(numbers, (n) => console.log(n));
