# File-system-in-C++
This assignment is to design a simple File System which makes the following assumptions:
* The File systemresides ona disk that is 128KBin size. There is only one root directory. No subdirectories are allowed. 
* The File system supports at most 16 files. 
* The maximum size of a file is 8 blocks where each block is 1KB in size. 
* Each File has a unique name.

The layout of 128 KB disk is as follows:
* The first 1KB block is called the super block. It stores the free block list and index nodes (inode) for each file. 
* The remaining 127 1KB blocks store data blocks of the files on your file system. 
* The exact structure of the super block is as follows;
* The first 128 bytes stores the free block list. Each entry in this list indicates whether the corresponding block is free or in use (if the i-th byte is 0, it indicates that the block is free, else it is in use). 
* Initially all blocks except the super block are free.Immediately following the free block list are the 16 index nodes, one for each file that is allowed in the file system. Initially, all inodesare free. 
