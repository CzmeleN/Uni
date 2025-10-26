#include <iostream>
#include <chrono>
#include <random>
#include <vector>

using namespace std;
using matrix_row = vector<float>;
using matrix = vector<matrix_row>;

constexpr size_t N = 3;
constexpr size_t sizes[N] = { 50, 100, 200 };
constexpr size_t tests[N] = { 500, 100, 25 };

matrix matrix_square(const matrix &m) {
    matrix res(m.size(), matrix_row(m.size(), 0));

    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j) {
            for (size_t k = 0; k < m.size(); ++k) {
                res[i][j] += m[i][k] * m[k][j];
            }
        }
    }

    return res;
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.5f, 2.0f);

    matrix matrices[N];

    for (size_t id = 0; id < N; ++id) {
        size_t size = sizes[id];

        matrices[id] = matrix(size, matrix_row(size));

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                matrices[id][i][j] = dis(gen);
            }
        }
    }

    for (size_t id = 0; id < N; ++id) {
        auto start = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < tests[id]; ++i) {
            auto res = matrix_square(matrices[id]);
        }

        auto end = chrono::high_resolution_clock::now();
        auto single = (end - start) / (double)tests[id];

        int millis = chrono::duration_cast<chrono::milliseconds>(single).count();

        cout << "size: " << sizes[id] << " #tests: " << tests[id]
            << "\n\tms: " << millis << "\n\tmins: "
            << fixed << setprecision(3) << millis / 60'000.0 << endl;
    }

    return 0;
}
