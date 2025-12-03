#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

enum Direction {
    LEFT,
    RIGHT,
};

std::string to_string(Direction d) {
    switch (d) {
        case LEFT:
            return "LEFT";
        case RIGHT:
            return "RIGHT";
        default:
            std::cerr << "impossible...\n";
            exit(1);
    }
}

std::vector<std::pair<Direction, int>> parse(std::string& fname) {
    std::ifstream inputfile(fname);
    std::string line;
    std::vector<std::pair<Direction, int>> res;
    if (inputfile.is_open()) {
        while (std::getline(inputfile, line)) {
            std::istringstream iss;
            iss.str(line);
            char dir;
            int times;
            Direction d;
            iss >> dir >> times;
            switch (dir) {
                case 'L':
                    d = Direction::LEFT;
                    break;
                case 'R':
                    d = Direction::RIGHT;
                    break;
                default:
                    std::cerr << "unknown direction " << dir << '\n';
                    exit(1);
            }
            res.push_back(
                std::make_pair(d, times)
            );
        }
        inputfile.close();
    } else {
        std::cerr << "error opening " << fname << '\n';
        exit(1);
    }
    return res;
}

int main() {
    std::string fname = "input.txt";
    auto input = parse(fname);
    
    int pos = 50;
    int password = 0;
    for (size_t i = 0 ; i < input.size() ; ++i) {
        auto [direction, distance] = input[i];
        switch (direction) {
            case Direction::LEFT:
                if (pos == 0) {
                    password += distance / 100;
                } else {
                    if (distance >= pos) {
                        password += (distance - pos) / 100 + 1;
                    }
                }
                pos = (pos - distance) % 100;
                if (pos < 0) pos += 100;
                break;
            case Direction::RIGHT:
                if (pos == 0) {
                    password += distance / 100;
                } else {
                    if (distance >= (100 - pos) % 100) {
                        password += (distance - 100 + pos) / 100 + 1;
                    }
                }
                pos = (pos + distance) % 100;
                break;
        }
    }
    std::cout << "password : " << password << '\n';
    assert(password == 6412);
    return 0;
}