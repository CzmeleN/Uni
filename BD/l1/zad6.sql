SELECT
    C.FirstName,
    C.LastName,
    SUM(SOD.OrderQty * SOD.UnitPrice - SOD.LineTotal) AS TotalSavings
FROM SalesLT.Customer AS C
JOIN SalesLT.SalesOrderHeader AS SOH ON C.CustomerID = SOH.CustomerID
JOIN SalesLT.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
WHERE SOD.UnitPriceDiscount > 0
GROUP BY C.FirstName, C.LastName
ORDER BY TotalSavings DESC;