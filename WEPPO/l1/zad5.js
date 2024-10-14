function fib_rec(n) {
    if (n == 0) {
        return 0;
    }
    else if (n <= 2) {
        return 1;
    }

    return fib_rec(n - 1) + fib_rec(n - 2);
}

function fib_it(n) {
    let x = 0, y = 1, temp;

    while(n--) {
        temp = x;
        x = y;
        y = temp + y;
    }

    return x;
}

function print_times() {
    console.log("[i]\n[time rec]\n[time iter]\n");
    for (let i = 10; i <= 40; i++) {
        console.log(`${i}.`);

        console.time("rec: ");
        fib_rec(i);
        console.timeEnd("rec: ");

        console.time("iter: ");
        fib_it(i);
        console.timeEnd("iter: ");

        console.log();
    }
}

print_times();