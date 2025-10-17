SELECT
    A.City,
    COUNT(DISTINCT C.CustomerID) AS NumberOfCustomers,
    COUNT(DISTINCT C.SalesPerson) AS NumberOfSalesPersons
FROM SalesLT.Address AS A
JOIN SalesLT.CustomerAddress AS CA ON A.AddressID = CA.AddressID
JOIN SalesLT.Customer AS C ON CA.CustomerID = C.CustomerID
GROUP BY A.City
ORDER BY A.City;