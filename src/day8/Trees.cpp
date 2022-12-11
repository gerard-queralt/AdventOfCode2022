#include <iostream>
#include <set>
#include "../fileReader/CppFileReader.h"

std::vector<std::vector<int> > trees;
std::set<std::pair<int, int> > visibleTrees;

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

void FindVisibleTrees()
{
    int nCol = trees.size();
    int nRow = trees[0].size();
    for (int i = 1; i < nCol - 1; ++i)
    {
        for (int j = 1; j < nRow - 1; ++j)
        {
            if (IsTreeVisible(i, j))
                visibleTrees.insert(std::make_pair(i, j));
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
    FindVisibleTrees();

    std::cout << "Part 1: " << visibleTrees.size() << std::endl;
}