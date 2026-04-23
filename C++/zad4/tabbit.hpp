#pragma once

#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <stdint.h>

class tabbit {
    using slowo = uint64_t; // komórka w tablicy

    static const int jednostka; // ile bitów w słowie

    friend std::istream& operator >> (std::istream &we, tabbit &tb);
    friend std::ostream& operator << (std::ostream &wy, const tabbit &tb);

    // klasa pomocnicza do adresowania bitów
    class ref {
        tabbit &tb;
        int id;
    public:
        ref(tabbit &t, int i);
        ref& operator=(bool b);
        ref& operator=(const ref& other);
        operator bool() const;
    };

    bool czytaj(int i) const; // odczyt bitu
    void pisz(int i, bool b); // zapis bitu

    void clean();
    int count_words(int bits);

protected:
    int dl; // liczba bitów
    slowo *tab; // tablica bitów

public:
    // wyzerowana tablica bitow [0...rozm]
    explicit tabbit(int rozm = 1);
    // tablica 64 bitów zainicjalizowana wzorcem
    explicit tabbit(slowo tb);

    tabbit(std::initializer_list<bool> lista);

    // destruktor
    ~tabbit();
    // konstruktor kopiujący
    tabbit(const tabbit &tb);
    // konstruktor przenoszący
    tabbit(tabbit &&tb);

    // przypisanie kopiujące
    tabbit& operator = (const tabbit &tb);
    // przypisanie przenoszące
    tabbit& operator = (tabbit &&tb);

    // indeksowanie dla stałych tablic bitowych
    bool operator [] (int i) const;
    // indeksowanie dla zwykłych tablic bitowych
    ref operator [] (int i);

    // ile bitów w tablicy
    inline int rozmiar() const;

    // operatory bitowe: | i |=, & i &=, ^ i ^= oraz !
    friend tabbit operator | (const tabbit &tb1, const tabbit &tb2);
    friend tabbit operator & (const tabbit &tb1, const tabbit &tb2);
    friend tabbit operator ^ (const tabbit &tb1, const tabbit &tb2);

    tabbit& operator |= (const tabbit &tb);
    tabbit& operator &= (const tabbit &tb);
    tabbit& operator ^= (const tabbit &tb);
    tabbit operator ! () const;
};
