# zad1

## def
- Proces osierocony (Orphaned Process): Jest to proces, którego proces macierzysty (rodzic) zakończył działanie. Adoptuje go init i reapuje.
- Zadanie drugoplanowe (Background Job/Process): W powłoce systemowej jest to proces lub grupa procesów uruchomiona ze znakiem &. Takie zadanie nie blokuje terminala — powłoka natychmiast wraca do znaku zachęty i jest gotowa na przyjęcie kolejnych poleceń, podczas gdy zadanie drugoplanowe wykonuje się "w tle".
- SIGKILL: Jest to jeden z sygnałów, które można wysłać do procesu. SIGKILL (o numerze 9) jest sygnałem "ostatecznym". Nie może on zostać przechwycony, zablokowany ani zignorowany przez proces. Powoduje natychmiastowe i bezwarunkowe zakończenie (zabicie) procesu przez jądro systemu operacyjnego.
- Sesja: Jest to kolekcja jednej lub więcej grup procesów. Sesja jest mechanizmem służącym do grupowania powiązanych ze sobą procesów, zwykle tych uruchomionych przez użytkownika podczas jednej "sesji logowania" na danym terminalu.
- Lider sesji (Session Leader): Jest to proces, który utworzył nową sesję. Zazwyczaj jest to pierwsza powłoka uruchomiona po zalogowaniu się na terminalu. PID lidera sesji jest taki sam jak identyfikator sesji (SID).
- Terminal sterujący (Controlling Terminal): Jest to terminal (fizyczny, jak tty1, lub pseudo-terminal, jak /dev/pts/1 w przypadku xterm) powiązany z daną sesją. Terminal sterujący zarządza wejściem i wyjściem dla procesów pierwszoplanowych oraz jest mechanizmem, przez który jądro wysyła sygnały do procesów.

## 1. stworzenie sieroty
```
xrdb -merge ~/.Xresources
xterm -e 'bash -i' &
// w xtermie
sleep 1000 &
// kitty
pstree
kill -9 (pidof bash)
pstree
// ewentualnie
ps -o pid,ppid,comm -p (pidof sleep)
```

## 2. utrata terminalu sterującego sesją
```
xterm -e 'bash -i'
// w xterm
sleep 1000 &
// kitty
sudo strace -e trace=signal -p (pidof bash)
(of sleep) w nowym terminalu
kill -9 (pidof xterm)
```

- widzimy, że dostanie sighup
