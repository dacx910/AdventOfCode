#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void sort(std::vector<int>& nums) {
    bool sorted = true;
    for (int i = 0; i < nums.size()-1; ++i) {
        if (nums.at(i+1) < nums.at(i)) {
            sorted = false;
            int temp;
            temp = nums.at(i);
            nums.at(i) = nums.at(i+1);
            nums.at(i+1) = temp;
        }
    }
    
    if (!sorted) {
        sort(nums);
    }
}

int main() {
    std::ifstream fileInput("input.txt");

    std::vector<int> num1(1000);
    std::vector<int> num2(1000);

    int a, b;
    for (int i = 0; i < 1000; ++i) {
        fileInput >> a >> b;
        num1.at(i) = a;
        num2.at(i) = b;
    }

    sort(num1);
    sort(num2);

    int distance = 0;
    for (int i = 0; i < num1.size(); ++i) {
        distance += abs(num1.at(i) - num2.at(i));
    }
    std::cout << distance << "\n";
}
