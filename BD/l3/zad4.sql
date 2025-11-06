CREATE OR ALTER TRIGGER SalesLT.trg_Customer_UpdateModifiedDate
ON SalesLT.Customer
AFTER UPDATE
AS
BEGIN
    UPDATE c
    SET c.ModifiedDate = SYSDATETIME()
    FROM SalesLT.Customer c
    INNER JOIN inserted i ON c.CustomerID = i.CustomerID;
END;
GO

SELECT CustomerID, FirstName, LastName, ModifiedDate 
FROM SalesLT.Customer WHERE CustomerID = 1;

WAITFOR DELAY '00:00:01';

UPDATE SalesLT.Customer
SET FirstName = 'Juan'
WHERE CustomerID = 1;

SELECT CustomerID, FirstName, LastName, ModifiedDate 
FROM SalesLT.Customer WHERE CustomerID = 1;