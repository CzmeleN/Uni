# zad3

## def

- Zarządzanie zadaniami (Job Control): Jest to funkcja powłoki systemowej (np. bash), która pozwala użytkownikowi na zarządzanie wieloma procesami (zadaniami) w ramach jednej sesji terminala. Obejmuje to możliwość:
  - Uruchamiania zadań w tle (np. sleep 100 &).
  - Zatrzymywania (zawieszania) zadań działających na pierwszym planie (zazwyczaj za pomocą Ctrl+Z).
  - Wznawiania zatrzymanych zadań na pierwszym planie (fg) lub w tle (bg).
  - Listowania wszystkich zadań (jobs).

- Edycja wiersza (Line Editing): Odnosi się do funkcji terminala (w trybie kanonicznym), które pozwalają użytkownikowi modyfikować bieżącą linię poleceń przed jej wysłaniem do aplikacji (np. przed naciśnięciem Enter). Obejmuje to usuwanie znaków (Backspace), kasowanie całej linii (Ctrl+U) czy kasowanie słów (Ctrl+W).

- Rozmiar okna (Window Size): Jest to atrybut (właściwość) terminala, który przechowuje jego aktualne wymiary, wyrażone najczęściej w liczbie wierszy (rows) i kolumn (columns). Jest to kluczowa informacja dla programów pełnoekranowych, takich jak edytory (vi, nano) czy pagery (less), aby wiedziały, jak poprawnie renderować swój interfejs.

## co jest czym?
```
stty -a
```

- zamienia na sygnały związane z zarządzaniem zadania:
  - intr ^C - SIGINT
  - quit ^\ - SIGQUIT
  - susp ^Z - SIGTSTP

- służą do edycji wiersza:
  - erase ^? - backspace
  - kill ^U - dd
  - werase ^W - db
  - rprnt ^R - reprint linii bufora

## sygnał informujący o zmianie rozmiaru okna
- jest to SIGWINCH
- nowy wczytamy przez ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  zwróci nam (sys/ioctl.h -> bits/ioctl-types.h)
  struct winsize
    {
      unsigned short int ws_row;
      unsigned short int ws_col;
      unsigned short int ws_xpixel;
      unsigned short int ws_ypixel;
    };
