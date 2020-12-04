/**
 * --- Day 3: Toboggan Trajectory ---
 * With the toboggan login problems resolved, you set off toward the airport. 
 * While travel by toboggan might be easy, it's certainly not safe: there's
 * very minimal steering and the area is covered in trees. You'll need to
 * see which angles will take you near the fewest trees.
 * 
 * Due to the local geology, trees in this area only grow on exact integer
 * coordinates in a grid. You make a map (your puzzle input) of the open 
 * squares (.) and trees (#) you can see. For example:
 * 
 * ..##.......
 * #...#...#..
 * .#....#..#.
 * ..#.#...#.#
 * .#...##..#.
 * ..#.##.....
 * .#.#.#....#
 * .#........#
 * #.##...#...
 * #...##....#
 * .#..#...#.#
 * These aren't the only trees, though; due to something you read about once 
 * involving arboreal genetics and biome stability, the same pattern repeats 
 * to the right many times:
 * 
 * ..##.........##.........##.........##.........##.........##.......  --->
 * #...#...#..#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..
 * .#....#..#..#....#..#..#....#..#..#....#..#..#....#..#..#....#..#.
 * ..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#
 * .#...##..#..#...##..#..#...##..#..#...##..#..#...##..#..#...##..#.
 * ..#.##.......#.##.......#.##.......#.##.......#.##.......#.##.....  --->
 * .#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#
 * .#........#.#........#.#........#.#........#.#........#.#........#
 * #.##...#...#.##...#...#.##...#...#.##...#...#.##...#...#.##...#...
 * #...##....##...##....##...##....##...##....##...##....##...##....#
 * .#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#  --->
 * You start on the open square (.) in the top-left corner and need to reach 
 * the bottom (below the bottom-most row on your map).
 * 
 * The toboggan can only follow a few specific slopes (you opted for a cheaper 
 * model that prefers rational numbers); start by counting all the trees you 
 * would encounter for the slope right 3, down 1:
 * 
 * From your starting position at the top-left, check the position that is 
 * right 3 and down 1. Then, check the position that is right 3 and down 1 
 * from there, and so on until you go past the bottom of the map.
 * 
 * The locations you'd check in the above example are marked here with O 
 * where there was an open square and X where there was a tree:
 * 
 * ..##.........##.........##.........##.........##.........##.......  --->
 * #..O#...#..#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..
 * .#....X..#..#....#..#..#....#..#..#....#..#..#....#..#..#....#..#.
 * ..#.#...#O#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#
 * .#...##..#..X...##..#..#...##..#..#...##..#..#...##..#..#...##..#.
 * ..#.##.......#.X#.......#.##.......#.##.......#.##.......#.##.....  --->
 * .#.#.#....#.#.#.#.O..#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#
 * .#........#.#........X.#........#.#........#.#........#.#........#
 * #.##...#...#.##...#...#.X#...#...#.##...#...#.##...#...#.##...#...
 * #...##....##...##....##...#X....##...##....##...##....##...##....#
 * .#..#...#.#.#..#...#.#.#..#...X.#.#..#...#.#.#..#...#.#.#..#...#.#  --->
 * In this example, traversing the map using this slope would cause you to 
 * encounter 7 trees.
 * 
 * Starting at the top-left corner of your map and following a slope of right 
 * 3 and down 1, how many trees would you encounter?
 * 
 * --- Part Two ---
 * Time to check the rest of the slopes - you need to minimize the probability
 * of a sudden arboreal stop, after all.
 * 
 * Determine the number of trees you would encounter if, for each of the 
 * following slopes, you start at the top-left corner and traverse the map all
 * the way to the bottom:
 * 
 * Right 1, down 1.
 * Right 3, down 1. (This is the slope you already checked.)
 * Right 5, down 1.
 * Right 7, down 1.
 * Right 1, down 2.
 * In the above example, these slopes would find 2, 7, 3, 4, and 2 tree(s) 
 * respectively; multiplied together, these produce the answer 336.
 * 
 * What do you get if you multiply together the number of trees encountered on
 * each of the listed slopes?
 **/

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Map
{
public:
    Map(std::unique_ptr<std::vector<std::string>> data)
        : m_width(data->at(0).length())
        , m_height(data->size())
        , m_data(std::move(data))
        , m_x(0)
        , m_y(0)
    {}

    size_t countTrees(size_t dx, size_t dy)
    {
        reset();

        size_t trees = 0;
        while (m_y < m_height - 1) {
            trees += move(dx, dy);
        }
        
        return trees;
    }

private:
    void reset() { m_x = 0; m_y = 0; }

    // returns true if new position is on a tree
    bool move(int dx, int dy)
    {
        m_x = (m_x + dx) % m_width;
        m_y = m_y + dy;
        if (m_y >= m_height) {
            m_y = m_height - 1;
        }

        return m_data->at(m_y).at(m_x) == '#';
    }

    const size_t m_width;    // wrap width
    const size_t m_height;
    size_t m_x;
    size_t m_y;
    std::unique_ptr<std::vector<std::string>> m_data;
};

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
    Map map(std::move(data));
    auto p1Answer = map.countTrees(3, 1);

    auto t2 = std::chrono::high_resolution_clock::now();

    // Part 2
    auto p2Answer = map.countTrees(1, 1)
        * p1Answer
        * map.countTrees(5, 1)
        * map.countTrees(7, 1)
        * map.countTrees(1, 2);


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