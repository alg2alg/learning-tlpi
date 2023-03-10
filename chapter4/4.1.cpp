#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <iostream>
#include <cstring>

#define BUFF_SIZE (1<<10)

int main(int argc, char *argv[]) {
    bool append = false;
    int ch;
    std::vector<int> fd_out;
    uint8_t buff[BUFF_SIZE];
    while ((ch = getopt(argc, argv, "a")) != -1) {
        switch (ch) {
            case 'a':
                append = true;
        }
    }
    for (int i = optind; i < argc; i++) {
        auto mode = O_WRONLY | O_CREAT;
        if (append) mode |= O_APPEND;
        else mode |= O_TRUNC;
        auto fd = open(argv[i], mode, 0666);
        if (fd == -1) {
            std::cerr << strerror(errno);
            exit(1);
        }
        fd_out.push_back(fd);
    }
    int size = 0;
    while ((size = read(STDIN_FILENO, buff, BUFF_SIZE)) > 0) {
        write(STDOUT_FILENO, buff, size);
        for (auto &fd: fd_out) {
            if (write(fd, buff, size) != size) {
                std::cerr << strerror(errno);
                exit(1);
            }
        }
    }
    return 0;
}