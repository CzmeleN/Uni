ALTER TABLE SalesLT.Customer
ADD CreditCardNumber VARCHAR(25) NULL;
GO

UPDATE SalesLT.SalesOrderHeader
SET CreditCardApprovalCode = 'APPROVED_TEST'
WHERE SalesOrderID IN (SELECT TOP 3 SalesOrderID FROM SalesLT.SalesOrderHeader ORDER BY NEWID()); -- new id w losowej

UPDATE C
SET C.CreditCardNumber = 'X'
FROM SalesLT.Customer AS C
WHERE EXISTS (
    SELECT 1
    FROM SalesLT.SalesOrderHeader AS SOH
    WHERE SOH.CustomerID = C.CustomerID
      AND SOH.CreditCardApprovalCode = 'APPROVED_TEST'
);

SELECT C.CustomerID, C.FirstName, C.LastName, C.CreditCardNumber
FROM SalesLT.Customer AS C
WHERE C.CreditCardNumber = 'X';

ALTER TABLE SalesLT.Customer DROP COLUMN CreditCardNumber;
UPDATE SalesLT.SalesOrderHeader SET CreditCardApprovalCode = NULL WHERE CreditCardApprovalCode = 'APPROVED_TEST';