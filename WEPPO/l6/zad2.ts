function fib(n: number): number {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

function memoize(fn: (n: number) => number): (n: number) => number {
    const cache: { [key: number]: number } = {};
    return function(n: number): number {
        if (n in cache) {
            return cache[n];
        } else {
            const result = fn(n);
            cache[n] = result;
            return result;
        }
    }
}

let memofib: (n: number) => number;
memofib = memoize(function(n: number): number {
    if (n <= 1) return n;
    return memofib(n - 1) + memofib(n - 2);
});

function compareFib(n: number): void {
    console.log(`Obliczanie fib(${n}) bez memoizacji:`);
    console.time('fib bez memoizacji');
    const result1 = fib(n);
    console.timeEnd('fib bez memoizacji');
    console.log(`Wynik: ${result1}\n`);

    console.log(`Obliczanie fib(${n}) z memoizacją:`);
    console.time('fib z memoizacją');
    const result2 = memofib(n);
    console.timeEnd('fib z memoizacją');
    console.log(`Wynik: ${result2}\n`);
}
