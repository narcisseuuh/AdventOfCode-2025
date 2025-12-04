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

inline bool valid_access(std::pair<int, int> p, int n, int m) {
    return (p.first >= 0 && p.first < n) && (p.second >= 0 && p.second < m);
}

std::vector<std::pair<int, int>> moves(int i, int j, int n, int m) {
    std::vector<std::pair<int, int>> res{};
    int dirs[8][2] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {-1, 0},
        {0, -1},
        {-1, -1},
        {1, -1},
        {-1, 1}
    };
    for (int k = 0 ; k < 8 ; ++k) {
        auto p = std::make_pair(i + dirs[k][0], j + dirs[k][1]);
        if (valid_access(p, n, m)) res.push_back(p);
    }
    return res;
}

int main() {
    auto input = parse("input.txt");
    int n = input.size();
    int m = input[0].size();
    unsigned long res = 0;

    for (int i = 0 ; i < n ; ++i) {
        for (int j = 0 ; j < m ; ++j) {
            if (input[i][j] != '@') continue;
            auto pos = moves(i, j, n, m);
            int num_adj_rolls = 0;
            for (auto [x, y] : pos) {
                if (input[x][y] == '@') ++num_adj_rolls;
                if (num_adj_rolls >= 4) {
                    break;
                }
            }
            if (num_adj_rolls < 4) {
                res += 1;
            }
        }
    }
    
    std::cout << "solution: " << res << '\n';
    return 0;
}