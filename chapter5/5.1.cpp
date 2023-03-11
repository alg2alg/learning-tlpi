#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>

void err_exit() {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
#ifdef __USE_LARGEFILE64
    std::cout << "define __USE_LARGEFILE64 " << __USE_LARGEFILE64 << std::endl;
#endif
    if (argc != 3) {
        std::cerr << "agrc != 3\n";
        exit(1);
    }
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) err_exit();
    auto offset = atoll(argv[2]);
    if (lseek(fd, offset, SEEK_SET) == -1) err_exit();
    if (write(fd, "test", 4) == -1) err_exit();
    close(fd);
}
