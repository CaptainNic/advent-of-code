/**
 * --- Day 2: Password Philosophy ---
 * Your flight departs in a few days from the coastal airport; the easiest way down to the coast from here is via toboggan.
 * 
 * The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day. "Something's wrong with our computers; we can't log in!" You ask if you can take a look.
 * 
 * Their password database seems to be a little corrupted: some of the passwords wouldn't have been allowed by the Official Toboggan Corporate Policy that was in effect when they were chosen.
 * 
 * To try to debug the problem, they have created a list (your puzzle input) of passwords (according to the corrupted database) and the corporate policy when that password was set.
 * 
 * For example, suppose you have the following list:
 * 
 * 1-3 a: abcde
 * 1-3 b: cdefg
 * 2-9 c: ccccccccc
 * Each line gives the password policy and then the password. The password policy indicates the lowest and highest number of times a given letter must appear for the password to be valid. For example, 1-3 a means that the password must contain a at least 1 time and at most 3 times.
 * 
 * In the above example, 2 passwords are valid. The middle password, cdefg, is not; it contains no instances of b, but needs at least 1. The first and third passwords are valid: they contain one a or nine c, both within the limits of their respective policies.
 * 
 * How many passwords are valid according to their policies?
 * 
 * --- Part Two ---
 * While it appears you validated the passwords correctly, they don't seem to be what the Official Toboggan Corporate Authentication System is expecting.
 * 
 * The shopkeeper suddenly realizes that he just accidentally explained the password policy rules from his old job at the sled rental place down the street! The Official Toboggan Corporate Policy actually works a little differently.
 * 
 * Each policy actually describes two positions in the password, where 1 means the first character, 2 means the second character, and so on. (Be careful; Toboggan Corporate Policies have no concept of "index zero"!) Exactly one of these positions must contain the given letter. Other occurrences of the letter are irrelevant for the purposes of policy enforcement.
 * 
 * Given the same example list from above:
 * 
 * 1-3 a: abcde is valid: position 1 contains a and position 3 does not.
 * 1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
 * 2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.
 * How many passwords are valid according to the new interpretation of the policies?
 **/
#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();

    // Read file
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<std::string> inputs;
    while (std::getline(inputFile, line)) {
        inputs.push_back(line);
    }

    auto t1 = std::chrono::high_resolution_clock::now();

    // Part 1
    auto p1Answer = 0;
    const auto regex = std::regex("([0-9]*)-([0-9]*) ([a-zA-Z]): (.*)");
    for (auto input : inputs) {
        std::smatch matches;
        std::regex_match(input, matches, regex);
        
        // Don't barf
        if (matches.size() != 5) {
            std::cout << "[SKIP | Bad Input] " << input << std::endl;
            continue;
        }

        const auto min = std::stoi(matches[1]);
        const auto max = std::stoi(matches[2]);
        const auto letter = matches[3].str()[0];
        const auto password = matches[4].str();

        auto letterCount = 0;
        for (auto idx = 0; idx < password.length(); ++idx) {
            if (password[idx] == letter) {
                letterCount++;
            }
        }

        if (letterCount >= min && letterCount <= max) {
            p1Answer++;
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    // Part 2
    auto p2Answer = 0;
    for (auto input : inputs) {
        std::smatch matches;
        std::regex_match(input, matches, regex);

        // Don't barf
        if (matches.size() != 5) {
            std::cout << "[SKIP | Bad Input] " << input << std::endl;
            continue;
        }

        // values are not one-indexed, so we offset them to be zero-indexed.
        const auto pos1 = std::stoi(matches[1]) - 1;
        const auto pos2 = std::stoi(matches[2]) - 1;
        const auto letter = matches[3].str()[0];
        const auto password = matches[4].str();

        // Since the validity is only valid if one of the positions matches the letter,
        // we can just flip the valid bool on each match as an XOR.
        bool valid = false;
        if (password[pos1] == letter) {
            valid = !valid;
        }
        if (password[pos2] == letter) {
            valid = !valid;
        }

        if (valid) {
            p2Answer++;
        }
    }

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