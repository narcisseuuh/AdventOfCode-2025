#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

std::pair<std::vector<ulong>, std::vector<std::pair<ulong, ulong>>>
parse(std::string fname) {
    std::ifstream inputfile(fname);
    std::string line;
    std::vector<ulong> ingredients;
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
            } else {
                iss.str(line);
                ulong id;
                iss >> id;
                ingredients.push_back(id);
            }
        }
        inputfile.close();
    } else {
        std::cerr << "error opening " << fname << '\n';
        exit(1);
    }
    return std::make_pair(ingredients, ranges);
}

int main() {
    auto [ingredients, ranges] = parse("input.txt");
    int n = ingredients.size();
    int m = ranges.size();
    int res = 0;

    std::sort(ranges.begin(), ranges.end(), [](const auto& p1, const auto& p2) {
        return p1.first < p2.first;
    });
    std::sort(ingredients.begin(), ingredients.end());

    int j = 0;
    for (int i = 0 ; i < n ; ++i) {
        auto [first, last] = ranges[j];
        if (ingredients[i] < first) continue;
        while (ingredients[i] > last && j < m) {
            ++j;
            first = ranges[j].first;
            last = ranges[j].second;
        }
        if (ingredients[i] >= first && ingredients[i] <= last) res += 1;
    }
    
    std::cout << "solution: " << res << '\n';
    return 0;
}