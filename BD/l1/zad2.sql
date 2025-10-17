SELECT M.Name AS ModelName, COUNT(P.ProductID) AS NumberOfProducts
FROM SalesLT.ProductModel AS M
JOIN SalesLT.Product AS P ON M.ProductModelID = P.ProductModelID
GROUP BY M.ProductModelID, M.Name -- samo name niedobre bo nazwy mogą nie być unikalne
HAVING COUNT(P.ProductID) > 1;