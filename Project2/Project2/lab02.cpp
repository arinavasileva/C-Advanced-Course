// Lab02.cpp by Arina Vasileva

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

int main() {
    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 37);

    // Generate two sets of 7 unique lotto numbers
    std::vector<int> lotto1, lotto2;
    while (lotto1.size() < 7) {
        int num = dist(gen);
        if (std::find(lotto1.begin(), lotto1.end(), num) == lotto1.end()) lotto1.push_back(num);
    }
    while (lotto2.size() < 7) {
        int num = dist(gen);
        if (std::find(lotto2.begin(), lotto2.end(), num) == lotto2.end()) lotto2.push_back(num);
    }

    // Print both sets using output stream iterator
    std::cout << "First lotto row: ";
    std::copy(lotto1.begin(), lotto1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nSecond lotto row: ";
    std::copy(lotto2.begin(), lotto2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Find common numbers
    std::sort(lotto1.begin(), lotto1.end());
    std::sort(lotto2.begin(), lotto2.end());
    std::vector<int> common_numbers;
    std::set_intersection(lotto1.begin(), lotto1.end(), lotto2.begin(), lotto2.end(), std::back_inserter(common_numbers));

    // Print common numbers using for_each
    std::cout << "Same numbers:\n";
    int idx = 1;
    std::for_each(common_numbers.begin(), common_numbers.end(), [&idx](int num) {
        std::cout << "#" << idx++ << ": " << num << std::endl;
        });

    return 0;
}