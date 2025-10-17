SELECT DISTINCT A.City
FROM SalesLT.SalesOrderHeader AS SOH
JOIN SalesLT.Address AS A ON SOH.ShipToAddressID = A.AddressID
ORDER BY A.City;