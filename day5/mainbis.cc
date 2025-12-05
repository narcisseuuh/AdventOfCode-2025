#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<std::pair<ulong, ulong>> parse(std::string fname) {
    std::ifstream inputfile(fname);
    std::string line;
    std::vector<std::pair<ulong, ulong>> ranges;
    if (inputfile.is_open()) {
        while (std::getline(inputfile, line)) {
            std::stringstream iss;
            if (line.size() < 2) continue;
            if (size_t pos = line.find("-"); pos != std::string::npos) {
                ulong first, last;
                line[pos] = ' ';
                iss.str(line);
                iss >> first >> last;
                ranges.push_back(std::make_pair(first, last));
            }
        }
        inputfile.close();
    } else {
        std::cerr << "error opening " << fname << '\n';
        exit(1);
    }
    return ranges;
}

bool intersects(const std::pair<ulong, ulong>& p1, const std::pair<ulong, ulong>& p2) {
    return (std::max(p1.first, p2.first)) <= (std::min(p1.second, p2.second));
}

int main() {
    auto ranges = parse("input.txt");
    ulong res = 0;

    std::sort(ranges.begin(), ranges.end(), [](const auto& p1, const auto& p2) {
        return p1.first < p2.first;
    });

    std::vector<std::pair<ulong, ulong>> merged;
    if (!ranges.empty()) {
        merged.push_back(ranges.front());
    }

    for (size_t idx = 1; idx < ranges.size(); ++idx) {
        auto& cur = ranges[idx];
        auto& back = merged.back();
        if (intersects(back, cur)) {
            back.first = std::min(back.first, cur.first);
            back.second = std::max(back.second, cur.second);
        } else {
            merged.push_back(cur);
        }
    }

    for (auto [first, last] : merged) {
        res += (last - first + 1);
    }
    
    std::cout << "solution: " << res << '\n';
    return 0;
}