#include <iostream>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <tuple>

// ważony graf dynamiczny jako lista sąsiadów
// krawędzie wagi double
// można dodawać i usuwać wierzchołkki, krawędzie i wagi
// id wierzchołka jako string, waga double

class DG {
private:
    std::unordered_map<std::string, std::unordered_map<std::string, double>> adjs;
public:
    bool add_v(const std::string &name) {
        if (adjs.contains(name)) {
            return false;
        } else {
            adjs[name] = {};
            return true;
        }
    }

    bool remove_v(const std::string &name) {
        if (adjs.erase(name)) {
            for (auto &[v, map] : adjs) {
                map.erase(name);
            }

            return true;
        }
        return false;
    }

    bool add_e(const std::string &v1, const std::string &v2, double w) {
        if (!adjs.contains(v1) || !adjs.contains(v2)) {
            return false;
        }

        adjs[v1][v2] = w;
        adjs[v2][v1] = w;
        return true;
    }

    bool remove_e(const std::string &v1, const std::string &v2) {
        if (adjs.contains(v1) && adjs.contains(v2) && adjs[v1].contains(v2)) {
            adjs[v1].erase(v2);
            adjs[v2].erase(v1);
            return true;
        }
        return false;
    }

    bool update_e(const std::string &v1, const std::string &v2, double w) {
        if (adjs.contains(v1) && adjs[v1].contains(v2)) {
            adjs[v1][v2] = w;
            adjs[v2][v1] = w;
            return true;
        }
        return false;
    }

    std::string first_v() const {
        if (adjs.empty()) return "";
        return adjs.begin()->first;
    }

    DG mst() {
        DG res;
        if (adjs.empty()) return res;

        using edge = std::tuple<double, std::string, std::string>;

        auto comp = [](const edge &a, const edge &b) {
            return std::get<double>(a) > std::get<double>(b); 
        };

        std::priority_queue<edge, std::vector<edge>, decltype(comp)> pq(comp);
        std::unordered_set<std::string> visited;
        std::string start = first_v();

        res.add_v(start);
        visited.insert(start);

        for (const auto &[neigh, w] : adjs.at(start)) {
            pq.push({w, neigh, start});
        }

        while (!pq.empty()) {
            auto [w, curr, parent] = pq.top();
            pq.pop();

            if (visited.contains(curr)) {
                continue;
            }

            res.add_v(curr);
            res.add_e(parent, curr, w);
            visited.insert(curr);

            for (const auto &[next_n, next_w] : adjs.at(curr)) {
                if (!visited.contains(next_n)) {
                    pq.push({next_w, next_n, curr});
                }
            }
        }

        return res;
    }

    void print() const {
        for (const auto &[u, neighbors] : adjs) {
            std::cout << u << ": ";
            for (const auto &[v, w] : neighbors) {
                std::cout << '{' << v << ", " << w << "} ";
            }
            std::cout << '\n';
        }
    }
};

int main() {
    DG g;
    g.add_v("A"); g.add_v("B"); g.add_v("C"); g.add_v("D");
    g.add_e("A", "B", 1.0);
    g.add_e("B", "C", 2.0);
    g.add_e("A", "C", 4.0);
    g.add_e("C", "D", 1.0);

    std::cout << "Graf:\n";
    g.print();

    DG mst = g.mst();
    std::cout << "\nMST:\n";
    mst.print();

    return 0;
}
