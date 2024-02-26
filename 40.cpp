#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    struct stat file_stat;

    // Get file status
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Print file permissions
    printf("File permissions for %s:\n", filename);
    printf("Owner: ");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf("\n");

    printf("Group: ");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf("\n");

    printf("Others: ");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Get user and group names
    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group *grp = getgrgid(file_stat.st_gid);

    if (pwd == NULL || grp == NULL) {
        perror("getpwuid/getgrgid");
        exit(EXIT_FAILURE);
    }

    // Print file owner and group
    printf("Owner: %s\n", pwd->pw_name);
    printf("Group: %s\n", grp->gr_name);

    return 0;
}

