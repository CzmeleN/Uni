# zad4

## def
- Urządzenie terminala (Terminal Emulator): Jest to program (taki jak xterm, gnome-terminal, konsole) udający stary, fizyczny terminal (np. VT100). Jego zadaniem jest:
  1. Wyjście: Odbierać strumień bajtów od sterownika TTY. Zwykłe znaki (jak 'a', 'b', 'c') wyświetla na ekranie.
  2. Wyjście (Interpretacja): Rozpoznawać specjalne sekwencje sterujące (ANSI escape codes) i interpretować je jako polecenia, np. "zmień kolor tekstu", "przesuń kursor", "wyczyść ekran".
  3. Wejście: Przechwytywać zdarzenia od użytkownika (np. naciśnięcie klawisza A, klawisza strzałki w górę, kliknięcie myszką) i tłumaczyć je na sekwencje bajtów, które następnie wysyła do sterownika TTY.

- Znaki i sekwencje sterujące (ANSI Escape Codes): Jest to standard komunikacji z terminalem. Pozwala programom kontrolować nie tylko co jest wyświetlane, ale też jak i gdzie.
  - Znaki sterujące: Pojedyncze znaki, jak \n (nowa linia), \t (tabulacja), \a (dzwonek systemowy, "alert").
  - Sekwencje sterujące: Złożone, wielobajtowe polecenia. Większość z nich zaczyna się od znaku ESC (kod ASCII \x1b).

- CSI (Control Sequence Introducer): Najważniejszy typ sekwencji sterującej. Zaczyna się od ESC a zaraz po nim [ (czyli \x1b[). Służy do wprowadzania poleceń terminala, takich jak:
  - \x1b[31m - Ustaw kolor tekstu na czerwony.
  - \x1b[0m - Zresetuj wszystkie atrybuty (kolor, pogrubienie).
  - \x1b[2J - Wyczyść cały ekran.
  - \x1b[5;10H - Przesuń kursor do wiersza 5, kolumny 10.

## prezentacja działanie znaków sterujących i sekwencji csi
```
echo -e "test\n\ttest"
echo -e "normalny, \x1b[31mczerwony\x1b[0m, \x1b[1mpogrubiony\x1b[0m, \x1b[4mpodkreślony\x1b[0m normalny"
echo -e "powrót do tej linii \x1b[1A i jej nadpisanie \x1b[2K nowy tekst"
```

## cat i sprawdź f1, strzałka w górę, czemu inne niż bash?
- bo cat jest w trybie kanonicznym, a powłowa niekanoniczny, cata obsługuje sterownik TTY (kernel) i nie obsługuje tych znaków, odsyła je do terminala a on interpretuje, powłokę obsługuje powłoka, wyłącza domyślnie obsługę tty i sam czyta bajty z klawiatury
  - bash jest programem "inteligentnym". Aktywnie przejmuje kontrolę nad terminalem (przełącza go w tryb niekanoniczny) i samodzielnie interpretuje sekwencje sterujące wysyłane przez klawiaturę, aby zaimplementować zaawansowane funkcje, jak historia poleceń czy autouzupełnianie.
  - cat jest programem "głupim". Działa w domyślnym trybie kanonicznym, polegając na prostej edycji linii przez sterownik TTY. Nie potrafi (i nie ma) interpretować sekwencji sterujących z klawiatury – są one dla niego po prostu danymi, które należy odczytać i odesłać.
