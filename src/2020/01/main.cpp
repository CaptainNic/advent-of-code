#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();
    const auto goal = 2020;

    // Read and parse each number
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<int> numbers;
    while (std::getline(inputFile, line)) {
        // Drop the number from the vector entirely
        // if it's over the goal number.
        // (turns out this doesn't ever happen with provided input)
        auto value = std::stoi(line);
        if (value < goal) {
            numbers.push_back(value);
        }
    }

    // Part 1
    auto t1 = std::chrono::high_resolution_clock::now();
    long p1Answer = 0;
    for (auto firstIter = numbers.cbegin(); firstIter != numbers.cend(); ++firstIter) {
        // skip, not valid
        if (*firstIter >= goal) {
            continue;
        }

        auto remaining = goal - *firstIter;
        for (auto secondIter = firstIter + 1; secondIter != numbers.cend(); ++secondIter) {
            if (*secondIter == remaining) {
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

        auto remaining = goal - *firstIter;
        for (auto secondIter = firstIter + 1; secondIter != numbers.cend(); ++secondIter) {
            // skip, not valid
            if (*secondIter >= remaining) {
                continue;
            }

            // Terrible name, but whatever, gotta go fast.
            auto remaining2 = remaining - *secondIter;
            for (auto thirdIter = secondIter + 1; thirdIter != numbers.cend(); ++thirdIter) {
                if (*thirdIter == remaining2) {
                    p2Answer = *firstIter * *secondIter * *thirdIter;
                    break;
                }
            }
        }
    }

    auto t3 = std::chrono::high_resolution_clock::now();

    auto fileLoad = std::chrono::duration_cast<std::chrono::microseconds>(t1 - start).count();
    auto p1duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto p2duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(t3 - start).count();

    std::cout
        << "File Load: " << fileLoad << "us" << std::endl
        << "Part1: " << p1Answer << " (" << p1duration << "us)" << std::endl
        << "Part2: " << p2Answer << " (" << p2duration << "us)" << std::endl
        << "Total Time: " << totalTime << "us" << std::endl;

    return 0;
}
