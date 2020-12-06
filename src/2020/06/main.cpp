/**
 * --- Day 6: Custom Customs ---
 * As your flight approaches the regional airport where you'll switch to a much larger plane, customs declaration forms are distributed to the passengers.
 * 
 * The form asks a series of 26 yes-or-no questions marked a through z. All you need to do is identify the questions for which anyone in your group answers "yes". Since your group is just you, this doesn't take very long.
 * 
 * However, the person sitting next to you seems to be experiencing a language barrier and asks if you can help. For each of the people in their group, you write down the questions for which they answer "yes", one per line. For example:
 * 
 * abcx
 * abcy
 * abcz
 * In this group, there are 6 questions to which anyone answered "yes": a, b, c, x, y, and z. (Duplicate answers to the same question don't count extra; each question counts at most once.)
 * 
 * Another group asks for your help, then another, and eventually you've collected answers from every group on the plane (your puzzle input). Each group's answers are separated by a blank line, and within each group, each person's answers are on a single line. For example:
 * 
 * abc
 * 
 * a
 * b
 * c
 * 
 * ab
 * ac
 * 
 * a
 * a
 * a
 * a
 * 
 * b
 * This list represents answers from five groups:
 * 
 * The first group contains one person who answered "yes" to 3 questions: a, b, and c.
 * The second group contains three people; combined, they answered "yes" to 3 questions: a, b, and c.
 * The third group contains two people; combined, they answered "yes" to 3 questions: a, b, and c.
 * The fourth group contains four people; combined, they answered "yes" to only 1 question, a.
 * The last group contains one person who answered "yes" to only 1 question, b.
 * In this example, the sum of these counts is 3 + 3 + 3 + 1 + 1 = 11.
 * 
 * For each group, count the number of questions to which anyone answered "yes". What is the sum of those counts?
 * 
 * --- Part Two ---
 * As you finish the last group's customs declaration, you notice that you misread one word in the instructions:
 * 
 * You don't need to identify the questions to which anyone answered "yes"; you need to identify the questions to which everyone answered "yes"!
 * 
 * Using the same example as above:
 * 
 * abc
 * 
 * a
 * b
 * c
 * 
 * ab
 * ac
 * 
 * a
 * a
 * a
 * a
 * 
 * b
 * This list represents answers from five groups:
 * 
 * In the first group, everyone (all 1 person) answered "yes" to 3 questions: a, b, and c.
 * In the second group, there is no question to which everyone answered "yes".
 * In the third group, everyone answered yes to only 1 question, a. Since some people did not answer "yes" to b or c, they don't count.
 * In the fourth group, everyone answered yes to only 1 question, a.
 * In the fifth group, everyone (all 1 person) answered "yes" to 1 question, b.
 * In this example, the sum of these counts is 3 + 0 + 1 + 1 + 1 = 6.
 * 
 * For each group, count the number of questions to which everyone answered "yes". What is the sum of those counts?
 **/

#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

size_t countAllAnsweredYes(const std::vector<std::bitset<26>>& groupAnswers) {
    std::bitset<26> allAnsweredYes;
    allAnsweredYes.set();
    for (auto individualAnswers : groupAnswers) {
        allAnsweredYes &= individualAnswers;
    }

    return allAnsweredYes.count();
}

int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();

    // Read file
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<std::string> inputData;
    bool startNextEntry = true;
    while (std::getline(inputFile, line)) {
        inputData.push_back(line);
    }
    inputFile.close();

    auto t1 = std::chrono::high_resolution_clock::now();

    // Part 1 & 2
    auto p1Answer = 0;
    auto p2Answer = 0;
    std::vector<std::bitset<26>> groupAnswers;
    for (auto data : inputData) {
        if (data.length() == 0) {
            // End of group, update P2 answer and reset.
            p2Answer += countAllAnsweredYes(groupAnswers);
            groupAnswers.clear();
            continue;
        }

        std::bitset<26> answers;
        for each (auto question in data)
        {
            answers.set(question - 'a'); // offset values so 'a' is 0 and 'z' is 25
        }

        // Update P1 answer & add to group for P2 answer.
        p1Answer += answers.count();
        groupAnswers.push_back(std::move(answers));
    }

    // Don't forget the last group
    p2Answer += countAllAnsweredYes(groupAnswers);

    auto t2 = std::chrono::high_resolution_clock::now();

    auto fileLoad = std::chrono::duration_cast<std::chrono::microseconds>(t1 - start).count();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - start).count();

    std::cout
        << std::endl
        << "File Load: " << fileLoad << "us" << std::endl
        << "Part1: " << p1Answer << ", Part2: " << p2Answer << " (" << duration << "us)" << std::endl
        << "Total Time: " << totalTime << "us" << std::endl;
}