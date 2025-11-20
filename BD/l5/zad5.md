# zad5

załóżmy że chcemy pobrać nazwisko i datę urodzenia po PESELu

```SQL
SELECT Nazwisko, DataUrodzenia FROM Pacjenci WHERE PESEL = '90010112345';

CREATE NONCLUSTERED INDEX IX_Pacjenci_Pesel_Covering
ON Pacjenci (PESEL)
INCLUDE (Nazwisko, DataUrodzenia);
```

indeks pokrywający zawiera w sobie jako include wszystkie kolumny wymagane przez zapytanie, więc unikamy key lookup w głównej tabeli

plan wykonania pokaże operator index seek (NONCLUSTERED), nie będzie key lookup
