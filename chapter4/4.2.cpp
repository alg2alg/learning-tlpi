#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>

void err_exit(){
    std::cerr << strerror(errno) << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "arg cnt not match\n";
        exit(1);
    }
    int src_fd = open(argv[1], O_RDONLY);
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(src_fd == -1 || dest_fd == -1) err_exit();
    struct stat st;
    if(fstat(src_fd, &st) == -1) err_exit();
    if(ftruncate(dest_fd, st.st_size) == -1)err_exit();

    off_t in_offset = 0, out_offset = 0;
    while (true) {
        auto next_hole = lseek(src_fd, in_offset, SEEK_HOLE);
        if (next_hole == -1) {
            if (errno == ENXIO)  break;
            err_exit();
        }
        if(copy_file_range(src_fd, &in_offset, dest_fd, &out_offset, next_hole - in_offset, 0) == -1) {
            std::cerr << strerror(errno) << std::endl;
            exit(1);
        }
        auto next_data = lseek(src_fd, in_offset, SEEK_DATA);
        if (next_data == -1) {
            if (errno == ENXIO) break;
            err_exit();
        }
        out_offset = in_offset = next_data;
    }
    return 0;
}