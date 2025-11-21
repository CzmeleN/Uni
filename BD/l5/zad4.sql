-- CREATE NONCLUSTERED INDEX Egzemplarz_KsiazkaID
-- ON Egzemplarz (Ksiazka_ID);

SELECT e.Egzemplarz_ID, k.Tytul
FROM Ksiazka k
JOIN Egzemplarz e ON k.Ksiazka_ID = e.Ksiazka_ID
WHERE k.Ksiazka_ID = 1;

SELECT e.Egzemplarz_ID, k.Tytul
FROM Ksiazka k
JOIN Egzemplarz e WITH(INDEX(0)) ON k.Ksiazka_ID = e.Ksiazka_ID
WHERE k.Ksiazka_ID = 1;