#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>

void err_exit() {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    system("echo first > temp.txt");
    int fd = open("temp.txt", O_WRONLY | O_APPEND);
    if (fd == -1) err_exit();
    if (lseek(fd, 0, SEEK_SET) == -1) err_exit();
    if (write(fd, "second", 6) == -1) err_exit();
    close(fd);
    system("more temp.txt");
}
