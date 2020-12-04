/**
 * This is a template for each challenge.
 * 
 **/
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();

    // Read file
    std::ifstream inputFile("input.txt");
    std::string line;
    auto data = std::make_unique<std::vector<std::string>>();
    while (std::getline(inputFile, line)) {
        data->push_back(std::move(line));
    }
    inputFile.close();

    auto t1 = std::chrono::high_resolution_clock::now();

    // Part 1
    auto p1Answer = 0;

    auto t2 = std::chrono::high_resolution_clock::now();

    // Part 2
    auto p2Answer = 0;

    auto t3 = std::chrono::high_resolution_clock::now();

    auto fileLoad = std::chrono::duration_cast<std::chrono::microseconds>(t1 - start).count();
    auto p1duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto p2duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(t3 - start).count();

    std::cout
        << std::endl
        << "File Load: " << fileLoad << "us" << std::endl
        << "Part1: " << p1Answer << " (" << p1duration << "us)" << std::endl
        << "Part2: " << p2Answer << " (" << p2duration << "us)" << std::endl
        << "Total Time: " << totalTime << "us" << std::endl;
}