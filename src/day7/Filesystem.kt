package day7

import fileReader.KotlinFileReader

fun main() {
    //TODO: does not work, incorrectly assumed directory names are unique
    //at least that's where I think the issue is
    val input = KotlinFileReader.readInputOfDay(7)
    val dirs: Collection<Directory> = Directory.createDirectoriesFromInput(input)
    val part1: Long = dirs.map(Directory::size).filter { it <= 100000 }.sum()
    println("Part 1: $part1")
}