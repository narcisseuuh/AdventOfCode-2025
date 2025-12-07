#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

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
    int j;
    unsigned long res = 0;

    for (j = 0 ; j < m ; ++j) {
        if (lines[0][j] == 'S') break;
    }
    q.push(j);
    for (int i = 1 ; i < n ; ++i) {
        int sz = q.size();
        while (sz > 0) {
            j = q.front();
            q.pop();
            if (lines[i][j] == '.') {
                lines[i][j] = '|';
                q.push(j);
            } else if (lines[i][j] == '|') {
                --sz;
                continue;
            } else { // lines[i][j] == '^'
                res += 1;
                if (j-1 >= 0 && lines[i][j-1] == '.') {
                    lines[i][j-1] = '|';
                    q.push(j-1);
                }
                if (j+1 < m && lines[i][j+1] == '.') {
                    lines[i][j+1] = '|';
                    q.push(j+1);
                }
            }
            --sz;
        }
    }
    
    std::cout << "solution: " << res << '\n';
    return 0;
}