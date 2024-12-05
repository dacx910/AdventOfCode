#include <iostream>
#include <fstream>
#include <vector>

void printVec(std::vector<int> vec) {
    for (int data: vec) {
        std::cout << data << " ";
    }
    std::cout << "\n";
}

bool checkSafety(std::vector<int> nums, bool secondCheck) {
    bool increasing = (nums.at(0) < nums.at(1));

    if (increasing) {
        for (int i = 0; i < nums.size()-1; ++i) {
            int difference = nums.at(i+1)-nums.at(i);
            if (difference < 1 || difference > 3) {
                return false;
            }
        }
    } else {
        for (int i = 0; i < nums.size()-1; ++i) {
            int difference = nums.at(i)-nums.at(i+1);
            if (difference < 1 || difference > 3) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    bool testing = false;

    if (testing) {
        std::vector<int> nums{9, 2, 8, 7};
        if (checkSafety(nums, false)) {
            std::cout << "Passed 1st try\n";
        } else {
            std::vector<int> temp;
            for (int i = 0; i < nums.size(); ++i) {
                temp = nums;
                temp.erase(temp.begin()+i);
                if(checkSafety(temp, false)) {
                    std::cout << "Passed after deleting index " << i << "\n";
                    return 0;
                }
            }
            std::cout << "Failed!\n";
        }
        return 0;
    }

    std::ifstream file("day2.txt");

    std::string input;
    int counter = 0;
    while (getline(file, input)) {
        std::vector<int> report;
        while (input.find(' ') != std::string::npos) {
            report.push_back(stoi(input.substr(0, input.find(' '))));
            input.erase(0, input.find(' ')+1);
        }
        report.push_back(stoi(input.substr(0, input.find(' '))));

        if (checkSafety(report, false)) {
            ++counter;
        } else {
            std::vector<int> temp;
            for (int i = 0; i < report.size(); ++i) {
                temp = report;
                temp.erase(temp.begin()+i);
                if(checkSafety(temp, false)) {
                    ++counter;
                    break;
                }
            }
        }
    }

    std::cout << "Total: ";
    std::cout << counter << "\n";


    return 0;
}