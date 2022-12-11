#include <iostream>
#include <set>
#include "../fileReader/CppFileReader.h"

std::vector<std::vector<int> > trees;
std::set<std::pair<int, int> > visibleTrees;
int maxScenicScore = 0;

void MarkBordersAsVisible()
{
    int nCol = trees.size();
    int nRow = trees[0].size();
    for(int i = 0; i < nCol; ++i){
        visibleTrees.insert(std::make_pair(i, 0));
        visibleTrees.insert(std::make_pair(i, nRow - 1));
    }
    for(int j = 0; j < nRow; ++j){
        visibleTrees.insert(std::make_pair(0, j));
        visibleTrees.insert(std::make_pair(nCol - 1, j));
    }
}

bool IsTreeVisible(int col, int row)
{
    int nCol = trees.size();
    int nRow = trees[0].size();
    int tree = trees[col][row];
    
    //down
    bool visibleFromCurrentSide = true;
    for (int i = col + 1; i < nCol && visibleFromCurrentSide; ++i)
    {
        int current = trees[i][row];
        if (tree <= current)
            visibleFromCurrentSide = false;
    }
    if (visibleFromCurrentSide)
        return true;
    
    //up
    visibleFromCurrentSide = true;
    for (int i = col - 1; 0 <= i && visibleFromCurrentSide; --i)
    {
        int current = trees[i][row];
        if (tree <= current)
            visibleFromCurrentSide = false;
    }
    if (visibleFromCurrentSide)
        return true;

    //right
    visibleFromCurrentSide = true; 
    for (int j = row + 1; j < nRow && visibleFromCurrentSide; ++j)
    {
        int current = trees[col][j];
        if (tree <= current)
            visibleFromCurrentSide = false;
    }
    if (visibleFromCurrentSide)
        return true;

    //left
    visibleFromCurrentSide = true;
    for (int j = row - 1; 0 <= j && visibleFromCurrentSide; --j)
    {
        int current = trees[col][j];
        if (tree <= current)
            visibleFromCurrentSide = false;
    }
    return visibleFromCurrentSide;
}

int ComputeScenicScoreOfTree(int col, int row)
{
    int nCol = trees.size();
    int nRow = trees[0].size();
    int tree = trees[col][row];
    
    //down
    bool notBlocked = true;
    int scoreDown = 0;
    for (int i = col + 1; i < nCol && notBlocked; ++i)
    {
        ++scoreDown;
        int current = trees[i][row];
        if (tree <= current)
            notBlocked = false;
    }
    
    //up
    notBlocked = true;
    int scoreUp = 0;
    for (int i = col - 1; 0 <= i && notBlocked; --i)
    {
        ++scoreUp;
        int current = trees[i][row];
        if (tree <= current)
            notBlocked = false;
    }

    //right
    notBlocked = true;
    int scoreRight = 0;
    for (int j = row + 1; j < nRow && notBlocked; ++j)
    {
        ++scoreRight;
        int current = trees[col][j];
        if (tree <= current)
            notBlocked = false;
    }

    //left
    notBlocked = true;
    int scoreLeft = 0;
    for (int j = row - 1; 0 <= j && notBlocked; --j)
    {
        ++scoreLeft;
        int current = trees[col][j];
        if (tree <= current)
            notBlocked = false;
    }
    return scoreDown * scoreUp * scoreRight * scoreLeft;
}

void IterateTrees()
{
    int nCol = trees.size();
    int nRow = trees[0].size();
    for (int i = 1; i < nCol - 1; ++i)
    {
        for (int j = 1; j < nRow - 1; ++j)
        {
            //part 1
            if (IsTreeVisible(i, j))
                visibleTrees.insert(std::make_pair(i, j));

            //part 2
            int scenicScore = ComputeScenicScoreOfTree(i, j);
            maxScenicScore = std::max(maxScenicScore, scenicScore);
        }
    }
}

int main()
{
    std::vector<std::string> treeLines = CppFileReader::InputAsLines(8);
    for (std::string line : treeLines)
    {
        std::vector<int> lineAsInts;
        for (char c : line)
        {
            lineAsInts.push_back(c - '0');
        }
        trees.push_back(lineAsInts);
    }

    MarkBordersAsVisible();
    IterateTrees();

    std::cout << "Part 1: " << visibleTrees.size() << std::endl;
    std::cout << "Part 2: " << maxScenicScore << std::endl;
}