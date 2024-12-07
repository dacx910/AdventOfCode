#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

bool testing;

int doMul(std::string input) {
    int firstDigit, secondDigit;

    firstDigit = stoi(input.substr(input.find('(') + 1 , input.find(',') - input.find('(') - 1));
    secondDigit = stoi(input.substr(input.find(',') + 1, input.find(')') - input.find(',') - 1));

    if (testing) {
        std::cout << "Input String: " << input << "\n";
        std::cout << "First Digit: " << firstDigit << "\n";
        std::cout << "Second Digit: " << secondDigit << "\n";
    }

    return firstDigit*secondDigit;
}

int main() {
    std::ifstream file("day3.txt");
    unsigned long long sum = 0;
    std::string input = "";
    std::string pieceInput;
    
    testing = false;
   
    int index = 0;
    while (getline(file, pieceInput)) {
        input += pieceInput;
    }

    while (input.find("don't()") != std::string::npos) {
        if (input.find("don't()") != std::string::npos) {
            input.erase(input.find("don't()"), input.find("do()", input.find("don't()")) - input.find("don't()"));
        } else {
            break;
        }
    }

    std::smatch match;
    std::regex exp("mul\\(\\d+,\\d+\\)");
    
    while(std::regex_search(input, match, std::regex("mul\\(\\d+,\\d+\\)"))) {
        sum += doMul(match.str());
        input.erase(input.find(match.str()), match.str().size());
    }

    std::cout << sum;

    return 0;
}