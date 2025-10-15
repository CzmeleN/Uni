# zad4

## znajdźmy pid X serwera
```
pgrep Xwayland
pmap -x [id]
```

## kolumny:
- adres
- kilobajty (rozmiar danego regionu)
- tryb/uprawnienia (s - shared)
- odwzorowanie - co znajduje się w danym regionie

## jak znaleźć/zidentyfikować powyższe:
- stos - będzie podpisane [ stos ]
- sterta - będzie też [ anon ], bo zarządza nią glibc i malloc/calloc, więc nie mamy podpisane jako [ sterta ]
- segmenty programu - będzie mapping na Xwayland - może być kodu/danych (kodu to r-x-- danych r---- lub rw---), kodu - instrukcje, danych - zmienne globalne i statyczne
- pamięć anonimowa - pamięć niepowiązana z żadnym plikiem na dysku [ anon ]
- pliki odwzorowane w pamięć - tam, gdzie mapping nie jest na Xwayland, głównie biblioteki współdzielone, zawartość pliku jes tmapowana bezpośrednio do przestrzeni adresowej procesu
