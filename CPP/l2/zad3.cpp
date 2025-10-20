#include <iostream>
#include <memory>
#include <vector>
#include <map>

using namespace std;

enum class Gender { male, female };

class Llama;

static const shared_ptr<Llama> noname = nullptr;
static const string UNKNOWN_DAD = "";

class Llama {
private:
    string name;
    Gender gender;
    shared_ptr<Llama> mom;
    shared_ptr<Llama> dad;
    vector<weak_ptr<Llama>> children;

public:
    Llama(string n, Gender g, shared_ptr<Llama>m = noname, shared_ptr<Llama>d = noname) : name(n), gender(g), mom(m), dad(d) {
        cerr << name << " dołączył" << (gender == Gender::male ? " " : "a ") << "do stada!" << endl;
    }

    ~Llama() {
        cerr << name << (gender == Gender::male ? " odszedł" : " odeszła") << " ze stada!" << endl;
    }

    void add_child(shared_ptr<Llama> child) {
        children.push_back(child);
    }

    const string get_name() {
        return name;
    }

    void print_children() {
        cout << "Dzieci: ";

        for (size_t i = 0; i < children.size(); ++i) {
            if (const auto c = children[i].lock(); c != noname) {
                cout << c->get_name();
            } else {
                cout << "expired";
            }
        
            if (i != children.size() - 1) cout << ", ";
        }

        cout << endl;
    }
};

class Herd {
private:
    map<string, shared_ptr<Llama>> llamas;

public:
    void buy(string name, Gender gender) {
        if (llamas.find(name) != llamas.end()) {
            cerr << "Err: Lama " << name << " już istnieje w stadzie" << endl;
            return;
        }
        
        llamas.emplace(name, make_shared<Llama>(name, gender));
    }

    void sell(string name) {
        if (llamas.erase(name) == 0) {
            cerr << "Err: lama " << name << " nie istnieje w stadzie" << endl;
        }
    }

    void birth(string name, Gender gender, string mom, string dad) {
        if (llamas.find(name) != llamas.end()) {
            cerr << "Err: Lama " << name << " już istnieje w stadzie" << endl; 
            return;
        }

        shared_ptr<Llama> mom_ptr = noname;

        if (const auto& it = llamas.find(mom); it != llamas.end()) {
            mom_ptr = it->second;
        } else {
            cerr << "Err: Mama lama " << mom << " nie istnieje w stadzie" << endl;
            return;
        }

        shared_ptr<Llama>dad_ptr = noname;

        if (dad != UNKNOWN_DAD) {
            if (const auto& it = llamas.find(dad); it != llamas.end()) {
                dad_ptr = it->second;
            } else {
                cerr << "Err: Tata lama " << dad << " nie istnieje w stadzie" << endl;
                return;
            }
        }

        auto child = make_shared<Llama>(name, gender, mom_ptr, dad_ptr);
        llamas.emplace(name, child);

        mom_ptr->add_child(child);
        
        if (dad_ptr != noname) dad_ptr->add_child(child);
    }

    void print_children(string name) {
        if (const auto& it = llamas.find(name); it != llamas.end()) {
            it->second->print_children();
        } else {
            cerr << "Err: Lama " << name << " nie istnieje w stadzie" << endl;
        }
    }
};

int main() {
    Herd herd;

    herd.buy("Jerry", Gender::male);
    herd.buy("Matilda", Gender::female);

    herd.birth("Jeremy", Gender::male, "Matilda", "Jerry");
    herd.birth("May", Gender::female, "Matilda", UNKNOWN_DAD);

    herd.sell("Jeremy");
    herd.print_children("Matilda");

    return 0;
}
