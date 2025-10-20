#include <iostream>
#include <memory>
#include <fstream>

using namespace std;

class Writer {
private:
    ofstream *stream;

public:
    Writer(string file) : stream(new ofstream(file)) {};

    ~Writer() {
        cerr << "Closing file" << endl;
        stream->close();
        delete stream;
    }

    void write(string line) {
        *stream << line << endl;
    }
};

int main() {
    shared_ptr<Writer> wrt(new Writer("test.txt"));
    wrt->write("hej");

    shared_ptr<Writer> two(wrt);
    two->write("co");

    shared_ptr<Writer> three(wrt);
    three->write("tam?");

    return 0;
}
