#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

void err_exit() {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
}

void print_all(int fd) {
    char buff[100];
    int num = pread(fd, buff, 100, 0);
    buff[num] = 0;
    std::cout << buff << std::endl;
}

int main(int argc, char* argv[]) {
    auto temp_file = "temp_file";
    auto fd1 = open(temp_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
    auto fd2 = dup(fd1);
    auto fd3 = open(temp_file, O_RDWR);
    if (fd1 == -1 || fd2 == -1 || fd3 == -1) err_exit();
    unlink(temp_file);

    write(fd1, "hello,", 6);
    print_all(fd1);

    write(fd2, "world", 6);
    print_all(fd2);

    lseek(fd2, 0, SEEK_SET);

    write(fd1, "HELLO,", 6);
    print_all(fd1);

    write(fd3, "Gidday", 6);
    print_all(fd3);

    close(fd1);
    close(fd2);
    close(fd3);
}