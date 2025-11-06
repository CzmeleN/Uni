DROP TABLE IF EXISTS Specimens;
DROP TABLE IF EXISTS Books;
GO

CREATE TABLE Books (
    BookID INT PRIMARY KEY,
    Title VARCHAR(100)
);

CREATE TABLE Specimens (
    SpecimenID INT PRIMARY KEY,
    BookID INT REFERENCES Books(BookID),
    Condition VARCHAR(10)
);
GO

INSERT INTO Books VALUES (1, 'Zemsta'), (2, '1984');
GO

CREATE TRIGGER trg_Specimen_CheckMaxFive
ON Specimens
AFTER INSERT, UPDATE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM Specimens s
        WHERE s.BookID IN (SELECT DISTINCT BookID FROM inserted)
        GROUP BY s.BookID
        HAVING COUNT(s.SpecimenID) > 5
    )
    BEGIN
        RAISERROR ('Book cant have more than five specimens. Denied', 16, 1);
        ROLLBACK TRANSACTION;
    END;
END;
GO

INSERT INTO Specimens VALUES
(1, 1, 'Good'),
(2, 1, 'Like new'),
(3, 1, 'New'),
(4, 1, 'Poor'),
(5, 1, 'Good');
SELECT BookID, COUNT(*) AS SpecimenCount FROM Specimens GROUP BY BookID;
GO

BEGIN TRY
    INSERT INTO Specimens VALUES (6, 1, 'New');
END TRY
BEGIN CATCH
    PRINT 'Catch: ' + ERROR_MESSAGE();
END CATCH;
GO

SELECT BookID, COUNT(*) AS SpecimenCount FROM Specimens GROUP BY BookID;
GO