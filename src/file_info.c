#include "../includes/ft_ls.h"

size_t get_username_width(struct passwd *pw, uid_t uid)
{
    if (pw != NULL)
        return strlen(pw->pw_name);
    char uid_str[32];
    return snprintf(uid_str, sizeof(uid_str), "%d", uid);
}

size_t get_groupname_width(struct group *gr, gid_t gid)
{
    if (gr != NULL)
        return strlen(gr->gr_name);
    char gid_str[32];
    return snprintf(gid_str, sizeof(gid_str), "%d", gid);
}

t_file_info *get_file_info(const char *path, const char *name)
{
    t_file_info *file = (t_file_info *)malloc(sizeof(t_file_info));
    if (file == NULL)
    {
        handle_error("Memory allocation failed");
        return NULL;
    }

    file->name = strdup(name);
    if (file->name == NULL)
    {
        handle_error("Memory allocation failed (strdup)");
        free(file);
        return NULL;
    }

    file->path = malloc(strlen(path) + strlen(name) + 2);
    if (file->path == NULL)
    {
        handle_error("Memory allocation failed (path)");
        free(file->name);
        free(file);
        return NULL;
    }

    strcpy(file->path, path);
    if (path[strlen(path) - 1] != '/')
        strcat(file->path, "/");
    strcat(file->path, name);

    if (lstat(file->path, &file->stat_info) == -1)
    {
        handle_error(file->path);
        free(file->path);
        free(file->name);
        free(file);
        return NULL;
    }
    file->next = NULL;
    return file;
}

void print_file_info(t_file_info *file, t_options *options)
{
    if (options->opt_l)
        print_long_format(file);
    else
        printf("%s  ", file->name);
}

void print_long_format(t_file_info *file)
{
    struct passwd *pw = getpwuid(file->stat_info.st_uid);
    struct group *gr = getgrgid(file->stat_info.st_gid);
    char time_str[20];
    char *time_format;
    char size_str[32];

    // Format the size string with appropriate units
    snprintf(size_str, sizeof(size_str), "%lld", (long long)file->stat_info.st_size);

    // Permissions (fixed width of 10 characters + space)
    printf((S_ISDIR(file->stat_info.st_mode)) ? "d" : "-");
    printf((file->stat_info.st_mode & S_IRUSR) ? "r" : "-");
    printf((file->stat_info.st_mode & S_IWUSR) ? "w" : "-");
    printf((file->stat_info.st_mode & S_IXUSR) ? "x" : "-");
    printf((file->stat_info.st_mode & S_IRGRP) ? "r" : "-");
    printf((file->stat_info.st_mode & S_IWGRP) ? "w" : "-");
    printf((file->stat_info.st_mode & S_IXGRP) ? "x" : "-");
    printf((file->stat_info.st_mode & S_IROTH) ? "r" : "-");
    printf((file->stat_info.st_mode & S_IWOTH) ? "w" : "-");
    printf((file->stat_info.st_mode & S_IXOTH) ? "x" : "-");
    printf("  ");

    // Number of hard links (right-aligned, minimum 4 characters)
    printf("%4lu ", (unsigned long)file->stat_info.st_nlink);

    // User name and group name (with 2 spaces between them)
    if (pw != NULL)
        printf("%-8s  ", pw->pw_name);
    else
        printf("%-8d  ", file->stat_info.st_uid);

    if (gr != NULL)
        printf("%-8s  ", gr->gr_name);
    else
        printf("%-8d  ", file->stat_info.st_gid);

    // File size (right-aligned, minimum 8 characters)
    printf("%8s ", size_str);

    // Time format
    time_t now = time(NULL);
    if (file->stat_info.st_mtime > now - (6 * 30 * 24 * 60 * 60) && file->stat_info.st_mtime <= now)
        time_format = "%b %e %H:%M";
    else
        time_format = "%b %e  %Y";
    strftime(time_str, sizeof(time_str), time_format, localtime(&file->stat_info.st_mtime));
    printf("%s ", time_str);

    // File name
    printf("%s", file->name);

    // Symbolic link
    if (S_ISLNK(file->stat_info.st_mode))
    {
        char link_target[1024];
        ssize_t len = readlink(file->path, link_target, sizeof(link_target) - 1);
        if (len != -1)
        {
            link_target[len] = '\0';
            printf(" -> %s", link_target);
        }
    }

    printf("\n");
}

void free_file_info_list(t_file_info *head)
{
    t_file_info *current = head;
    t_file_info *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->name);
        free(current->path);
        free(current);
        current = next;
    }
}