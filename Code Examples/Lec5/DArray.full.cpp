#include <iostream>
using namespace std;

class DArray {
    int len_;
    int *data_;
public:
    DArray(int len = 5) : len_(len) {
        data_ = new int[len];
    }

    ~DArray() {
        delete [] data_;
    }

    // setters/getters
    int operator[](int index) const {
        return data_[index];
    }

    int& operator[](int index) {
        return data_[index];
    }

    size_t length() const {
        return len_;
    }

    void resize(int size) {
        int *newdata = new int[size];
        for (int i = 0; i < len_ && i < size; i++) {
            newdata[i] = data_[i];
        }
        delete data_;
        data_ = newdata;
        len_ = size;
    }

    DArray(const DArray& other) {
        len_ = other.len_;
        data_ = new int[len_];
        for (int i = 0; i < len_; i++)
            data_[i] = other.data_[i];
    }

    DArray& operator=(DArray other) {
        swap(data_,other.data_);
        swap(len_, other.len_);
        return *this;
    }
};

ostream& operator<<(ostream& output, const DArray& vals ) {
    for (size_t i = 0; i < vals.length() - 1; i++) {
        output << vals[i] << ",";
    }
    output << vals[vals.length()-1];
}

int main() {
    DArray vals(4);
    vals[0] = 1;
    cout << vals << endl;
    vals[1] = 2;
    vals[2] = 3;
    vals[3] = vals[2] + 1;
    cout << vals << endl;

    DArray other(vals);
    other = vals;
}
