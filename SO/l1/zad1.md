# zad1

## definicje
- rodzic-dziecko - nowy proces jest tworzony fork(), dziecko dziedziczy uprawnienia, env vars, otwarte pliki, ale ma nowe PID
- wątki jądra - procesy, które działają w przestrzeni jądra i odpowiadają za zadania systemowe (np. obsługa przerwań, zarządzanie pamięcią, I/O)
- hierarchia procesów - struktura powstające w wyniku tych włąśnie relacji

## co zwróci nam ps ...
```
ps -eo user,pid,ppid,pgid,tid,pri,stat,wchan,cmd
```
- USER - nazwa użytkownika - właściciela procesu - konto, z którego uprawieniami proces jest wykonywany
- PID - id procesu, unikalny numer każdego procesu 
- PPID - id rodzica - id procesu, który utworzył ten proces
- PGID - id grupy procesów, czyli takiej która pozwala na wysłanie procesów do całej grupy naraz
- TID - id wątku - unikalny dla wielowątkowych, PID dla jedno
- PRI - priorytet procesu - niżej - wyższy
- STAT - stan procesu, R - działą, S - śpi, Z - zombie, I - bezczynny
- WCHAN - miejsce w jądrze, gdzie śpi
- CMD - polecenie, które uruchomiło proces w kwadratowych - wątki jądra

## kto jest rodzicem procesu init?
- PPID = 0 oznacza, że nie ma rodzica - utworzony prez kernel

## które z zadań są wątkami jądra
- są to zadania w nawiasach kwadratowych

## które z zadań są wątkami?
```
pstree
```

- wątkami są zadania wątki są w {}
