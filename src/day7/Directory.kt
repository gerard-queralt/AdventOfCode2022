package day7

import java.io.File

class Directory(val parent: Directory? = null) : SystemItem {
    override val size: Long
        get() {
            return contents.values.sumOf(SystemItem::size)
        }
    private val contents: MutableMap<String, SystemItem> = HashMap()

    fun addItem(itemName: String, item: SystemItem) {
        contents.putIfAbsent(itemName, item)
    }

    companion object{
        fun createDirectoriesFromInput(input: File) : Collection<Directory> {
            val dirs: MutableSet<Directory> = HashSet()
            var currentDir: Directory? = null
            input.forEachLine {line ->
                if (line[0] == '$') { //command
                    val command = line.substring(2, 4)
                    if (command == "cd") {
                        val dirName = line.substring(5)
                        currentDir = if (dirName == "..") {
                            currentDir!!.parent
                        } else {
                            //if there is a current dir, move to child
                            //else create new root
                            (currentDir?.contents?.get(dirName) ?: Directory(null)) as Directory?
                        }
                        dirs.add(currentDir!!)
                    }
                }
                else { //ls result
                    if (line.substring(0, 3) == "dir"){
                        val dirName = line.substring(4)
                        currentDir!!.addItem(dirName, Directory(currentDir))
                    }
                    else { //file
                        //note: this assumes no directory will be listed twice
                        val fileSize = line.substringBefore(" ").toLong()
                        val fileName = line.substringAfter(" ")
                        currentDir!!.addItem(fileName, File(fileSize))
                    }
                }
            }
            return dirs
        }
    }
}