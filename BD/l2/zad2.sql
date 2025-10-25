DROP TABLE IF EXISTS firstnames
DROP TABLE IF EXISTS lastnames
DROP TABLE IF EXISTS fldata

CREATE TABLE firstnames (id INT IDENTITY PRIMARY KEY, firstname VARCHAR(50));
CREATE TABLE lastnames (id INT IDENTITY PRIMARY KEY, lastname VARCHAR(50));
CREATE TABLE fldata (
    firstname VARCHAR(50),
    lastname VARCHAR(50),
    CONSTRAINT PK_fldata PRIMARY KEY (firstname, lastname)
);
GO

INSERT INTO firstnames (firstname) VALUES ('Jan'), ('Anna'), ('Piotr'), ('Maria');
INSERT INTO lastnames (lastname) VALUES ('Kowalski'), ('Nowak'), ('Wiśniewski');
GO

CREATE OR ALTER PROCEDURE GenerujDane @n INT
AS
BEGIN
    DECLARE @max_pairs INT;
    SELECT @max_pairs = (SELECT COUNT(*) FROM firstnames) * (SELECT COUNT_BIG(*) FROM lastnames);

    IF @n > @max_pairs
    BEGIN
        THROW 50001, 'n jest większe niż maksymalna liczba par', 1;
        RETURN;
    END;

    TRUNCATE TABLE fldata;

    INSERT INTO fldata (firstname, lastname)
    SELECT TOP (@n)
        f.firstname,
        l.lastname
    FROM
        firstnames AS f
    CROSS JOIN
        lastnames AS l
    ORDER BY
        NEWID();
END;
GO

EXEC GenerujDane @n = 5;
SELECT * FROM fldata;

EXEC GenerujDane @n = 2;
SELECT * FROM fldata;

-- mamy max 12
--EXEC dbo.sp_GenerujDane @n = 15;
