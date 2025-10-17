EXEC sp_helpconstraint 'SalesLT.SalesOrderHeader';

-- ALTER TABLE SalesLT.SalesOrderHeader NOCHECK CONSTRAINT CK_SalesOrderHeader_ShipDate;

UPDATE SalesLT.SalesOrderHeader
SET ShipDate = '2005-06-30'
WHERE SalesOrderID = 71774;

SELECT SalesOrderID, OrderDate, ShipDate FROM SalesLT.SalesOrderHeader WHERE SalesOrderID = 71774;

ALTER TABLE SalesLT.SalesOrderHeader CHECK CONSTRAINT CK_SalesOrderHeader_ShipDate;

SELECT SalesOrderID, OrderDate, ShipDate
FROM SalesLT.SalesOrderHeader
WHERE ShipDate < OrderDate AND ShipDate IS NOT NULL;