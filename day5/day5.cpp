#include <fstream>
#include <vector>
#include <string>
#include <iostream>

bool checkIsValid(std::string input) {

}

int main() {
    std::fstream inputRules("rules.txt");
    std::fstream inputPages("pages.txt");
    std::vector<std::vector<int>> rules(100);
    std::string input;

    if (!inputRules.is_open() || !inputPages.is_open()) {
        std::cout << "File open failed\n";
        return -1;
    }

    // Read rules
    while (getline(inputRules, input)) {
        int num = stoi(input.substr(0,2));
        int preceding = stoi(input.substr(3,2));

        rules.at(num).push_back(preceding);
    }

    // Read pages
    while (getline(inputPages, input)) {
        if (checkIsValid(input)) {
            std::cout << input;
        }
    }

    return 0;
}