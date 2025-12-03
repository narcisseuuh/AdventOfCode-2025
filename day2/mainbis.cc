#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

std::vector<std::pair<unsigned long, unsigned long>> parse(std::string fname) {
    std::ifstream inputfile(fname);
    std::string line;
    std::vector<std::pair<unsigned long, unsigned long>> res;
    if (inputfile.is_open()) {
        while (std::getline(inputfile, line)) {
            std::istringstream iss;
            iss.str(line);

            unsigned long beg, end;
            char sep;
            while (iss) {
                iss >> beg >> sep >> end;
                if (iss && sep == '-') {
                    res.push_back(
                        std::make_pair(beg, end)
                    );
                } else {
                    std::cout << "stream error..." << '\n';
                    exit(1);
                }
                iss >> sep;
                if (iss && sep == ',') {
                    continue;
                } else {
                    break;
                }
            }
        }
        inputfile.close();
    } else {
        std::cerr << "error opening " << fname << '\n';
        exit(1);
    }
    return res;
}

inline int n_digits(unsigned long val) {
    int i = 0;
    while (val) {
        val = val / 10;
        ++i;
    }
    return i;
}

std::pair<unsigned long, unsigned long> splice(unsigned long val, int mid) {
    // gives a pair (upper, pow) with :
    // upper == digits of val between (beg, end),
    // pow == 10 ** beg
    unsigned long upper = 0;
    int acc = 1;
    for (int i = 1 ; i <= mid ; ++i) {
        acc *= 10;
    }
    upper = val / acc;
    return std::make_pair(upper, acc);
}

inline unsigned long next_pow10(unsigned long val) {
    unsigned long pow = 1;
    while (val) {
        val /= 10;
        pow *= 10;
    }
    return pow;
}

inline unsigned long pow10(int d) {
    unsigned long pow = 1;
    while (d) {
        pow *= 10;
        --d;
    }
    return pow;
}

int main() {
    auto input = parse("input.txt");
    int n = input.size();
    unsigned long res = 0;

    for (int i = 0 ; i < n ; ++i) {
        auto [beg, end] = input[i];
        int beg_digits = n_digits(beg);
        int end_digits = n_digits(end);
        std::unordered_set<unsigned long> seen;

        for (int d = beg_digits ; d <= end_digits ; ++d) {
            unsigned long powd = pow10(d);
            unsigned long low_d = pow10(d - 1);
            unsigned long high_d = powd - 1;

            for (int L = 1; L <= d/2; ++L) {
                if (d % L != 0) continue;
                int k = d / L;
                if (k < 2) continue;

                unsigned long powL = pow10(L);
                unsigned long denom = powL - 1;
                if (denom == 0) continue;
                unsigned long factor = (powd - 1) / denom;

                unsigned long b_min_digits = pow10(L - 1);
                unsigned long b_max_digits = pow10(L) - 1;

                unsigned long target_min = std::max(beg, low_d);
                unsigned long target_max = std::min(end, high_d);
                if (target_min > target_max) continue;

                unsigned long b_start = (target_min + factor - 1) / factor;
                unsigned long b_end = target_max / factor;

                if (b_start < b_min_digits) b_start = b_min_digits;
                if (b_end > b_max_digits) b_end = b_max_digits;
                if (b_start > b_end) continue;

                for (unsigned long b = b_start; b <= b_end; ++b) {
                    unsigned long target = b * factor;
                    if (target >= beg && target <= end) {
                        if (seen.insert(target).second) {
                            res += target;
                        }
                    }
                }
            }
        }
    }

    std::cout << "solution: " << res << '\n';
    return 0;
}