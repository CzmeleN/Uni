# zad 5

## co robimy

1.
```
sleep 1000
// w drugim
sudo strace -e trace=signal -p (pidof sleep)
Ctrl+Z // SIGTSTP
bg // SIGCONT
```

2.
```
xterm -e 'bash -i'
find /
Ctrl+S
Ctrl+Q
// i tak dalej
```

find nie został zamrożony, a przepływ danych z bufora jądra do terminala
VSTOP, VSTART - znaki sterujące XON/XOFF - jądro blokuje write() finda 

3.
```
strace -e trace=signal cat - &
jobs
kill %1 // job 1
```

zadanie drugoplanowe nie może czytać z terminala sterującego, gdy próbował read(), dostał SIGTTIN

4.
```
xterm -e 'bash -i'
cat /etc/shells &
stty tostop
cat /etc/shells &
```

tostop zabrania procesom w tle pisać na terminal -tostop zezwala, wyśle SIGTTOU

5.
```
cat
Ctrl+C
// widzimy ^C
stty -echoctl
// nie widzimy
```

echoctl nakazuje sterownikami terminala potwierdzenie znaków sterujących wizualnie
