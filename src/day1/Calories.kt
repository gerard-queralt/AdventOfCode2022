package day1

import fileReader.KotlinFileReader
import java.io.File

fun main() {
    val input = KotlinFileReader.readInputOfDay(1)

    val calories = getCaloriesFromInput(input)
    val sortedCalories = calories.sorted().reversed()

    val topOne = sortedCalories[0]
    println("Part 1: $topOne")
    val topThree = topOne + sortedCalories[1] + sortedCalories[2]
    println("Part 2: $topThree")
}

fun getCaloriesFromInput(input: File): List<Long> {
    val calories = ArrayList<Long>()
    var currentCalories = 0L

    input.forEachLine {line ->
        if (line.isNotEmpty())
            currentCalories += line.toLong()
        else {
            calories.add(currentCalories)
            currentCalories = 0L
        }
    }

    return calories
}
