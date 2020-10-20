// Ex. 4
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]) {
    DIR *dirp = opendir(".");
    if (dirp == NULL) {
        printf("Error opening current directory\n");
        return 1;
    }

    struct dirent *entry;
    struct stat file_info;
    while ((entry = readdir(dirp)) != NULL) {
        stat(entry->d_name, &file_info);
        // Assuming that all the hard links are in the current directory
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..") && file_info.st_nlink >= 2) {
            printf("Inode: %ld, filename: %s, %ld hard links\n", entry->d_ino, entry->d_name, file_info.st_nlink);
        }
    }

    closedir(dirp);
    return 0;
}
