#include "../includes/ft_ls.h"

void list_directory(const char *path, t_options *options)
{
    DIR *dir;
    struct dirent *entry;
    t_file_info *file_list = NULL;
    t_file_info *current = NULL;
    t_file_info *new_file = NULL;

    if ((dir = opendir(path)) == NULL)
    {
        handle_error(path);
        return;
    }

    if (options->opt_R || opendir(path) == NULL)
        printf("%s:\n", path);

    while ((entry = readdir(dir)) != NULL)
    {
        if (!options->opt_a && entry->d_name[0] == '.')
            continue;

        new_file = get_file_info(path, entry->d_name);
        if (new_file == NULL)
            continue; 

        if (file_list == NULL)
        {
            file_list = new_file;
            current = file_list;
        }
        else
        {
            current->next = new_file;
            current = new_file;
        }
    }

    closedir(dir);

    sort_file_list(&file_list, options);

    current = file_list;
    while (current != NULL)
    {
        print_file_info(current, options);
        current = current->next;
    }
    if (!options->opt_l)
        printf("\n");

    if (options->opt_R)
    {
        current = file_list;
        while (current != NULL)
        {
            if (S_ISDIR(current->stat_info.st_mode) && strcmp(current->name, ".") != 0 && strcmp(current->name, "..") != 0)
            {
                char *newPath = malloc(strlen(path) + strlen(current->name) + 2);
                if (!newPath)
                    handle_error("Memory allocation failed in recursive");

                strcpy(newPath, path);
                if (path[strlen(path) - 1] != '/')
                    strcat(newPath, "/");
                strcat(newPath, current->name);
                printf("\n");
                list_directory(newPath, options);
                free(newPath);
            }
            current = current->next;
        }
    }
    free_file_info_list(file_list);
}