package day7

import java.io.File

class Directory(val parent: Directory? = null) : SystemItem {
    override val size: Long
        get() {
            return contents.sumOf(SystemItem::size)
        }
    private val contents: MutableList<SystemItem> = ArrayList()

    fun addItem(item: SystemItem) {
        contents.add(item)
    }

    companion object{
        fun createDirectoriesFromInput(input: File) : Collection<Directory> {
            val dirDictionary: MutableMap<String, Directory> = HashMap()
            var currentDir: Directory? = null
            input.forEachLine {line ->
                if (line[0] == '$') { //command
                    val command = line.substring(2, 4)
                    if (command == "cd") {
                        val dirName = line.substring(5)
                        if (dirName == "..") {
                            currentDir = currentDir!!.parent
                        }
                        else {
                            if (!dirDictionary.containsKey(dirName))
                                dirDictionary[dirName] = Directory(null)
                            currentDir = dirDictionary[dirName]
                        }
                    }
                }
                else { //ls result
                    if (line.substring(0, 3) == "dir"){
                        val dirName = line.substring(4)
                        if (!dirDictionary.containsKey(dirName)) {
                            val newDir = Directory(currentDir)
                            dirDictionary[dirName] = newDir
                            currentDir!!.addItem(newDir)
                        }
                    }
                    else { //file
                        //note: this assumes no directory will be listed twice
                        val fileSize = line.substringBefore(" ").toLong()
                        currentDir!!.addItem(File(fileSize))
                    }
                }
            }
            return dirDictionary.values
        }
    }
}