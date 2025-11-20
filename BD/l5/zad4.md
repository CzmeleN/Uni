# zad4
weźmy
```SQL
SELECT * FROM Książka k JOIN Egzemplarz e ON k.Ksiazka_ID = e.Ksiazka_ID
```

## clustered index
w Książka: Książka_ID
w Egzemlarz: Egzemplarz_ID

bez indeksu na FK sql server musiałby wykonać clustered index scan - przeskanować całą tabelę na tabeli egzemplarz, aby znaleźć pasujące

## non-clustered
w Egzemplarz: Książka_ID

silnik wykona index seek, co zmniejszy liczbę odczytów, szczególnie gdy szukamy jednej konkretnej
