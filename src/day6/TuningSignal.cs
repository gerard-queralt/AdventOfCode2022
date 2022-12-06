using System.Collections.Generic;
using System.Linq;

public class TuningSignal
{
    public static void Run()
    {
        string input = CsharpFileReader.ReadInputOfDay(6);
        Console.Write("Part 1: " + CharsUntilMarker(input, 4));
        Console.Write("Part 2: " + CharsUntilMarker(input, 14));
    }

    private static int CharsUntilMarker(string datastream, int sizeOfMarker)
    {
        List<char> checkedSoFar = new List<char>();
        List<char> lastN = new List<char>(sizeOfMarker);
        for (int c = 0; c < sizeOfMarker; ++c)
        {
            checkedSoFar.Add(datastream[c]);
            lastN.Add(datastream[c]);
        }
        for (int c = sizeOfMarker; c < datastream.Length && !IsMarker(lastN); ++c){
            checkedSoFar.Add(datastream[c]);
            lastN.RemoveAt(0);
            lastN.Add(datastream[c]);
        }
        return checkedSoFar.Count;
    }

    private static bool IsMarker(List<char> lastFour){
        //check all are unique
        return lastFour.GroupBy(c => c).All(g => g.Count() == 1);
    }
}