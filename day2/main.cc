#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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

        for (int d = beg_digits ; d <= end_digits ; ++d) {
            if (d % 2 == 1) continue;
            int mid = d / 2;
            unsigned long spliced;
            if (d == beg_digits) {
                spliced = beg;
            } else {
                spliced = pow10(d - 1);
            }
            auto [upper, pow] = splice(spliced, mid);
            unsigned long bound = next_pow10(upper * pow);
            auto target = upper * pow + upper;
            while (target <= std::min(bound, end)) {
                if (!(target >= beg && target <= end)) {
                    upper += 1;
                    target = upper * pow + upper;
                    continue;
                }
                std::cout << "found target : " << target << '\n';
                res += target;
                upper += 1;
                target = upper * pow + upper;
            }
        }
    }

    std::cout << "solution: " << res << '\n';
    return 0;
}