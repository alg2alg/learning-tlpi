# learning-tlpi
tlpi 的课后练习



### [4.1](chapter4/4.1.cpp)

这题主要是需要学会 getopt 的使用，根据输入参数来切换文件打开方式就好了。

### [4.2](chapter4/4.2.cpp)

cp 源代码在 [coreutils](https://github.com/coreutils/coreutils)
中，在 [8.x](https://github.com/coreutils/coreutils/blob/v8.32/src/cp.c) 版本的的实现中，使用 **ioctl** + **FS_IOC_FIEMAP
** 的方式来获取文件的空洞情况，而在最新的 [9.x](https://github.com/coreutils/coreutils/blob/v9.0/src/cp.c) 版本中，则使用
**lseek**+**SEEK_HOLE** 获取空洞信息，并使用 **copy_file_range**
系统调用在两个文件间复制内容，这样可以避免把文件内容从内核传输到用户空间再传输道内核中，从而加速了拷贝过程。我使用了后者的方式来实现改代码。

### [5.1](chapter5/5.1.cpp)

在我实验机器上 ( glibc 版本 2.31 ) 中，默认使用 open64 代替了open 系统调用， 在 feature.h 中可以看到 _LARGEFILE64_SOURCE
被设置为 1，这会令 open64 替代 open。因此，本题可以不作额外的设置，直接调用 open 即可访问超过 2G 的大文件。

### [5.2](chapter5/5.2.cpp)

会显示在文件末尾，因为有 append 的文件在写入数据时，会自动 lseek 到文件末尾再写入，并恢复原来的 offset
值，且该过程是原子性的，可以避免多进程同时写入操作造成的冲突覆盖。

### [5.3](chapter5/5.3.cpp)

两个文件的大小如下，可以看到 f2 文件比 f1 文件小很多，这是因为写入 f2 文件的两个进程每次 lseek 后再写入的过程并不是原子的，两个进程可能会使文件
offset 指到相同的位置，然后在相同的位置上写入，从而造成了写入的覆盖，导致总大小变小了，而加入了 append flag 后，每次写入前都会
lseek 到文件末尾再写入，且该过程是原子的，不存在覆盖写入，所以并不存在冲突问题。

```shell
$ ll f*       
-rw-r--r-- 1 alg alg  2.0M Mar 12 02:02 f1
-rw-r--r-- 1 alg alg 1005K Mar 12 02:02 f2
```



### [5.4](chapter5/5.4.cpp)

没啥难点。	



### [5.5](chapter5/5.5.cpp)

没啥难点。	



### [5.6](chapter5/5.6.cpp)

没啥难点。	