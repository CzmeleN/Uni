const readln = require('readline');
let cl = readln.createInterface( process.stdin, process.stdout );

function question (q) {
    return new Promise( (res, _) => {
        cl.question( q, answer => {
            res(answer);
        })
    });
};

(async function main() {
    let nr = Math.floor(Math.random() * 101);
    console.log('Zgadnij o jakiej liczbie z zakresu od 0 do 100 pomyślałem')

    while(true) {
        let guess = await(question('Podaj liczbę: '));

        if (guess > nr) {
            console.log('Podana liczba jest za duża :c');
        }
        else if (guess < nr) {
            console.log('Podana liczba jest za mała :c');
        }
        else {
            console.log('Gratulacje, zgadłeś!');
            break;
        }
    }

    cl.close();
})();


