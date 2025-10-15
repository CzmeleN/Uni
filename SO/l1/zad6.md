# zad6

## definicje:
- czas wykonania:
  - real - czas rzeczywisty
  - user - wykonywanie kodu programu w trybie użytkownika
  - sys - wykonywanie kodu jądra systemu w imieniu programu (np. I/O)

## czemu user + sys:
```
time find /usr "*.so"
```

- nie jest równa real - proces nie miał cały czas dostępu do cpu, mógł czekać na I/O na plikach lub wywalił go scheduler
- może być większa od real - w programach wielowątkowych na systemie wielordzeniowym, np. na 2 rdzeniach zużyje 2 sekundy cpu i skończy się w sekundę

```
dd if=/dev/zero of=bigfile bs=1M count=1024    
time xz -T0 -k bigfile
```

kompresja, -T0 - tyle wątków ile można, -k - zostawia og plik

## ograniczenie czasu procesów potomnych powłoki
```
ulimit -t 1 yes
```

ogranicza po usr + sys
```
```
