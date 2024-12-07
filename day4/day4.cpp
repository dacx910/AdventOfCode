#include <fstream>
#include <iostream>
#include <vector>

int findDiagonal (std::vector<std::string> input) {
    int num = 0;
    std::string check;

    // Find diagonals like this: "\"
    for (int line = 0; line < 137; ++line) {
        for (int column = 0; column < 137; ++column) {
            check = "";
            check += input.at(line).at(column);
            check += input.at(line+1).at(column+1);
            check += input.at(line+2).at(column+2);
            check += input.at(line+3).at(column+3);

            if (check == "XMAS" || check == "SAMX") {
                ++num;
            }
        }
    }

    // Find diagonals like this: "/"
    for (int line = 0; line < 137; ++line) {
        for (int column = 3; column < 140; ++column) {
            check = "";
            check += input.at(line).at(column);
            check += input.at(line+1).at(column-1);
            check += input.at(line+2).at(column-2);
            check += input.at(line+3).at(column-3);

            if (check == "XMAS" || check == "SAMX") {
                ++num;
            }
        }
    }

    return num;
}

int findVertical (std::vector<std::string> input ) {
    int num = 0;
    std::string check;

    for (int row = 0; row < 137; ++row) {
        for (int column = 0; column < 140; ++column) {
            check = "";
            check += input.at(row).at(column);
            check += input.at(row+1).at(column);
            check += input.at(row+2).at(column);
            check += input.at(row+3).at(column);

            if (check == "XMAS" || check == "SAMX") {
                ++num;
            }
        }
    }

    return num;
}

int findHorizontal(std::vector<std::string> input) {
    int num = 0;
    for (std::string line : input) {
        while (line.find("XMAS") != std::string::npos) {
            ++num;
            line.replace(line.find("XMAS"), 4, "ZZZZ");
        }
    }

    for (std::string line : input) {
        while (line.find("SAMX") != std::string::npos) {
            ++num;
            line.replace(line.find("SAMX"), 4, "ZZZZ");
        }
    }

    return num;
}

int findXmas(std::vector<std::string> input) {
    int num = 0;
    std::string first,second,third;

    for (int row = 0; row < 138; ++row) {
        for (int column = 0; column < 138; ++column) {
            first = input.at(row).substr(column, 3);
            second = input.at(row+1).substr(column, 3);
            third = input.at(row+2).substr(column, 3);
            
            first.at(1) = ' ';
            second.at(0) = ' ';
            second.at(2) = ' ';
            third.at(1) = ' ';

            if (second.at(1) != 'A') {
                continue;
            }

            if ( (first.at(0) == 'M' && third.at(2) == 'S') || (first.at(0) == 'S' && third.at(2) == 'M') ) {
                if ( (first.at(2) == 'M' && third.at(0) == 'S') || (first.at(2) == 'S' && third.at(0) == 'M') ) {
                    ++num;
                    // std::cout << first << "\n" << second << "\n" << third << "\n******\n";
                }
            }
        }
    }
    return num;
}

int main() {
    std::fstream file("day4.txt");
    std::vector<std::string> puzzle(140);
    int total = 0;
    
    std::string line;
    for (int i = 0; i < 140; ++i) {
        getline(file, line);
        puzzle.at(i) = line;
    }

    // total += findHorizontal(puzzle);
    // total += findVertical(puzzle);
    // total += findDiagonal(puzzle);
    total += findXmas(puzzle);

    std::cout << total << "\n";

    return 0;
}