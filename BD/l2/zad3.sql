CREATE OR ALTER PROCEDURE dbo.DodajCzytelnika
    @PESEL CHAR(11),
    @Nazwisko VARCHAR(30),
    @Miasto VARCHAR(30),
    @Data_Urodzenia_str VARCHAR(10)
AS
BEGIN
    DECLARE @Data_Urodzenia DATE;

    IF LEN(@PESEL) <> 11 OR @PESEL LIKE '%[^0-9]%'
    BEGIN
        THROW 50001, 'PESEL musi mieć 11 cyfr', 1;
        RETURN;
    END;

    -- dosłownie porównuje znaki po znaku (czy => 'A' <= 'Z')
    IF LEN(@Nazwisko) < 2 OR @Nazwisko COLLATE Latin1_General_100_BIN2 NOT LIKE '[A-Z]%'
    BEGIN
        THROW 50002, 'nazwisko musi zaczynać się wielką literą i mieć co najmniej 2 znaki', 1;
        RETURN;
    END;

    SET @Data_Urodzenia = TRY_CONVERT(DATE, @Data_Urodzenia_str, 105); -- 105 dd-mm-rrrr

    IF @Data_Urodzenia IS NULL
    BEGIN
        THROW 50003, 'data nie jest w formacie dd-mm-rrrr', 1;
        RETURN;
    END;
    
    IF @Data_Urodzenia > GETDATE()
    BEGIN
        THROW 50004, 'data urodzenia nie może być z przyszłości', 1;
        RETURN;
    END;

    INSERT INTO Czytelnik (PESEL, Nazwisko, Miasto, Data_Urodzenia)
    VALUES (@PESEL, @Nazwisko, @Miasto, @Data_Urodzenia);
    
    PRINT 'dodano pomyslnie';
END;
GO

DELETE FROM Czytelnik WHERE PESEL = '90010112345'
DELETE FROM Czytelnik WHERE PESEL = '91010112345'

-- można też ..Czytelnika 'PESEL', 'NAZWISKO', ... pozycyjnie
EXEC dbo.DodajCzytelnika @PESEL = '90010112345', @Nazwisko = 'Malinowski', @Miasto = 'Wrocław', @Data_Urodzenia_str = '01-01-1990';

-- bł nazwiska
EXEC dbo.DodajCzytelnika @PESEL = '91010112345', @Nazwisko = 'Kowalski', @Miasto = 'Wrocław', @Data_Urodzenia_str = '01-01-1991';

-- bł pesel
-- EXEC dbo.sp_DodajCzytelnika @PESEL = '9201011234A', @Nazwisko = 'Bąk', @Miasto = 'Wrocław', @Data_Urodzenia_str = '01-01-1992';

-- bł data
-- EXEC dbo.sp_DodajCzytelnika @PESEL = '92010112345', @Nazwisko = 'Wiśniewski', @Miasto = 'Wrocław', @Data_Urodzenia_str = '01-01-2026';
