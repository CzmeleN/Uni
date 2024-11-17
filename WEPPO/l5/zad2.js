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
    var answer = await(question('Podaj nazwę użytkownika: '));
    console.log('Witaj', answer);
    cl.close();
})();
