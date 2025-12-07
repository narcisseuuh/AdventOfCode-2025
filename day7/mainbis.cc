#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>

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
    std::queue<int> q;
    std::unordered_map<int, ulong> memoize;
    int j;
    unsigned long res = 0;

    for (j = 0 ; j < m ; ++j) {
        if (lines[0][j] == 'S') break;
    }
    q.push(j);
    memoize[j] = 1;
    for (int i = 1 ; i < n ; ++i) {
        if (i == n-1) break;
        int sz = q.size();
        std::unordered_map<int, ulong> new_memoize{};
        while (sz > 0) {
            j = q.front();
            q.pop();
            if (lines[i][j] == '.') {
                lines[i][j] = '|';
                new_memoize[j] = memoize[j];
                q.push(j);
            } else if (lines[i][j] == '|') {
                --sz;
                new_memoize[j] += memoize[j];
                continue;
            } else { // lines[i][j] == '^'
                if (j-1 >= 0 && lines[i][j-1] == '.') {
                    lines[i][j-1] = '|';
                    new_memoize[j-1] = memoize[j];
                    q.push(j-1);
                } else if (j-1 >= 0 && lines[i][j-1] == '|') {
                    new_memoize[j-1] += memoize[j];
                }
                if (j+1 < m && lines[i][j+1] == '.') {
                    lines[i][j+1] = '|';
                    new_memoize[j+1] = memoize[j];
                    q.push(j+1);
                } else if (j+1 < m && lines[i][j+1] == '|') {
                    new_memoize[j+1] += memoize[j];
                }
            }
            --sz;
        }
        memoize = std::move(new_memoize);
    }

    for (auto& [j, count] : memoize) {
        res += count;
    }
    
    std::cout << "solution: " << res << '\n';
    return 0;
}