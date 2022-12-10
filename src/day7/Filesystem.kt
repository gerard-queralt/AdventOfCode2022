package day7

import fileReader.KotlinFileReader

fun main() {
    val input = KotlinFileReader.readInputOfDay(7)
    val dirs: Collection<Directory> = Directory.createDirectoriesFromInput(input)
    val dirSizes: List<Long> = dirs.map(Directory::size)
    val part1: Long = dirSizes.filter { it <= 100000 }.sum()
    println("Part 1: $part1")
    val totalMem: Long = 70000000
    val unusedMem = totalMem - dirSizes.max()
    val neededMem: Long = 30000000
    val sizeOfDirToDelete = dirSizes.sorted().find { neededMem <= unusedMem + it }
    println("Part 2: $sizeOfDirToDelete")
}