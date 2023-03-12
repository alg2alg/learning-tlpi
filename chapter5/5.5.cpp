#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

void err_exit() {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
}

int main(int argc, char* argv[]) {
    auto temp_file = "temp_file";
    auto fd1 = open(temp_file, O_RDWR | O_CREAT | O_APPEND, 0666);
    if (fd1 == -1) err_exit();
    if (unlink(temp_file) == -1) err_exit();
    auto fd2 = dup(fd1);
    if (fd2 == -1) err_exit();

    auto flag1 = fcntl(fd1, F_GETFL);
    if (flag1 == -1) err_exit();
    flag1 &= ~O_APPEND;
    if (fcntl(fd1, F_SETFL, flag1) == -1) err_exit();
    auto flag2 = fcntl(fd2, F_GETFL);
    if (flag2 == -1) err_exit();
    if (flag1 == flag2) {
        std::cout << "falg same\n";
    } else {
        std::cout << int(flag1 & O_APPEND) << " " << int(flag2 & O_APPEND)
                  << " flag not same\n";
    }

    auto fd1_off = 10, fd2_off = 0;
    if (lseek(fd1, fd1_off, SEEK_SET) == -1) err_exit();
    if ((fd2_off = lseek(fd1, fd1_off, SEEK_SET)) == -1) err_exit();
    if (fd1_off == fd2_off) {
        std::cout << "offset same\n";
    } else {
        std::cout << "offset not same\n";
    }

    close(fd1);
    close(fd2);
}
