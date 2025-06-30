#include "../include/ft_ls.h"

static void process_recursive(t_file *files, t_options *options)
{
    t_file *current;

    current = files;
    while (current)
    {
        if (S_ISDIR(current->stat.st_mode))
        {
            if (ft_strcmp(current->name, ".") != 0 && ft_strcmp(current->name, "..") != 0)
            {
                ft_putstr_fd("\n", 1);
                ft_putstr_fd(current->path, 1);
                ft_putstr_fd(":\n", 1);
                list_directory(current->path, options);
            }
        }
        current = current->next;
    }
}

int list_directory(char *path, t_options *options)
{
    t_file *files;
    struct stat path_stat;

    if (stat(path, &path_stat) == -1)
    {
        print_errno_error("ft_ls", path);
        return (1);
    }

    if ((options->flags & OPT_D) && S_ISDIR(path_stat.st_mode))
    {
        files = create_file_node(path, path);
        if (!files)
            return (1);
        display_files(files, options);
        free_file_list(files);
        return (0);
    }

    if (!S_ISDIR(path_stat.st_mode))
    {
        files = create_file_node(path, path);
        if (!files)
            return (1);
        display_files(files, options);
        free_file_list(files);
        return (0);
    }

    files = get_file_list(path, options);
    if (!files)
        return (1);

    sort_files(&files, options);
    display_files(files, options);

    if (options->flags & OPT_R)
        process_recursive(files, options);

    free_file_list(files);
    return (0);
}

int ft_ls(char **paths, t_options *options)
{
    int i;
    int error;
    int multiple_paths;

    i = 0;
    error = 0;
    multiple_paths = 0;

    while (paths[i])
    {
        i++;
        if (i > 1)
            multiple_paths = 1;
    }

    i = 0;
    while (paths[i])
    {
        if (multiple_paths)
        {
            // if (i > 0)
                // ft_putstr_fd("\n", 1);
            ft_putstr_fd(paths[i], 1);
            ft_putstr_fd(":\n", 1);
        }
        if (list_directory(paths[i], options) != 0)
            error = 1;
        i++;
    }
    return (error);
}
