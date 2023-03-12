#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

void err_exit() {
    std::cerr << strerror(errno) << std::endl;
    exit(1);
}

int my_dup(int oldfd) { return fcntl(oldfd, F_DUPFD, 0); }

int my_dup2(int oldfd, int newfd) {
    if (fcntl(oldfd, F_GETFL) == -1) {
        errno = EBADF;
    }
    if (oldfd == newfd) return oldfd;
    if (fcntl(newfd, F_GETFL) != -1) {
        close(newfd);
    }
    return fcntl(oldfd, F_DUPFD, newfd);
}

int main(int argc, char* argv[]) {
    if (my_dup2(STDOUT_FILENO, STDIN_FILENO) == -1) err_exit;
    write(STDIN_FILENO, "output info\n", 12);
}
