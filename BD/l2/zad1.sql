CREATE OR ALTER FUNCTION CzytelnicyPrzetrzymujacy (@LiczbaDni INT)
RETURNS TABLE
AS
RETURN
(
    SELECT
        C.PESEL,
        COUNT(W.Wypozyczenie_ID) AS LacznaLiczbaEgzemplarzy
    FROM Czytelnik AS C
    JOIN Wypozyczenie AS W ON C.Czytelnik_ID = W.Czytelnik_ID
    WHERE
        C.Czytelnik_ID IN (
            SELECT DISTINCT W_sub.Czytelnik_ID
            FROM Wypozyczenie AS W_sub
            WHERE W_sub.Liczba_Dni > @LiczbaDni
        )
    GROUP BY C.Czytelnik_ID, C.PESEL
);
GO

SELECT * FROM CzytelnicyPrzetrzymujacy(5);
