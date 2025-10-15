# zad5

## definicje
- pliki zwykłe - z danymi
- katalogi
- urządzenia - pliki specjalne reprezentujące sprzęt, chr obsługuje znak po znaku, a blk na blokach danych
- gniazda - punkty końcowe komunikacji siecią, unix jest między procesami
- potoki - jednokierunkowe kanały komunikacji międzyprocesowej, fifo - nazwane w systemie plikóœ, pipe - nienazwane w kernelu

## zasoby plikopodobne firefoxa
- są to obiekty, które nie są na dysku, ale mamy do nich interfejs jak do plików - udostępnia open, read, write, close

```
pgrep zen-bin
lsof -p [PID]
```

### kolumny:
- command - nazwa procesu
- pid
- user - właściciel
- fd - deskryptor piku - numer, lub np. cwd - current katalog, mem - mapowany w pamięci, del - usunięty, txt - wykonwywalny
- type - reg - plik, dir - katalog, ipv4/6 - gniazdo sieciowe, chr - urządzenie znakowe, blk - blokowe, fifo/pipe - potoki komunikacji
- device - block device, w którym jest plik (major,minor)
- size/off - rozmiar/ilość danych w buforze dla sieciowych
- node - nr węzła w systemie plików, każdy w partycji ma swój unikalny inode dla jądra
- name

## zobaczenie połączenia sieciowego
```
lsof -p [PID] -i > before
> after
diff -u 
```
