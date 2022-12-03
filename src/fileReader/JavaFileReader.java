package fileReader;

import java.io.File;

public class JavaFileReader {
    public static File readInputOfDay(int day){
        File dayPath = new File("src", "day" + day);
        return new File(dayPath + File.separator + "input.txt");
    }
}
