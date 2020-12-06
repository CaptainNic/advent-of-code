/**
 * --- Day 5: Binary Boarding ---
 * You board your plane only to discover a new problem: you dropped your boarding pass! You aren't sure which seat is yours, and all of the flight attendants are busy with the flood of people that suddenly made it through passport control.
 * 
 * You write a quick program to use your phone's camera to scan all of the nearby boarding passes (your puzzle input); perhaps you can find your seat through process of elimination.
 * 
 * Instead of zones or groups, this airline uses binary space partitioning to seat people. A seat might be specified like FBFBBFFRLR, where F means "front", B means "back", L means "left", and R means "right".
 * 
 * The first 7 characters will either be F or B; these specify exactly one of the 128 rows on the plane (numbered 0 through 127). Each letter tells you which half of a region the given seat is in. Start with the whole list of rows; the first letter indicates whether the seat is in the front (0 through 63) or the back (64 through 127). The next letter indicates which half of that region the seat is in, and so on until you're left with exactly one row.
 * 
 * For example, consider just the first seven characters of FBFBBFFRLR:
 * 
 * Start by considering the whole range, rows 0 through 127.
 * F means to take the lower half, keeping rows 0 through 63.
 * B means to take the upper half, keeping rows 32 through 63.
 * F means to take the lower half, keeping rows 32 through 47.
 * B means to take the upper half, keeping rows 40 through 47.
 * B keeps rows 44 through 47.
 * F keeps rows 44 through 45.
 * The final F keeps the lower of the two, row 44.
 * The last three characters will be either L or R; these specify exactly one of the 8 columns of seats on the plane (numbered 0 through 7). The same process as above proceeds again, this time with only three steps. L means to keep the lower half, while R means to keep the upper half.
 * 
 * For example, consider just the last 3 characters of FBFBBFFRLR:
 * 
 * Start by considering the whole range, columns 0 through 7.
 * R means to take the upper half, keeping columns 4 through 7.
 * L means to take the lower half, keeping columns 4 through 5.
 * The final R keeps the upper of the two, column 5.
 * So, decoding FBFBBFFRLR reveals that it is the seat at row 44, column 5.
 * 
 * Every seat also has a unique seat ID: multiply the row by 8, then add the column. In this example, the seat has ID 44 * 8 + 5 = 357.
 * 
 * Here are some other boarding passes:
 * 
 * BFFFBBFRRR: row 70, column 7, seat ID 567.
 * FFFBBBFRRR: row 14, column 7, seat ID 119.
 * BBFFBBFRLL: row 102, column 4, seat ID 820.
 * As a sanity check, look through your list of boarding passes. What is the highest seat ID on a boarding pass?
 * 
 * --- Part Two ---
 * Ding! The "fasten seat belt" signs have turned on. Time to find your seat.
 * 
 * It's a completely full flight, so your seat should be the only missing boarding pass in your list. However, there's a catch: some of the seats at the very front and back of the plane don't exist on this aircraft, so they'll be missing from your list as well.
 * 
 * Your seat wasn't at the very front or back, though; the seats with IDs +1 and -1 from yours will be in your list.
 * 
 * What is the ID of your seat?
 **/
#include <algorithm>
#include <bitset>
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
    std::vector<std::string> entries;
    while (std::getline(inputFile, line)) {
        // This is just binary w/ F/L as 0 and B/R as 1.
        // BFFFBBF RRR: row 70, column 7, seat ID 567.
        // 1000110 111 -->  70,        7
        std::replace(line.begin(), line.end() - 3, 'B', '1');
        std::replace(line.begin(), line.end() - 3, 'F', '0');
        std::replace(line.end() - 3, line.end(), 'R', '1');
        std::replace(line.end() - 3, line.end(), 'L', '0');
        entries.push_back(std::move(line));
    }
    inputFile.close();

    auto t1 = std::chrono::high_resolution_clock::now();

    // Part 1
    std::bitset<0x3FF> seatMap;
    auto p1Answer = 0;
    for (auto entry : entries) {
        // seat ID : multiply the row by 8, then add the column
        //  ... this is the same as row << 3  + col
        //  ... or just leaving the bitset<10> alone.
        std::bitset<10> seat(entry);
        auto seatId = seat.to_ulong();
        seatMap.set(seatId);
        if (seatId > p1Answer) {
            p1Answer = seatId;
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    // Part 2
    auto p2Answer = 0;
    auto mapAsString = seatMap.to_string();

    // the seats with IDs +1 and -1 from yours will be in your list
    size_t pos = 1;
    while (pos < mapAsString.length() - 1) {
        if (mapAsString[pos - 1] == '1' && mapAsString[pos + 1] == '1') {
            // We're reading from MSB but want the positing from LSB.
            p2Answer = mapAsString.length() - pos - 1;
            break;
        }
        pos = mapAsString.find('0', pos + 1);
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