IF NOT EXISTS (SELECT * FROM sys.types WHERE name = 'ListaID')
    CREATE TYPE dbo.ListaID AS TABLE (
        ID INT PRIMARY KEY
    );
GO

CREATE OR ALTER PROCEDURE dbo.ZatrzymajProdukty
    @ListaProduktow dbo.ListaID READONLY,
    @DataZatrzymania DATE
AS
BEGIN
    DECLARE @ProductID INT;
    DECLARE @ProductName NVARCHAR(100);
    DECLARE @Msg NVARCHAR(500);

    DECLARE cur_skip CURSOR FOR
        SELECT P.ProductID, P.Name
        FROM SalesLT.Product AS P
        JOIN @ListaProduktow AS L ON P.ProductID = L.ID
        WHERE P.DiscontinuedDate IS NOT NULL;

    OPEN cur_skip;
    FETCH NEXT FROM cur_skip INTO @ProductID, @ProductName;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @Msg = FORMATMESSAGE('produkt id: %d (%s) ma już datę zatrzymania produkcji', @ProductID, @ProductName);
        PRINT @Msg;
        FETCH NEXT FROM cur_skip INTO @ProductID, @ProductName;
    END;
    
    CLOSE cur_skip;
    DEALLOCATE cur_skip;

    UPDATE P
    SET
        P.DiscontinuedDate = @DataZatrzymania
    FROM
        SalesLT.Product AS P
    JOIN
        @ListaProduktow AS L ON P.ProductID = L.ID
    WHERE
        P.DiscontinuedDate IS NULL;
    
    PRINT FORMATMESSAGE('zaaktualizowano %d produktów', @@ROWCOUNT);
END;
GO

DECLARE @MojeProdukty dbo.ListaID;

INSERT INTO @MojeProdukty (ID) VALUES (680), (706), (708);

EXEC dbo.ZatrzymajProdukty @ListaProduktow = @MojeProdukty, @DataZatrzymania = '2025-10-23';
