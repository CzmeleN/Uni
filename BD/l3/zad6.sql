IF OBJECT_ID('brands', 'U') IS NOT NULL
    DROP TABLE brands
GO

CREATE TABLE brands (
    brand_id INT IDENTITY PRIMARY KEY,
    brand_name VARCHAR(255) NOT NULL UNIQUE
);
GO

IF OBJECT_ID('brand_approvals', 'U') IS NOT NULL
    DROP TABLE brand_approvals
GO

CREATE TABLE brand_approvals(
    brand_id INT IDENTITY PRIMARY KEY,
    brand_name VARCHAR(255) NOT NULL
);
GO

CREATE OR ALTER VIEW vw_brands 
AS
SELECT
    brand_name,
    'Approved' approval_status
FROM
    brands
UNION
SELECT
    brand_name,
    'Pending Approval' approval_status
FROM
    brand_approvals;
GO

CREATE OR ALTER TRIGGER trg_vw_brands 
ON vw_brands
INSTEAD OF INSERT
AS
BEGIN
    SET NOCOUNT ON;
    INSERT INTO brand_approvals ( 
        brand_name
    )
    SELECT
        i.brand_name
    FROM
        inserted i
    WHERE
        i.brand_name NOT IN (
            SELECT 
                brand_name
            FROM
                brands
        );
END
GO

INSERT INTO vw_brands(brand_name)
VALUES('Eddy Merckx');

SELECT
	brand_name,
	approval_status
FROM
	vw_brands;

SELECT 
	*
FROM 
	brand_approvals;