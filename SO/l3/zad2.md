# zad2

## def
- Tryb kanoniczny (Canonical Mode): Jest to domyślny tryb pracy sterownika terminala (TTY) w systemach Unix/Linux. Jego główną cechą jest buforowanie liniowe. Oznacza to, że sterownik terminala (a nie aplikacja, np. bash) zbiera znaki w wewnętrznym buforze, pozwalając użytkownikowi na edycję tej linii (np. używając Backspace czy Ctrl+U) zanim linia zostanie wysłana do programu. Aplikacja, która wywołała funkcję read(), "śpi" i nie otrzymuje żadnych danych, dopóki użytkownik nie naciśnie klawisza Enter (lub innego znaku końca linii, jak EOL czy EOF). Kontrolowane przez flagę ICANON w polu c_lflag.

- Kolejka wejściowa (Input Queue): Jest to bufor w jądrze systemu operacyjnego, zarządzany przez sterownik terminala. Trafiają do niego "surowe" znaki wpisywane przez użytkownika na klawiaturze. To tutaj dane czekają na przetworzenie przez sterownik (np. sprawdzenie, czy to znak INTR jak Ctrl+C) i ewentualne przekazanie do bufora linii (w trybie kanonicznym) lub bezpośrednio do aplikacji (w trybie niekanonicznym). W sekcji "Input Processing and Reading Data".

- Kolejka wyjściowa (Output Queue): Jest to analogiczny bufor w jądrze dla danych wysyłanych do terminala. Gdy program (np. ls) wywołuje funkcję write(), aby coś wydrukować, dane te nie trafiają natychmiast na ekran. Są one umieszczane w kolejce wyjściowej, a sterownik terminala w wolnej chwili pobiera je i wysyła do emulatora terminala w celu wyświetlenia. W sekcji "Writing Data and Output Processing".

## Jak zachowuje się sterownik terminala działającego w trybie kanonicznym?
- "Canonical Mode Input Processing":
  - "terminal input is processed in units of lines" (wejście jest przetwarzane w jednostkach linii).
  - "A line is delimited by a newline \n character, an end-of-file (EOF) character, or an end-of-line (EOL) character" (linia jest oddzielona znakiem nowej linii, końca pliku lub końca linii).
  - "a read request will not return until an entire line has been typed" (wywołanie read() nie wróci, dopóki cała linia nie zostanie wpisana).
  - "Erase and kill processing occur" (zachodzi przetwarzanie kasowania (ERASE - Backspace) i czyszczenia linii (KILL - Ctrl+U)).

- W trybie kanonicznym (gdy flaga ICANON jest ustawiona), sterownik terminala aktywnie zarządza wprowadzaniem danych. Gromadzi on znaki w wewnętrznym buforze liniowym. Jeśli użytkownik naciśnie znak ERASE (zazwyczaj Backspace), sterownik usuwa ostatni znak z tego bufora. Jeśli naciśnie KILL (zazwyczaj Ctrl+U), sterownik czyści cały bufor. Aplikacja, która czeka na dane (wywołała read()), nie dostaje nic aż do momentu, gdy użytkownik naciśnie Enter (\n). Dopiero wtedy cała, zedytowana zawartość bufora liniowego jest udostępniana aplikacji.

