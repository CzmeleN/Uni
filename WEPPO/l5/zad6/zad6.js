const fs = require('fs');
const readln = require('readline');
const https = require('https');

let cl = readln.createInterface( process.stdin, process.stdout );

function question (q) {
    return new Promise( (res, _) => {
        cl.question( q, answer => {
            res(answer);
        })
    });
};

async function analyzeLog(path) {
    const ipCounts = {};

    const rl = readln.createInterface({
        input: fs.createReadStream(path)
    });

    for await (const line of rl) {
        const parts = line.split(' ')
        const ip = parts[1];

        ipCounts[ip] = (ipCounts[ip] || 0) + 1;
    }

    const sortedIps = Object.entries(ipCounts).sort(([, countA], [, countB]) => countB - countA).slice(0, 3);

    console.log('Najwięcej zapytań wysłali: ');

    sortedIps.forEach(([ip, count]) => {
        console.log(`${ip} ${count}`);
    });
}

(async function main() {
    var answer = await(question('Podaj ścieżkę do pliku: '));
    analyzeLog(answer);
    cl.close();
})();
