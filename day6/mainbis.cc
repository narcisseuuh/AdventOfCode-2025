#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>

enum Op {
    Add,
    Mul,
    Default
};

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

int main() {
    auto lines = parse("input.txt");
    int n = lines.size();
    int m = lines[0].size();
    unsigned long long res = 0;
    unsigned long partial_res = 0;
    Op cur = Op::Default;

    for (int j = 0 ; j < m ; ++j) {
        if (lines[n-1][j] == '+') {
            cur = Op::Add;
            res += partial_res;
            partial_res = 0;
        }
        if (lines[n-1][j] == '*') {
            cur = Op::Mul;
            res += partial_res;
            partial_res = 0;
        }

        int num_spaces = 0;
        std::string num{};
        for (int i = 0 ; i < n-1 ; ++i) {
            if (lines[i][j] == ' ') {
                ++num_spaces;
                continue;
            }
            num += lines[i][j];
        }
        if (num_spaces == n-1) continue;
        switch (cur) {
            case Op::Add:
                partial_res += std::stoul(num);
                break;
            case Op::Mul:
                if (partial_res) {
                    partial_res *= std::stoul(num);
                } else {
                    partial_res = std::stoul(num);
                }
                break;
            default:
                std::cerr << "Unknown operand\n";
                exit(1);
        }
    }
    if (partial_res) res += partial_res;
    
    std::cout << "solution: " << res << '\n';
    return 0;
}