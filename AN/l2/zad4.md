# zad4

## 1991 rok, w Arabii Saudyjskiej fail pocisku Patriot
- rakieta wystrzelona przez stany mająca za zadanie przechwycić jedną z rakiet Iraku, nie podołała z wyzwaniem, co doprowadziło do uderzenia rakiety Scud w baraki zabijając 28 żołnierzy i 100 innych zostało rannych
- problem leżał w tym, że obliczenia przy uruchomieniu były niedokładnie przez błąd obliczeniowy
- dokładniej, czas liczony co 1/10 sekundy przez zegar był zapisany na 24 bitach
- 1/10 nie ma skończonej reprezentacji binarnej, a 24-bitowy rejestr ucinał za każdym razem jej rozwinięcie, co prowadziło do błędu ok. 0.000000095 z każdym dodaniem
- na okresie 100 godzin daje to 0.34 s błędu, a rakieta leciała z prędkością 1676 m/s, co daje pół kilometra przez ten czas
- było to wystarczająco, żeby uciekła z pola śledzenia Patriota, co umożliwiło jej lot do celu
