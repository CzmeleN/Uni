# zad3

## definicje
- argumenty programu - parametry przekazane przy uruchomieniu
- zmienne środowiskowe - zbiór par klucz-wartość dziedziczonych od rodzica, definiujących jego środowisko

## do czego służy proc(5) na linuxie?
- wirtualny system plików, tzn. że nie istnieje na dysku ale jest tworzony przez kernel w ramie, gdy próbujemy uzyskać do niego dostęp, służy jako interfejs do wew. stuktur danych jądra, pozwalając na monitorowanie i modyfikowanie stanu systemu

## plik z argumentami i envami
```
cat /proc/id/cmdline
cat /proc/id/environ
```

## znaczenie pól
```
cat /proc/id/status
```

- Uid - id użytkownika
- Gid - id grupy głównej
- Groups - ids grup dodatkowych
- VmPeak - szczytowe użycie pamięci wirtualnej
- VmSize - aktualne
- VmRSS - ilość RAM jaką zajmuje
- Threads - liczba wątków w procesie
- voluntary_ctxt_switches - liczba dobrowolnych przełączeń kontekstu - np. gdy proces sam oddaje procesor bo czeka na dane z pliku
- nonvoluntary_ctxt_switches - liczba niedobrowolnych... - gdy scheduler kernela odbiera procesor procesorowi (np. skończył mu się czas) i oddaje innemu procesowi
