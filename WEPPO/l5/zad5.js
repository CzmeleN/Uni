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

function fetchWebsite(url) {
    return new Promise((resolve, reject) => {
        https.get(url, (response) => {
            let data = '';

            response.on('data', (chunk) => {
                data += chunk;
            });

            response.on('end', () => {
                resolve(data);
            });
        }).on('error', (err) => {
                reject(err);
        });
    });
}

(async function main() {
    var answer = await(question('Podaj URL strony: '));
    try {
        const data = await fetchWebsite(answer);
        console.log('Zawartość strony:\n');
        console.log(data);
    } catch (err) {
        console.error('Error: ', err.message);
    }
    cl.close();
})();
