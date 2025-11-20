# zad6

załóżmy że mamy 1M zamówień, ale tylko 1K jest otwarte, reszta to archiwum

```SQL
SELECT ID, KlientID FROM Zamowienia WHERE Status = 'Owarte';

CREATE NONCLUSTERED INDEX IX_Zamowienia_Owarte
ON Zamowienia (KlientID)
WHERE Status = 'Owarte';
```

indeks filtrowany to indeks z WHERE, jest mniejszy i szybszy bo indeksuje część wierszy

plan wykonania użyje index seek jeśi zapytamy o otwarte, a jeśli o zamknięte to zignoruje ten indeks/wykona inny jeśli będzie
