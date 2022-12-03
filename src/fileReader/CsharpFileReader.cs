public class CsharpFileReader
{
    public static string ReadInputOfDay(int day){
        string dayInputPath = ".\\src\\day" + day + "\\input.txt";
        return System.IO.File.ReadAllText(dayInputPath);
    }
}