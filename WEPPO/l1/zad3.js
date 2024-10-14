function list_primes() {
    let is_prime = new Array(100000).fill(true);
    let res = [];

    for (let i = 2; i * i <= 100000; ++i) {
        for (let j = i * i; j <= 100000; j += i) {
            is_prime[j] = false;
        }
    }

    for (let i = 2; i <= 100000; ++i) {
        if (is_prime[i]) {
        res.push(i);
        }
    }

    return res;
}

console.log(list_primes());