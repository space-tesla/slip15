Q.1) Display all the files from the current directory whose size is greater than n Bytes, where n is accepted from the user

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char *directory = "."; // Current directory
    long n;

    printf("Enter the size (in bytes): ");
    scanf("%ld", &n);

    dir = opendir(directory);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Files larger than %ld bytes:\n", n);
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            if (fileStat.st_size > n) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}

Output:
Enter the size (in bytes): 1000
Files larger than 1000 bytes:
largefile.txt
anotherfile.dat
