#include <iostream>
#include <fstream>
#include <string>

template <typename T>
void serialize(std::ostream& os, const T& value) {
    os.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
void deserialize(std::istream& is, T& value) {
    is.read(reinterpret_cast<char*>(&value), sizeof(T));
}

void serialize_string(std::ostream& os, const std::string& str) {
    size_t size = str.size();

    serialize(os, size);
    os.write(str.data(), size); 
}

void deserialize_string(std::istream& is, std::string& str) {
    size_t size;

    deserialize(is, size);
    str.resize(size);
    is.read(&str[0], size);
}

template <typename T>
void serialize_array(std::ostream& os, const T* arr, size_t size) {
    serialize(os, size);
    os.write(reinterpret_cast<const char*>(arr), size * sizeof(T));
}

template <typename T>
std::pair<T*, size_t> deserialize_array(std::istream& is) {
    size_t size;

    deserialize(is, size);
    T* arr = new T[size];
    is.read(reinterpret_cast<char*>(arr), size * sizeof(T));

    return {arr, size};
}

int main() {
    const std::string fn = "dane.bin";
    std::ofstream out(fn, std::ios::binary);

    if (!out) {
        std::cerr << "Błąd otwarcia " << fn << '\n';
        exit(1);
    }

    int nr = 42;
    double pi = 3.14159;
    std::string s = "Witaj Swiecie";

    double tab[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    size_t size = 5;

    serialize(out, nr);
    serialize(out, pi);
    serialize_string(out, s);
    serialize_array(out, tab, size);

    out.close();

    std::ifstream in(fn, std::ios::binary);

    if (!in) {
        std::cerr << "Błąd otwarcia " << fn << '\n';
        exit(2);
    }

    int r_nr;
    double r_pi;
    std::string r_s;
    std::pair<double*, size_t> r_tab;

    deserialize(in, r_nr);
    deserialize(in, r_pi);
    deserialize_string(in, r_s);
    r_tab = deserialize_array<double>(in);

    std::cout << "int: " << r_nr << '\n'
              << "PI: " << r_pi << '\n'
              << "string: " << r_s << '\n'
              << "tablica: ";

    double* arr = r_tab.first;
    size_t size2 = r_tab.second;

    for(size_t i = 0; i < size2; ++i) std::cout << arr[i] << " ";
    std::cout << '\n';

    delete[] arr;

    in.close();

    return 0;
}