## W jaki sposób przetwarza znaki wchodzące do kol wej/wyj (zdj2)
1. Kolejka Wejściowa (Input Queue)
Serce trybu kanonicznego

  - Wejście: Gdy użytkownik naciska klawisz (np. a), urządzenie (klawiatura) wysyła znak. Staje się on "next character read from device" (następny znak odczytany z urządzenia) i trafia do kolejki wejściowej.
  - Przetwarzanie (Logika sterownika TTY): Tutaj dzieje się cała magia, której diagram nie pokazuje wprost, ale która jest opisana w termios(4):
    1. Sprawdzenie ISIG: Czy ten znak to Ctrl+C (VINTR) lub Ctrl+Z (VSUSP)?
       - TAK: Znak jest wyrzucany (nie trafia do bufora). Zamiast tego do procesu wysyłany jest odpowiedni sygnał (SIGINT lub SIGTSTP).
    2. Sprawdzenie ICANON (Tryb Kanoniczny): Czy to znak edycji, np. Backspace (VERASE) lub Ctrl+U (VKILL)?
      - TAK: Znak jest wyrzucany. Sterownik modyfikuje swoją wewnętrzną linię buforową (która jest częścią input queue), usuwając ostatni znak lub całą linię.
    3. Sprawdzenie ICANON (Koniec linii): Czy to Enter (\n), EOF (Ctrl+D) lub EOL?
      - TAK: Cała zawartość linii buforowej jest oznaczana jako "gotowa do odczytu". Proces, który czekał na read(), zostaje obudzony.
    4. Jeśli to zwykły znak: (np. a, b, c) Znak jest dodawany do linii buforowej.
  - Echo: Jak pokazuje strzałka "if echo enabled" (jeśli ECHO jest włączone), kopia znaku (lub odpowiednia sekwencja kasująca dla VERASE) jest natychmiast wysyłana do kolejki wyjściowej, aby użytkownik zobaczył, co pisze.

  - Wyjście: Gdy linia jest gotowa (po naciśnięciu Enter), staje się ona "next character read by process" (następny znak czytany przez proces). Dopiero wtedy aplikacja (np. cat, bash) otrzymuje dane.

2. Kolejka Wyjściowa (Output Queue)
Jest ona znacznie prostsza i ma dwa źródła:

  1. Od procesu: Gdy proces (np. ls, echo) chce coś wyświetlić, wywołuje write(). Dane te stają się "next character written by process" (następny znak zapisany przez proces) i trafiają do tej kolejki.

  2. Z Echa: Jak opisano wyżej, znaki wpisywane przez użytkownika również tu trafiają, aby mogły pojawić się na ekranie.

  - Wyjście: Sterownik TTY w wolnej chwili pobiera znaki z tej kolejki jako "next character to transmit to device" (następny znak do przesłania do urządzenia) i wysyła je do emulatora terminala (monitora).

## Jak konfigurację terminala powinien zmienić program sterujący na czas wpisania hasła?
- Nie może być widoczne
- Program do wpisywania hasła (np. login lub sudo) musi tymczasowo wyłączyć flagę ECHO w strukturze termios (w polu c_lflag).
  - Pobierz obecne ustawienia terminala (funkcją tcgetattr()).
  - Stwórz kopię ustawień i zmodyfikuj ją, wyłączając bit ECHO (np. settings.c_lflag &= ~ECHO;).
  - Zastosuj nowe ustawienia (funkcją tcsetattr()).
  - Przeczytaj hasło od użytkownika (nadal w trybie kanonicznym, więc read() zaczeka na Enter).
  - Przywróć oryginalne ustawienia (te zapisane w kroku 1), aby terminal znowu działał normalnie.

## Czemu edytory jak vi konfigurują sterownik terminala do pracy w trybie niekanonicznym?
- Edytory pełnoekranowe, takie jak vi, nie mogą pracować w trybie kanonicznym, ponieważ tryb ten wymaga naciśnięcia Enter, aby aplikacja otrzymała jakiekolwiek dane. vi musi natychmiast przechwytywać każde naciśnięcie klawisza, aby móc na nie zareagować.

Dlatego vi przełącza terminal w tryb niekanoniczny (wyłącza flagę ICANON w c_lflag). W tym trybie:
  - Buforowanie liniowe jest wyłączone.
  - Znaki edycyjne (Backspace) i sygnałowe (Ctrl+C) nie są interpretowane przez sterownik, ale przekazywane do aplikacji jako surowe bajty.
  - vi zazwyczaj ustawia VMIN = 1 i VTIME = 0. Oznacza to (zgodnie z "Case B" w podręczniku), że wywołanie read() będzie czekać, aż pojawi się dokładnie jeden znak, i natychmiast go zwróci.

To pozwala vi czytać jeden znak na raz, interpretować go jako polecenie (np. "przesuń kursor") lub jako tekst do wstawienia, i samodzielnie odświeżać ekran.
