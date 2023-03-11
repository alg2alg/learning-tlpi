#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>

void err_exit() {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        std::cerr << "argc not match\n";
        exit(1);
    }
    auto mode = O_WRONLY | O_CREAT | O_TRUNC | O_APPEND;
    bool append = true;
    if (argc == 4 && strcmp(argv[3], "x") == 0) {
        append = false;
        mode &= ~O_APPEND;
    }
    int fd = open(argv[1], mode, 0666);
    if (fd == -1) err_exit();
    int n_bytes = atoi(argv[2]);
    for (int i = 0; i < n_bytes; ++i) {
        if (!append) lseek(fd, 0, SEEK_END);
        write(fd, "\0", 1);
    }
    close(fd);
}
