package day5;

import fileReader.JavaFileReader;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Crane {
    private static List<Stack<Character>> createStacksFromInput(List<String> cratesInput){
        String lastLine = cratesInput.get(cratesInput.size() - 1);
        String lastLineNoSpaces = lastLine.replace(" ", "");
        int numberOfStacks = lastLineNoSpaces.length();
        List<Stack<Character>> crateStacks = new ArrayList<>(numberOfStacks);
        for (int s = 0; s < numberOfStacks; ++s)
            crateStacks.add(new Stack<>());

        //iterate backwards and avoid iterating last line
        for (int row = cratesInput.size() - 2; 0 <= row; --row){
            String crateRow = cratesInput.get(row);
            int stackIndex = 0;
            //start at to avoid fist bracket, advance by 4 to avoid bracket + space + bracket
            for (int i = 1; i < crateRow.length(); i += 4){
                char current = crateRow.charAt(i);
                if (current != ' ')
                    crateStacks.get(stackIndex).push(current);
                ++stackIndex;
            }
        }

        return crateStacks;
    }

    private static void executeProcedureOneByOne(List<String> procedure, List<Stack<Character>> crateStacks){
        for (String step : procedure){
            List<Integer> simpleStep = simplifyStep(step);
            int numberToMove = simpleStep.get(0);
            int from = simpleStep.get(1) - 1;
            int to = simpleStep.get(2) - 1;
            for (int n = 0; n < numberToMove; ++n){
                char crate = crateStacks.get(from).pop();
                crateStacks.get(to).push(crate);
            }
        }
    }

    private static void executeProcedureMultiMove(List<String> procedure, List<Stack<Character>> crateStacks){
        for (String step : procedure){
            List<Integer> simpleStep = simplifyStep(step);
            int numberToMove = simpleStep.get(0);
            int from = simpleStep.get(1) - 1;
            int to = simpleStep.get(2) - 1;
            Stack<Character> auxStack = new Stack<>();
            for (int n = 0; n < numberToMove; ++n){
                char crate = crateStacks.get(from).pop();
                auxStack.push(crate);
            }
            while (!auxStack.empty()){
                crateStacks.get(to).push(auxStack.pop());
            }
        }
    }

    //this method converts the step in a list of 3 ints
    private static List<Integer> simplifyStep(String step) {
        String spacesRemoved = step.replace(" ", "");
        String replaceWordsWithCommas = spacesRemoved
                .replace("move", "")
                .replace("from", ",")
                .replace("to", ",");
        List<String> splitByCommas = List.of(replaceWordsWithCommas.split(","));
        return splitByCommas
                .stream()
                .map(Integer::parseInt)
                .toList();
    }

    public static void main(String[] args) throws FileNotFoundException {
        File inputFile = JavaFileReader.readInputOfDay(5);
        Scanner in = new Scanner(inputFile);

        List<String> crates = new ArrayList<>();
        List<String> procedure = new ArrayList<>();

        //fill the crates list while blank line not found
        while (in.hasNextLine()){
            String line = in.nextLine();
            if (line.isEmpty())
                break;
            crates.add(line);
        }
        //fill the procedure list with the rest
        while (in.hasNextLine()){
            procedure.add(in.nextLine());
        }
        in.close();

        List<Stack<Character>> crateStacks = createStacksFromInput(crates);

        List<Stack<Character>> crateStacksCopy = deepCopy(crateStacks);
        executeProcedureOneByOne(procedure, crateStacksCopy);
        System.out.println("Part 1: ");
        for (Stack<Character> crateStack : crateStacksCopy)
            System.out.print(crateStack.peek());
        System.out.println();

        crateStacksCopy = deepCopy(crateStacks);
        executeProcedureMultiMove(procedure, crateStacksCopy);
        System.out.println("Part 2: ");
        for (Stack<Character> crateStack : crateStacksCopy)
            System.out.print(crateStack.peek());
        System.out.println();
    }

    private static List<Stack<Character>> deepCopy(List<Stack<Character>> crateStacks) {
        return crateStacks
                .stream()
                .map(Stack::clone)
                .map(o -> (Stack<Character>) o)
                .toList();
    }
}
