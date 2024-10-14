function divisible(x) {
    let div, sum = 0, temp = x;

    while (temp) {
        div = temp % 10;
        if (div == 0 || temp % div) {
            return false;
        }
        sum += div;
        temp = Math.floor(temp / 10);
    }

    return x % sum == 0;
}

function list_divisible() {
    let res = [];

    for (let i = 1; i <= 100000; ++i) {
        if (divisible(i)) {
            res.push(i);
        }
    }

    return res;
}

console.log(list_divisible())