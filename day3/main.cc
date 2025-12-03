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

int main() {
    auto input = parse("input.txt");
    int n = input.size();
    unsigned long res = 0;
    
    for (int i = 0 ; i < n ; ++i) {
        int m = input[i].size();
        std::string& line = input[i];
        int max_idx = 0;
        int j;
        for (j = 1 ; j < m - 1 ; ++j) {
            if (to_int(line[j]) > to_int(line[max_idx])) max_idx = j;
        }
        int max_idx2 = max_idx + 1;
        for (j = max_idx + 2; j < m ; ++j) {
            if (to_int(line[j]) > to_int(line[max_idx2])) max_idx2 = j;
        }
        res += to_int(line[max_idx]) * 10 + to_int(line[max_idx2]);
    }

    std::cout << "solution: " << res << '\n';
    return 0;
}