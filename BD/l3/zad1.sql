IF OBJECT_ID('SalesLT.SalesOrderDetailBackup', 'U') IS NOT NULL
    DROP TABLE SalesLT.SalesOrderDetailBackup;

CREATE TABLE SalesLT.SalesOrderDetailBackup(
    SalesOrderID int NOT NULL,
    SalesOrderDetailID int NOT NULL,
    OrderQty smallint NOT NULL,
    ProductID int NOT NULL,
    UnitPrice money NOT NULL,
    UnitPriceDiscount money NOT NULL,
    LineTotal numeric(38, 6) NOT NULL,
    rowguid uniqueidentifier NOT NULL,
    ModifiedDate datetime NOT NULL,
    PRIMARY KEY CLUSTERED (SalesOrderID, SalesOrderDetailID)
);
GO

-- NORMAL
DECLARE @StartTimeSet DATETIME2 = SYSDATETIME();

INSERT INTO SalesLT.SalesOrderDetailBackup
SELECT * FROM SalesLT.SalesOrderDetail;

DECLARE @EndTimeSet DATETIME2 = SYSDATETIME();
PRINT 'Normal execution time: ' + CAST(DATEDIFF(MILLISECOND, @StartTimeSet, @EndTimeSet) AS VARCHAR) + ' ms';
GO

TRUNCATE TABLE SalesLT.SalesOrderDetailBackup;
GO

-- CURSOR
DECLARE @StartTimeCursor DATETIME2 = SYSDATETIME();

DECLARE @SalesOrderID INT, @SalesOrderDetailID INT, @OrderQty SMALLINT, 
        @ProductID INT, @UnitPrice MONEY, @UnitPriceDiscount MONEY, 
        @LineTotal NUMERIC(38,6), @rowguid UNIQUEIDENTIFIER, @ModifiedDate DATETIME;

DECLARE c_Copy CURSOR FOR
    SELECT SalesOrderID, SalesOrderDetailID, OrderQty, ProductID, UnitPrice, 
           UnitPriceDiscount, LineTotal, rowguid, ModifiedDate
    FROM SalesLT.SalesOrderDetail;

OPEN c_Copy;

FETCH NEXT FROM c_Copy INTO 
    @SalesOrderID, @SalesOrderDetailID, @OrderQty, @ProductID, @UnitPrice, 
    @UnitPriceDiscount, @LineTotal, @rowguid, @ModifiedDate;

WHILE @@FETCH_STATUS = 0
BEGIN
    INSERT INTO SalesLT.SalesOrderDetailBackup (
        SalesOrderID, SalesOrderDetailID, OrderQty, ProductID, UnitPrice, 
        UnitPriceDiscount, LineTotal, rowguid, ModifiedDate
    )
    VALUES (
        @SalesOrderID, @SalesOrderDetailID, @OrderQty, @ProductID, @UnitPrice, 
        @UnitPriceDiscount, @LineTotal, @rowguid, @ModifiedDate
    );

    FETCH NEXT FROM c_Copy INTO 
        @SalesOrderID, @SalesOrderDetailID, @OrderQty, @ProductID, @UnitPrice, 
        @UnitPriceDiscount, @LineTotal, @rowguid, @ModifiedDate;
END

CLOSE c_Copy;
DEALLOCATE c_Copy;

DECLARE @EndTimeCursor DATETIME2 = SYSDATETIME();
PRINT 'Cursor execution time: ' + CAST(DATEDIFF(MILLISECOND, @StartTimeCursor, @EndTimeCursor) AS VARCHAR) + ' ms';
GO