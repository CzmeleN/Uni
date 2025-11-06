IF OBJECT_ID('SalesLT.ProductPriceHistory', 'U') IS NOT NULL
    DROP TABLE SalesLT.ProductPriceHistory;
GO

CREATE TABLE SalesLT.ProductPriceHistory (
    ProductPriceHistoryID INT IDENTITY PRIMARY KEY,
    ProductID INT NOT NULL,
    StandardCost MONEY NULL,
    ListPrice MONEY NULL,
    ChangeDate DATETIME2 NOT NULL
);
GO

CREATE  OR ALTER TRIGGER SalesLT.trg_Product_PriceCostLifecycle
ON SalesLT.Product
AFTER INSERT, UPDATE, DELETE
AS
BEGIN
    -- INSERT
    INSERT INTO SalesLT.ProductPriceHistory (ProductID, StandardCost, ListPrice, ChangeDate)
    SELECT
        i.ProductID,
        i.StandardCost,
        i.ListPrice,
        SYSDATETIME()
    FROM
        inserted i
    WHERE
        NOT EXISTS (SELECT 1 FROM deleted d WHERE d.ProductID = i.ProductID);


    -- UPDATE
    INSERT INTO SalesLT.ProductPriceHistory (ProductID, StandardCost, ListPrice, ChangeDate)
    SELECT
        i.ProductID,
        i.StandardCost,
        i.ListPrice,
        SYSDATETIME()
    FROM
        inserted i
    INNER JOIN
        deleted d ON i.ProductID = d.ProductID
    WHERE
        i.StandardCost != d.StandardCost
        OR i.ListPrice != d.ListPrice;

    -- DELETE
    INSERT INTO SalesLT.ProductPriceHistory (ProductID, StandardCost, ListPrice, ChangeDate)
    SELECT
        d.ProductID,
        NULL,
        NULL,
        SYSDATETIME()
    FROM
        deleted d
    WHERE
        NOT EXISTS (SELECT 1 FROM inserted i WHERE i.ProductID = d.ProductID);
END;
GO

-- INSERT
DECLARE @TestProductID INT;
INSERT INTO SalesLT.Product (
    Name, ProductNumber, StandardCost, ListPrice, 
    ProductCategoryID, ProductModelID, SellStartDate
)
VALUES (
    'Test Product Lifecycle', 'TEST-LIFE', 10.00, 20.00, 
    (SELECT MIN(ProductCategoryID) FROM SalesLT.ProductCategory), 
    (SELECT MIN(ProductModelID) FROM SalesLT.ProductModel), 
    GETDATE()
);

SET @TestProductID = SCOPE_IDENTITY();

SELECT ProductID, StandardCost, ListPrice, ChangeDate 
FROM SalesLT.ProductPriceHistory WHERE ProductID = @TestProductID;
GO

-- ZMIANA CENY
WAITFOR DELAY '00:00:01';
DECLARE @TestProductID INT = (SELECT ProductID FROM SalesLT.Product WHERE ProductNumber = 'TEST-LIFE');

UPDATE SalesLT.Product
SET ListPrice = 25.00 
WHERE ProductID = @TestProductID;

SELECT ProductID, StandardCost, ListPrice, ChangeDate 
FROM SalesLT.ProductPriceHistory WHERE ProductID = @TestProductID 
ORDER BY ChangeDate;
GO

-- ZMIANA NAZWY
WAITFOR DELAY '00:00:01';
DECLARE @TestProductID INT = (SELECT ProductID FROM SalesLT.Product WHERE ProductNumber = 'TEST-LIFE');

UPDATE SalesLT.Product
SET Name = 'Test Product Lifecycle V2'
WHERE ProductID = @TestProductID;

SELECT ProductID, StandardCost, ListPrice, ChangeDate 
FROM SalesLT.ProductPriceHistory WHERE ProductID = @TestProductID 
ORDER BY ChangeDate;
GO

-- DELETE
WAITFOR DELAY '00:00:01';
DECLARE @TestProductID INT = (SELECT ProductID FROM SalesLT.Product WHERE ProductNumber = 'TEST-LIFE');

DELETE FROM SalesLT.Product
WHERE ProductID = @TestProductID;

SELECT ProductID, StandardCost, ListPrice, ChangeDate 
FROM SalesLT.ProductPriceHistory WHERE ProductID = @TestProductID 
ORDER BY ChangeDate;
GO

SELECT 
    ProductID, 
    StandardCost, 
    ListPrice,
    ChangeDate AS EffectiveStartDate,
    -- LEAD bierze z następnego wiersza
    LEAD(ChangeDate, 1, NULL) OVER (
        PARTITION BY ProductID 
        ORDER BY ChangeDate
    ) AS EffectiveEndDate
FROM 
    SalesLT.ProductPriceHistory
ORDER BY 
    ProductID, EffectiveStartDate;

DECLARE @TestProductID INT = (SELECT ISNULL(MAX(ProductID),0) FROM SalesLT.ProductPriceHistory WHERE ProductID NOT IN (SELECT ProductID FROM SalesLT.Product));
IF @TestProductID != 0
BEGIN
    DELETE FROM SalesLT.ProductPriceHistory
    WHERE ProductID = @TestProductID;
END
GO