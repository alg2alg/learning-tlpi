# learning-tlpi
tlpi 的课后练习



### [4.1.cpp](chapter4/4.1.cpp)

这题主要是需要学会 getopt 的使用，根据输入参数来切换文件打开方式就好了。



### [4.2.cpp](chapter4/4.2.cpp)

cp 源代码在 [coreutils](https://github.com/coreutils/coreutils) 中，在 [8.x](https://github.com/coreutils/coreutils/blob/v8.32/src/cp.c) 版本的的实现中，使用 **ioctl** + **FS_IOC_FIEMAP** 的方式来获取文件的空洞情况，而在最新的 [9.x](https://github.com/coreutils/coreutils/blob/v9.0/src/cp.c) 版本中，则使用 **lseek**+**SEEK_HOLE** 获取空洞信息，并使用 **copy_file_range** 系统调用在两个文件间复制内容，这样可以避免把文件内容从内核传输到用户空间再传输道内核中，从而加速了拷贝过程。我使用了后者的方式来实现改代码。

