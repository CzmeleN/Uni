--UPDATE SalesLT.Product SET ProductCategoryID = 1 WHERE ProductID = 680;

SELECT
    PC.Name AS CategoryName,
    P.Name AS ProductName
FROM SalesLT.Product AS P
JOIN SalesLT.ProductCategory AS PC ON P.ProductCategoryID = PC.ProductCategoryID
WHERE P.ProductCategoryID IN ( -- znajdujemy najpierw wszystkich rodziców dla innych
    SELECT DISTINCT ParentProductCategoryID
    FROM SalesLT.ProductCategory
    WHERE ParentProductCategoryID IS NOT NULL
);

UPDATE SalesLT.Product SET ProductCategoryID = 18 WHERE ProductID = 680;