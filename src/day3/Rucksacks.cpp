#include <iostream>
#include "../fileReader/CppFileReader.h"

int ValueOfItem(char item)
{
    if ('a' <= item && item <= 'z')
        //a will have value 0, b value 1, etc.
        return (int) item - 'a';
    //A will have value 26, B value 27, etc.
    return (int) item - 'A' + 26;
}

int PriorityOfDuplicatedItemsInRucksack(const std::string& rucksack)
{
    std::string firstCompartment = rucksack.substr(0, rucksack.size() / 2);
    std::string secondCompartment = rucksack.substr(rucksack.size() / 2);
    int freqItemsInFirst[52] = {0};
    int freqItemsInSecond[52] = {0};
    for (int c = 0; c < rucksack.size() / 2; ++c)
    {
        int indexItemInFirst = ValueOfItem(firstCompartment[c]);
        int indexItemInSecond = ValueOfItem(secondCompartment[c]);
        freqItemsInFirst[indexItemInFirst]++;
        freqItemsInSecond[indexItemInSecond]++;
    }
    
    int totalPriority = 0;
    for (int c = 0; c < 52; ++c)
    {
        if (freqItemsInFirst[c] != 0 &&
            freqItemsInSecond[c] != 0)
        {
            totalPriority += c + 1;
        }
    }
    return totalPriority;
}

std::vector<int> FrequencyOfItemsInRucksack(const std::string& rucksack)
{
    std::vector<int> freq(52, 0);
    for (int c = 0; c < rucksack.size(); ++c)
    {
        int itemIndex = ValueOfItem(rucksack[c]);
        freq[itemIndex]++;
    }
    return freq;
}

int PriorityOfBadge(const std::string& rucksack1,
                    const std::string& rucksack2,
                    const std::string& rucksack3)
{
    std::vector<int> freqOfRucksack1 = FrequencyOfItemsInRucksack(rucksack1);
    std::vector<int> freqOfRucksack2 = FrequencyOfItemsInRucksack(rucksack2);
    std::vector<int> freqOfRucksack3 = FrequencyOfItemsInRucksack(rucksack3);

    for (int c = 0; c < 52; ++c)
    {
        if (freqOfRucksack1[c] != 0 &&
            freqOfRucksack2[c] != 0 &&
            freqOfRucksack3[c] != 0)
        {
            //assume it can only happen once
            return c + 1;
        }
    }
    //should not happen
    return 0;
}

int main()
{
    std::vector<std::string> rucksacks = CppFileReader::InputAsLines(3);
    
    int priorityOfDuplicates = 0;
    for (std::string rucksack : rucksacks)
    {
        priorityOfDuplicates += PriorityOfDuplicatedItemsInRucksack(rucksack);
    }
    std::cout << "Part 1: " << priorityOfDuplicates << std::endl;

    int priorityOfBadges = 0;
    for (int r = 0; r < rucksacks.size(); r += 3)
    {
        priorityOfBadges += PriorityOfBadge(rucksacks[r], rucksacks[r+1], rucksacks[r+2]);
    }
    std::cout << "Part 2: " << priorityOfBadges << std::endl;
}