type User = {
    type: 'user'; // Dodane pole 'type' z wartością 'user'
    name: string;
    age: number;
    occupation: string;
}

type Admin = {
    type: 'admin'; // Dodane pole 'type' z wartością 'admin'
    name: string;
    age: number;
    role: string;
}

export type Person = User | Admin;

export const persons: Person[] = [
    {
        type: 'user', // Dodane pole 'type'
        name: 'Jan Kowalski',
        age: 17,
        occupation: 'Student'
    },
    {
        type: 'admin', // Dodane pole 'type'
        name: 'Tomasz Malinowski',
        age: 20,
        role: 'Administrator'
    }
];

export function isAdmin(person: Person): person is Admin {
    return person.type === 'admin';
}

export function isUser(person: Person): person is User {
    return person.type === 'user';
}

export function logPerson(person: Person) {
    let additionalInformation: string = '';
    if (isAdmin(person)) {
        additionalInformation = person.role;
    }
    if (isUser(person)) {
        additionalInformation = person.occupation;
    }
    console.log(` - ${person.name}, ${person.age}, ${additionalInformation}`);
}

// Przykładowe wywołanie funkcji
persons.forEach(logPerson);
