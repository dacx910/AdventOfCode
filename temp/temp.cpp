#include <fstream>
#include <vector>
#include <string>
#include <iostream>

bool vectorContains(std::vector<int> vec, int num) {
    for (int i : vec) {
        if (num == i) {
            return true;
        }
    }
    return false;
}

int findMiddleNum(std::vector<int> nums) {
    // std::cout << nums.at(nums.size()/2) << "\n";
    return nums.at(nums.size() / 2);
}

bool checkIsValid(std::vector<int> nums, std::vector<std::vector<int>> rules) {
    // for (int num : nums) {
    //     std::cout << num << ": ";
    //     for (int rule : rules.at(num)) {
    //         std::cout << rule << ", ";
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "\n";

    for (unsigned checkNum = nums.size() - 1; checkNum > 0; --checkNum) {
        for (int rule : rules.at(nums.at(checkNum))) {
            for (unsigned i = 0; i < checkNum; ++i) {
                if (nums.at(i) == rule) {
                    return false;
                }
            }
        }
    }

    // std::cout << "Successful string: {";
    // for (unsigned i = 0; i < nums.size()-1; ++i) {
    //     std::cout << nums.at(i) << ", ";
    // }
    // std::cout << nums.back() << "}\n";
    return true;
}

int vectorFind(std::vector<int> vec, int search) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec.at(i) == search) {
            return i;
        }
    }
    return -1;
}

std::vector<int> fixIncorrect(std::vector<int> page, std::vector<std::vector<int>> rules) {
    std::vector<int> fixed(page.size()), magnitude(page.size());
    std::vector<std::vector<int>> newRules(100);

    for (int num : page) {
        for (int rule : rules.at(num)) {
            if (vectorContains(page, rule)) {
                newRules.at(num).push_back(rule);
            }
        }
    }

    for (int i = 0; i < page.size(); ++i) {
        magnitude.at(i) = newRules.at(page.at(i)).size();
    }
    
    for (int i = 0; i < fixed.size(); ++i) {
        fixed.at(i) = page.at( vectorFind(magnitude, fixed.size() - 1 - i) );
    }

    return fixed;
}

int main() {
    std::fstream inputRules("rules.txt");
    std::fstream inputPages("pages.txt");
    std::vector<std::vector<int>> rules(100);
    std::vector<std::vector<int>> pages, incorrectPages, fixed;
    std::string input;
    int totalCorrect = 0;
    int totalIncorrect = 0;

    if (!inputRules.is_open() || !inputPages.is_open()) {
        std::cout << "File open failed\n";
        return -1;
    }

    // Read rules
    while (getline(inputRules, input)) {
        int num = stoi(input.substr(0, 2));
        int preceding = stoi(input.substr(3, 2));

        rules.at(num).push_back(preceding);
    }

    // Read pages
    for (int i = 0; getline(inputPages, input); ++i) {
        pages.push_back(std::vector<int>());
        while (input.find(",") != std::string::npos) {
            pages.at(i).push_back(stoi(input.substr(0, input.find(","))));
            input.erase(0, input.find(",") + 1);
        }
        pages.at(i).push_back(stoi(input.substr(0, 2)));
    }


    for (unsigned i = 0; i < pages.size(); ++i) {
        if (checkIsValid(pages.at(i), rules)) {
            totalCorrect += findMiddleNum(pages.at(i));
        }
        else {
            incorrectPages.push_back(pages.at(i));
        }
    }

    std::cout << "Sum of correct: " << totalCorrect << "\n";

    for (std::vector<int> page : incorrectPages) {
        totalIncorrect += findMiddleNum(fixIncorrect(page,rules));
    }

    std::cout << "Sum of incorrect (corrected): " << totalIncorrect << "\n";

    return 0;
}