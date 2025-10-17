-- SELECT
--     SOH.SalesOrderID,
--     SOH.SalesOrderNumber,
--     SOH.PurchaseOrderNumber,
--     SUM(SOD.OrderQty * SOD.UnitPrice) AS TotalWithoutDiscount,
--     SUM(SOD.LineTotal) AS FinalOrderAmount
-- FROM SalesLT.SalesOrderHeader AS SOH
-- JOIN SalesLT.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
-- GROUP BY SOH.SalesOrderID, SOH.SalesOrderNumber, SOH.PurchaseOrderNumber
-- ORDER BY SOH.SalesOrderID;

-- B
WITH OrderSummary AS (
    SELECT -- z A
        SOH.SalesOrderID,
        SOH.SalesOrderNumber,
        SOH.PurchaseOrderNumber,
        SUM(SOD.OrderQty * SOD.UnitPrice) AS TotalWithoutDiscount,
        SUM(SOD.LineTotal) AS FinalOrderAmount
    FROM SalesLT.SalesOrderHeader AS SOH
    JOIN SalesLT.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
    GROUP BY SOH.SalesOrderID, SOH.SalesOrderNumber, SOH.PurchaseOrderNumber
)
SELECT TOP 5
    SalesOrderID,
    SalesOrderNumber,
    PurchaseOrderNumber,
    TotalWithoutDiscount,
    FinalOrderAmount,
    (TotalWithoutDiscount - FinalOrderAmount) AS TotalDiscountAmount
FROM OrderSummary
ORDER BY TotalDiscountAmount DESC;