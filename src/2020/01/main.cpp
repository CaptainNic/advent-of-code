#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    const auto goal = 2020;

    // Read and parse each number
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<int> numbers;
    while (std::getline(inputFile, line)) {
        numbers.push_back(std::stoi(line));
    }

    // Part 1
    auto t1 = std::chrono::high_resolution_clock::now();
    long p1Answer = 0;
    for (auto firstIter = numbers.cbegin(); firstIter != numbers.cend(); ++firstIter) {
        // skip, not valid
        if (*firstIter >= goal) {
            continue;
        }

        for (auto secondIter = firstIter + 1; secondIter != numbers.cend(); ++secondIter) {
            if (*firstIter + *secondIter == goal) {
                p1Answer = *firstIter * *secondIter;
                break;
            }
        }
    }

    // Part 2
    auto t2 = std::chrono::high_resolution_clock::now();
    long p2Answer = 0;
    for (auto firstIter = numbers.cbegin(); firstIter != numbers.cend(); ++firstIter) {
        // skip, not valid
        if (*firstIter >= goal) {
            continue;
        }

        for (auto secondIter = firstIter + 1; secondIter != numbers.cend(); ++secondIter) {
            // skip, not valid
            if (*firstIter + *secondIter >= goal) {
                continue;
            }

            for (auto thirdIter = secondIter + 1; thirdIter != numbers.cend(); ++thirdIter) {
                if (*firstIter + *secondIter + *thirdIter == goal) {
                    p2Answer = *firstIter * *secondIter * *thirdIter;
                    break;
                }
            }
        }
    }

    auto t3 = std::chrono::high_resolution_clock::now();

    auto p1duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto p2duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();

    std::cout
        << "Part1: " << p1Answer << " (" << p1duration << "us)" << std::endl
        << "Part2: " << p2Answer << " (" << p2duration << "us)" << std::endl;

    return 0;
}
