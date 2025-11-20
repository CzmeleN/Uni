# zad3

```SQL
SELECT DISTINCT c.PESEL, c.Nazwisko
FROM Egzemplarz e
JOIN Ksiazka k ON e.Ksiazka_ID=k.Ksiazka_ID
JOIN Wypozyczenie w ON e.Egzemplarz_ID=w.Egzemplarz_ID
JOIN Czytelnik c ON c.Czytelnik_ID = w.Czytelnik_ID;
```

```SQL
SELECT c.PESEL, c.Nazwisko
FROM Czytelnik c WHERE c.Czytelnik_ID IN (
SELECT w.Czytelnik_ID FROM Wypozyczenie w WHERE w.Egzemplarz_ID IN (
SELECT e.Egzemplarz_ID FROM Egzemplarz e WHERE e.Ksiazka_ID IN (
SELECT k.Ksiazka_ID FROM Ksiazka k)))
```

różnica:
1. JOIN + DISTINCT - łączy a potem usuwa duplikaty
  - najpierw ogromny zbiór wynikowy (iloczyn wszystkich złączeń)
  - potem sortowanie/hashowanie dla usunięcia duplikatów
2. filtruje Czytelników sprawdzając obecność ID w podzbiorach
  - powinno zostać zoptymalizowane jako semi-join
  - jeśli znajdzie pierwsze dopasowanie w tabeli podrzędnej (Wypożyczenie), przestaje szukać dalej dla tego Czytelnika
  - nie generuje duplikatów, ani nie sortuje


