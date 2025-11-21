-- CREATE NONCLUSTERED INDEX Czytelnik_PESEL_Covering
-- ON Czytelnik (PESEL)
-- INCLUDE (Nazwisko);
-- GO

SELECT Nazwisko 
FROM Czytelnik WITH(INDEX(Czytelnik_UK_PESEL))
WHERE PESEL = '90010112345';

SELECT Nazwisko 
FROM Czytelnik 
WHERE PESEL = '90010112345';