#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr long max_stream_size = std::numeric_limits<std::streamsize>::max();

int main() {
    std::ifstream file("day2.input");

    if (!file.is_open()) {
        std::cout << "Unable to open file";
        return 1;
    }

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line);) {
        lines.push_back(line);
    }

    // Part 1
    int line_number = 0;
    int ids_sum = 0;
    int power_sum = 0;
    for (const auto &line : lines) {
        ++line_number;

        std::istringstream iss(line);
        iss.ignore(max_stream_size, ':');
        iss.get();

        std::string amount_str;
        std::string color;

        bool illegal_game = false;
        int min_red = 0;
        int min_green = 0;
        int min_blue = 0;

        while (std::getline(iss, amount_str, ' ')) {
            std::getline(iss, color, ' ');
            if (!std::isalpha(color.back())) {
                color.pop_back();
            }

            int amount = std::stoi(amount_str);

            if (color == "red") {
                min_red = std::max(min_red, amount);
                illegal_game |= amount > 12;
            } else if (color == "green") {
                min_green = std::max(min_green, amount);
                illegal_game |= amount > 13;
            } else if (color == "blue") {
                min_blue = std::max(min_blue, amount);
                illegal_game |= amount > 14;
            } else {
                std::cout << "Unknown color: " << color << std::endl;
                return 1;
            }
        }
        if (!illegal_game) {
            ids_sum += line_number;
        }
        power_sum += min_red * min_green * min_blue;
    }

    std::cout << ids_sum << std::endl;
    std::cout << power_sum << std::endl;

    return 0;
}
