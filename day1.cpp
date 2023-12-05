#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const char input_path[] = "day1.input";

struct possibility {
    std::string digit_str;
    size_t index;
    std::size_t digit;
};

constexpr std::array<std::string_view, 10> digits = {
    "zero", "one", "two",   "three", "four",
    "five", "six", "seven", "eight", "nine"};

int should_add(char c, std::vector<possibility> &digit_checking,
               bool reverse = false) {
    if (std::isdigit(c)) {
        return (c - '0');
    }

    digit_checking.erase(
        std::remove_if(digit_checking.begin(), digit_checking.end(),
                       [c](auto &to_check) {
                           return to_check.digit_str[to_check.index++] != c;
                       }),
        digit_checking.end());

    for (auto const &to_check : digit_checking) {
        if (to_check.index == to_check.digit_str.size()) {
            return to_check.digit;
        }
    }

    for (size_t i = 0; i < digits.size(); ++i) {
        std::string digit(digits[i]);
        if (reverse) {
            std::reverse(digit.begin(), digit.end());
        }
        if (digit[0] == c) {
            digit_checking.push_back({digit, 1, i});
        }
    }

    return -1;
}

int main() {
    std::ifstream file(input_path);

    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line);) {
        lines.push_back(line);
    }

    // Part 1
    int sum = 0;

    for (const auto &line : lines) {
        for (const auto &c : line) {
            if (std::isdigit(c)) {
                sum += (c - '0') * 10;
                break;
            }
        }

        for (auto iter = line.crbegin(); iter != line.crend(); ++iter) {
            const auto &c = *iter;
            if (std::isdigit(c)) {
                sum += c - '0';
                break;
            }
        }
    }

    std::cout << sum << std::endl;

    // Part 2
    sum = 0;
    std::vector<possibility> digit_checking;

    for (const auto &line : lines) {
        digit_checking.clear();
        for (const auto &c : line) {
            auto to_add = should_add(c, digit_checking);
            if (to_add != -1) {
                sum += to_add * 10;
                break;
            }
        }

        digit_checking.clear();
        for (auto iter = line.crbegin(); iter != line.crend(); ++iter) {
            const auto &c = *iter;
            auto to_add = should_add(c, digit_checking, true);
            if (to_add != -1) {
                sum += to_add;
                break;
            }
        }
    }

    std::cout << sum << std::endl;
}
