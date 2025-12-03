#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> parse(std::string fname) {
    std::ifstream inputfile(fname);
    std::string line;
    std::vector<std::string> res;
    if (inputfile.is_open()) {
        while (std::getline(inputfile, line)) {
            res.push_back(line);
        }
        inputfile.close();
    } else {
        std::cerr << "error opening " << fname << '\n';
        exit(1);
    }
    return res;
}

inline int to_int(unsigned char c) {
    return c - '0';
}

unsigned long long max_for_line(std::string& line, int m) {
    std::vector<int> indices{};
    indices.push_back(0);
    int indices_sz = 1;
    for (int i = 11 ; i >= 0 ; --i) {
        int max_idx;
        if (i == 11) max_idx = indices[indices_sz - 1];
        else max_idx = indices[indices_sz - 1] + 1;
        for (int j = max_idx + 1 ; j < m - i ; ++j) {
            if (to_int(line[j]) > to_int(line[max_idx])) max_idx = j;
        }
        ++indices_sz;
        indices.push_back(max_idx);
    }
    unsigned long long res = 0;
    for (int i = 1 ; i < indices_sz ; ++i) {
        res = res * 10 + to_int(line[indices[i]]);
    }
    return res;
}

int main() {
    auto input = parse("input.txt");
    int n = input.size();
    unsigned long long res = 0;
    
    for (int i = 0 ; i < n ; ++i) {
        int m = input[i].size();
        std::string& line = input[i];
        res += max_for_line(line, m);
    }

    std::cout << "solution: " << res << '\n';
    return 0;
}