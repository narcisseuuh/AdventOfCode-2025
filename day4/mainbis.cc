#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

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

void debug(std::vector<std::string>& input, int n, int m) {
    for (int i = 0 ; i < n ; ++i) {
        for (int j = 0 ; j < m ; ++j) {
            std::cout << input[i][j];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void dfs(std::vector<std::string>& input, std::vector<size_t>& hashes,
    int n, int m, unsigned long& res) {
    std::hash<std::string> hasher;
    std::vector<std::vector<bool>> marked(n, std::vector<bool>(m));
    std::stack<std::pair<int, int>> s{};
    for (int i = 0 ; i < n ; ++i) {
        for (int j = 0 ; j < m ; ++j) {
            if (input[i][j] == '@') s.push(std::make_pair(i, j));
        }
    }

    while (!s.empty()) {
        auto [i, j] = s.top();
        s.pop();
        if (marked[i][j]) continue;
        if (input[i][j] != '@') continue;
        marked[i][j] = true;
        auto next = moves(i, j, n, m);
        int num_adj_rolls = 0;
        for (auto [x, y] : next) {
            if (input[x][y] == '@') {
                ++num_adj_rolls;
                s.push(std::make_pair(x, y));
            }
            if (num_adj_rolls >= 4) {
                break;
            }
        }
        if (num_adj_rolls < 4) {
            input[i][j] = 'x';
            hashes[i] = hasher(input[i]);
            res += 1;
        }
    }
}

bool is_stable(std::vector<size_t>& hashes, std::vector<size_t>& prev_hashes) {
    for (int i = 0 ; i < hashes.size() ; ++i) {
        if (hashes[i] != prev_hashes[i]) return false;
    }
    return true;
}

int main() {
    auto input = parse("input.txt");
    int n = input.size();
    int m = input[0].size();
    unsigned long res = 0;
    
    bool stable = false;
    std::hash<std::string> hasher;
    std::vector<size_t> hashes(n);
    for (int i = 0 ; i < n ; ++i) {
        hashes[i] = hasher(input[i]);
    }
    
    while (!stable) {
        std::vector<size_t> prev_hashes{hashes.begin(), hashes.end()};
        dfs(input, hashes, n, m, res);
        stable = is_stable(hashes, prev_hashes);
    }
    
    std::cout << "solution: " << res << '\n';
    return 0;
}