const readln = require('readline');
const fs = require('fs').promises;

let cl = readln.createInterface( process.stdin, process.stdout );

function question (q) {
    return new Promise( (res, _) => {
        cl.question( q, answer => {
            res(answer);
        })
    });
};

async function readPrintFile(path) {
    try {
        const data = await fs.readFile(path, 'utf-8');
        console.log('Zawartość:\n')
        console.log(data);
    } catch (err) {
        console.error('Error: ', err.message);
    }
}

(async function main() {
    var answer = await(question('Podaj ścieżkę do pliku: '));
    readPrintFile(answer);
    cl.close();
})();
