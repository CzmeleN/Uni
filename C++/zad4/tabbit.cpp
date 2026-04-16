#include "tabbit.hpp"
#include <climits>

const int tabbit::jednostka = sizeof(tabbit::slowo) * CHAR_BIT;

std::ostream& operator<<(std::ostream &wy, const tabbit &tb) {
    for (int i = tb.dl - 1; i >= 0; --i) wy << tb.czytaj(i);

    return wy;
}

std::istream& operator>>(std::istream &we, tabbit &tb) {
    std::string s;
    we >> s;

    int to_read = std::min((int)s.length(), tb.dl);

    for (int i = 0; i < to_read; ++i) tb.pisz(i, s[i] == '1');
    for (int i = to_read; i < tb.dl; ++i) tb.pisz(i, false);

    return we;
}

tabbit::ref::ref(tabbit& t, int i) : tb(t), id(i) {}

tabbit::ref& tabbit::ref::operator=(bool b) {
    tb.pisz(id, b);

    return *this;
}

tabbit::ref& tabbit::ref::operator=(const ref& other) {
    tb.pisz(id, other.tb.czytaj(other.id));

    return *this;
}

tabbit::ref::operator bool() const {
    return tb.czytaj(id);
}

bool tabbit::czytaj(int i) const {
    if (i < 0 || i >= dl) throw std::out_of_range("id bitu poza tablicą");
    return (tab[i / jednostka] >> (i % jednostka)) & 1;
}

void tabbit::pisz(int i, bool b) {
    if (i < 0 || i >= dl) throw std::out_of_range("id bitu poza tablicą");

    slowo mask = 1ULL << (i % jednostka);

    if (b) tab[i / jednostka] |= mask;
    else tab[i / jednostka] &= ~mask;
}
void tabbit::clean() {
    int over = dl % jednostka;

    if (over != 0) {
        int last = dl / jednostka;
        slowo mask = (1ULL << over) - 1;
        tab[last] &= mask;
    }
}

inline int tabbit::count_words(int bits) {
    return (bits + tabbit::jednostka - 1) / tabbit::jednostka;
}

tabbit::tabbit(int rozm) : dl(rozm) {
    if (dl < 0) throw std::invalid_argument("rozmiar tablicy nie może być ujemny");

    int count = count_words(dl);
    tab = new slowo[count]();
}

tabbit::tabbit(slowo tb) : dl(jednostka) {
    tab = new slowo[1];
    tab[0] = tb;
}

tabbit::tabbit(std::initializer_list<bool> lista) : dl(lista.size()) {
    int count = count_words(dl);
    tab = new slowo[count]();

    int i = 0;
    for (bool bit : lista) pisz(i++, bit);
}

tabbit::~tabbit() {
    delete[] tab;
}

tabbit::tabbit(const tabbit &tb) : dl(tb.dl) {
    int ilosc = count_words(dl);
    tab = new slowo[ilosc];
    std::copy(tb.tab, tb.tab + ilosc, tab);
}

tabbit::tabbit(tabbit &&tb) : dl(tb.dl), tab(tb.tab) {
    tb.dl = 0;
    tb.tab = nullptr;
}

tabbit& tabbit::operator=(const tabbit &tb) {
    if (this != &tb) {
        delete[] tab;
        dl = tb.dl;
        int count = count_words(dl);
        tab = new slowo[count];
        std::copy(tb.tab, tb.tab + count, tab);
    }

    return *this;
}

tabbit& tabbit::operator=(tabbit &&tb) {
    if (this != &tb) {
        delete[] tab;
        dl = tb.dl;
        tab = tb.tab;
        tb.dl = 0;
        tb.tab = nullptr;
    }

    return *this;
}

bool tabbit::operator[](int i) const {
    return czytaj(i);
}

tabbit::ref tabbit::operator[](int i) {
    return ref(*this, i);
}

inline int tabbit::rozmiar() const {
    return dl;
}

tabbit& tabbit::operator|=(const tabbit &tb_other) {
    if (dl != tb_other.dl) throw std::invalid_argument("tablice nie mają równych rozmiarów");

    for (int i = 0; i < count_words(dl); ++i) {
        tab[i] |= tb_other.tab[i];
    }

    return *this;
}

tabbit& tabbit::operator&=(const tabbit &tb_other) {
    if (dl != tb_other.dl) throw std::invalid_argument("tablice nie mają równych rozmiarów");

    for (int i = 0; i < count_words(dl); ++i) {
        tab[i] &= tb_other.tab[i];
    }

    return *this;
}

tabbit& tabbit::operator^=(const tabbit &tb_other) {
    if (dl != tb_other.dl) throw std::invalid_argument("tablice nie mają równych rozmiarów");
    
    for (int i = 0; i < count_words(dl); ++i) {
        tab[i] ^= tb_other.tab[i];
    }

    return *this;
}

tabbit tabbit::operator!() const {
    tabbit wynik(*this);

    for (int i = 0; i < wynik.count_words(dl); ++i) {
        wynik.tab[i] = ~wynik.tab[i];
    }

    wynik.clean();

    return wynik;
}

tabbit operator|(const tabbit &tb1, const tabbit &tb2) {
    tabbit wynik(tb1);
    wynik |= tb2;

    return wynik;
}

tabbit operator&(const tabbit &tb1, const tabbit &tb2) {
    tabbit wynik(tb1);
    wynik &= tb2;

    return wynik;
}

tabbit operator^(const tabbit &tb1, const tabbit &tb2) {
    tabbit wynik(tb1);
    wynik ^= tb2;

    return wynik;
}
