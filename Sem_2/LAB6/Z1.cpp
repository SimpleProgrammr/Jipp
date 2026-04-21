//
// Created by Elmo on 09/04/2026.
//

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

string path = "./test.bin";

class BinaryRangeException : public std::exception {
public:
    BinaryRangeException() = default;

    virtual const char *what() const noexcept {
        return "BinaryRangeException";
    };
};

int get_file_size(const string &file_path) {
    ifstream file(file_path, ios::binary | ios::ate);
    if (file.is_open()) {
        int pos = file.tellg();
        file.close();
        return pos;
    }
    throw ios_base::failure("Cannot open file");
}

auto get_64_bytes(const string &file_path) {
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) {
        throw ios_base::failure("Cannot open file");
    }
    int pos = 0;
    while (!file.eof() && pos < 64) {
        int data = file.get();
        if (data == EOF) {
            break;
        }
        cout << std::hex << data << " ";
        pos++;
    }
    file.close();
    cout << endl;
}

auto read_64_bytes(const string &file_path) {
    int file_size = get_file_size(file_path);
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) {
        throw ios_base::failure("Cannot open file");
    }
    int len = min(64, file_size);

    char *data = new char[len];
    file.read(data, len);

    for (int i = 0; i < len; i++) {
        cout << data[i] << "";
    }

    return data;
}

void ascii_dump(const string &file_path) {
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) {
        throw ios_base::failure("Cannot open file");
    }
    int byte = 0;
    while (byte = file.get(), byte != EOF) {
        if (byte >= 31 && byte < 127) {
            cout << char(byte);
        } else cout << ".";
    }
}

void count_bytes(const string &file_path) {
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) {
        throw ios_base::failure("Cannot open file");
    }
    int *bytes = new int[256];

    int b = 0;
    while (b = file.get(), b != EOF) {
        bytes[b]++;
    }

    for (int i = 0; i < 256; i++) {
        if (bytes[i] > 0)
            cout << std::hex << i << std::dec << ": " << bytes[i] << endl;
    }
    delete [] bytes;
}

void get_ints(const string &file_path, int offset, int mode) {
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) {
        throw ios_base::failure("Cannot open file");
    }
    int size = get_file_size(file_path);
    if (offset + mode / 8 > size)
        throw BinaryRangeException();
    uint16_t u16 = 0;
    uint32_t u32 = 0;
    uint64_t u64 = 0;
    switch (mode) {
        case 16:
            file.read(reinterpret_cast<char *>(&u16), sizeof(u16));
            cout << "U16: " << u16 << endl;
            break;
        case 32:
            file.read(reinterpret_cast<char *>(&u32), sizeof(u32));
            cout << "U32: " << u32 << endl;
            break;
        case 64:
            file.read(reinterpret_cast<char *>(&u64), sizeof(u64));
            cout << "U64: " << u64 << endl;
            break;
        default:
            throw runtime_error("Unknown mode");
    }
}


int main(int argc, char *argv[]) {
    int mode = 16;
    int offset = 0;
    for (int i = 1; i < argc; i++) {
        cout << argv[i] << endl;
        if (strcmp(argv[i], "--offset") == 0) {
            if (i + 1 < argc) {
                offset = stoi(argv[++i]);
            }
        } else if (strcmp(argv[i], "--mode") == 0) {
            if (i + 1 < argc) {
                char *m = argv[++i];
                if (strcmp(m, "u16") == 0) {
                    mode = 16;
                } else if (strcmp(m, "u32") == 0) {
                    mode = 32;
                } else if (strcmp(m, "u64") == 0) {
                    mode = 64;
                }
            }
        }
    }


    cout << path << endl;
    cout << "File size: " << get_file_size(path) << endl;
    cout << "Hex read 64 bytes: ";
    get_64_bytes(path);
    cout << "Read 64 bytes: ";
    char *c64 = read_64_bytes(path);
    cout << endl;
    delete [] c64;
    cout << "ASCII dump: ";
    ascii_dump(path);
    cout << "Bytes count: " << endl;
    count_bytes(path);

    get_ints(path, offset, mode);

    return 0;
}