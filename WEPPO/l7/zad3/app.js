const express = require('express');
const cookieParser = require('cookie-parser');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(cookieParser());
app.use(express.urlencoded({ extended: true }));
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

function validateData(body) {
    const { firstName, lastName, courseName } = body;
    if (!firstName || !lastName || !courseName) {
        return false;
    }
    return true;
}

app.get('/', (req, res) => {
    res.render('form', { error: null });
});

app.post('/', (req, res) => {
    const { firstName, lastName, courseName } = req.body;
    const tasks = [];
    for (let i = 1; i <= 10; i++) {
        const val = parseFloat(req.body[`task${i}`]) || 0;
        tasks.push(val);
    }

    if (!validateData(req.body)) {
        return res.render('form', { error: 'Imię, nazwisko i nazwa zajęć są wymagane!' });
    }

    res.cookie('firstName', firstName, { httpOnly: true });
    res.cookie('lastName', lastName, { httpOnly: true });
    res.cookie('courseName', courseName, { httpOnly: true });
    res.cookie('tasks', JSON.stringify(tasks), { httpOnly: true });

    res.redirect('/print');
});

app.get('/print', (req, res) => {
    const { firstName, lastName, courseName } = req.cookies;
    const tasks = JSON.parse(req.cookies.tasks || '[]');
    const sum = tasks.reduce((acc, val) => acc + val, 0);

    if (!firstName || !lastName || !courseName || !tasks.length) {
        return res.redirect('/');
    }

    res.render('print', { firstName, lastName, courseName, tasks, sum });
});

app.listen(PORT, () => {
    console.log(`Działa na porcie ${PORT}`);
});

