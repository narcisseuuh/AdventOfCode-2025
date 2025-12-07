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
    Mul
};

std::pair<std::vector<std::vector<ulong>>, std::vector<Op>>
parse(std::string fname) {
    std::ifstream inputfile(fname);
    std::string line;
    std::vector<std::vector<ulong>> numbers;
    std::vector<Op> operands;
    if (inputfile.is_open()) {
        while (std::getline(inputfile, line)) {
            if (line[0] != '+' && line[0] != '*') {
                std::stringstream iss(line);
                std::vector<ulong> cur{
                    std::istream_iterator<ulong>(iss),
                    std::istream_iterator<ulong>()
                };
                numbers.push_back(cur);
            } else {
                int sz = line.size();
                for (int i = 0 ; i < sz ; ++i) {
                    if (line[i] == '+') operands.push_back(Op::Add);
                    if (line[i] == '*') operands.push_back(Op::Mul);
                }
            }
        }
        inputfile.close();
    } else {
        std::cerr << "error opening " << fname << '\n';
        exit(1);
    }
    return std::make_pair(numbers, operands);
}

int main() {
    auto [numbers, operands] = parse("input.txt");
    int n = numbers.size();
    int m = operands.size();
    unsigned long long res = 0;
    ulong partial_res = 0;

    for (int j = 0 ; j < m ; ++j) {
        switch (operands[j]) {
            case Op::Add:
                partial_res = numbers[0][j];
                for (int i = 1 ; i < n ; ++i) {
                    partial_res += numbers[i][j];
                }
                res += partial_res;
                partial_res = 0;
                break;
            case Op::Mul:
                partial_res = numbers[0][j];
                for (int i = 1 ; i < n ; ++i) {
                    partial_res *= numbers[i][j];
                }
                res += partial_res;
                partial_res = 0;
                break;
        }
    }
    
    std::cout << "solution: " << res << '\n';
    return 0;
}