-- UPDATE Ksiazka 
-- SET Wypozyczona_Ostatni_Miesiac = 1 
-- WHERE Ksiazka_ID <= 50;
-- GO

-- CREATE NONCLUSTERED INDEX Ksiazka_Wypozyczone
-- ON Ksiazka (Tytul)
-- WHERE Wypozyczona_Ostatni_Miesiac = 1;
-- GO

SELECT Tytul 
FROM Ksiazka 
WHERE Wypozyczona_Ostatni_Miesiac = 1;

SELECT Tytul 
FROM Ksiazka 
WHERE Wypozyczona_Ostatni_Miesiac = 0;