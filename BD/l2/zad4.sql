IF NOT EXISTS (SELECT * FROM sys.types WHERE name = 'ListaID')
    CREATE TYPE dbo.ListaID AS TABLE (
        ID INT PRIMARY KEY
    );
GO

CREATE OR ALTER PROCEDURE dbo.SumujDniWypozyczen
    @ListaCzytelnikow dbo.ListaID READONLY
AS
BEGIN
    SELECT
        W.Czytelnik_ID AS reader_id,
        SUM(W.Liczba_Dni) AS sum_days
    FROM Wypozyczenie AS W
    JOIN @ListaCzytelnikow AS L ON W.Czytelnik_ID = L.ID
    GROUP BY
        W.Czytelnik_ID;
END;
GO

DECLARE @MojaListaID dbo.ListaID;

INSERT INTO @MojaListaID (ID) VALUES (1), (3);

EXEC dbo.SumujDniWypozyczen @ListaCzytelnikow = @MojaListaID;
