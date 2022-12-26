#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void print_prem(struct stat stats);

int main(int argc, char **argv)
{
    printf("\n");
    struct dirent *idir = NULL;
    struct stat stats;
    struct passwd *usr;
    struct group *grp;
    char my_path[300] = {0};
    char *t_d = NULL;
    DIR *my_dir;
    strcpy(my_path, argv[1]);
    my_dir = opendir(my_path);
    if (my_dir == NULL)
        return 1;
    int rev;
    while ((idir = readdir(my_dir)) != NULL)
    {
        sprintf(my_path, "%s/%s", argv[1], idir->d_name);
        rev = stat(my_path, &stats);
        if ((stats.st_mode & S_IFMT) == S_IFDIR)
            continue;
        if (rev == 0)
        {
            t_d = ctime(&stats.st_mtime);
            usr = getpwuid(stats.st_uid);
            grp = getgrgid(stats.st_gid);
            print_prem(stats);
            printf(" %lu", stats.st_nlink);
            printf(" %s", usr->pw_name);
            printf(" %s", grp->gr_name);
            printf(" %ld", stats.st_size);
            printf(" ");
            for (int i = 0; i < 16; i++)
                printf("%c", t_d[i]);
            printf(" %s", idir->d_name);
            printf("\n");
        }
        else
            return 2;
    }
}

void print_prem(struct stat stats)
{
    {
        if (S_ISDIR(stats.st_mode))
            printf("d");
        else
            printf("-");
        if (stats.st_mode & S_IRUSR)
            printf("r");
        else
            printf("-");
        if (stats.st_mode & S_IWUSR)
            printf("w");
        else
            printf("-");
        if (stats.st_mode & S_IXUSR)
            printf("x");
        else
            printf("-");
        if (stats.st_mode & S_IRGRP)
            printf("r");
        else
            printf("-");
        if (stats.st_mode & S_IWGRP)
            printf("w");
        else
            printf("-");
        if (stats.st_mode & S_IXGRP)
            printf("x");
        else
            printf("-");
        if (stats.st_mode & S_IROTH)
            printf("r");
        else
            printf("-");
        if (stats.st_mode & S_IWOTH)
            printf("w");
        else
            printf("-");
        if (stats.st_mode & S_IXOTH)
            printf("x");
        else
            printf("-");
    }
}