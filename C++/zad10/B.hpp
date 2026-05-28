#pragma once

#include <fstream>
#include <string>
#include <type_traits>

#define NOT_POD_ERROR "typ musi być POD"

class ifsbin {
private:
    std::ifstream f;

public:
    explicit ifsbin(const std::string& fn) {
        f.exceptions(std::ios_base::failbit | std::ios_base::badbit);
        f.open(fn, std::ios::binary);
    }

    ~ifsbin() {
        if (f.is_open()) {
            try {
                f.close();
            } catch (...) {}
        }
    }

    template<typename T>
    ifsbin& read(T& val) {
        static_assert(std::is_trivially_copyable<T>::value, NOT_POD_ERROR);

        f.read(reinterpret_cast<char*>(&val), sizeof(T));

        return *this;
    }

    ifsbin& read(std::string& val) {
        val.clear();

        char c;

        while (true) {
            f.read(&c, 1);

            if (c == '\0') break;

            val += c;
        }

        return *this;
    }
};

class ofsbin {
private:
    std::ofstream f;

public:
    explicit ofsbin(const std::string& fn) {
        f.exceptions(std::ios_base::failbit | std::ios_base::badbit);
        f.open(fn, std::ios::binary);
    }

    ~ofsbin() {
        if (f.is_open()) {
            try {
                f.close();
            } catch (...) {}
        }
    }

    template<typename T>
    ofsbin& write(const T& val) {
        static_assert(std::is_trivially_copyable<T>::value, NOT_POD_ERROR);

        f.write(reinterpret_cast<const char*>(&val), sizeof(T));

        return *this;
    }

    ofsbin& write(const std::string& val) {
        f.write(val.c_str(), val.length() + 1);

        return *this;
    }
};
