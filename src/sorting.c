#include "../include/ft_ls.h"

static int compare_files(t_file *a, t_file *b, t_options *options)
{
    int result;

    if (options->flags & OPT_F) // If -f option is set, do not sort
        return (0);

    if (options->flags & OPT_T)
    {
        time_t time_a, time_b;

        if (options->flags & OPT_U)
        {
            time_a = a->stat.st_atime;
            time_b = b->stat.st_atime;
        }
        else
        {
            time_a = a->stat.st_mtime;
            time_b = b->stat.st_mtime;
        }

        if (time_a > time_b)
            result = -1;
        else if (time_a < time_b)
            result = 1;
        else
            result = ft_strcmp(a->name, b->name);
    }
    else if (options->flags & OPT_U && !(options->flags & OPT_L))
    {
        time_t time_a = a->stat.st_atime;
        time_t time_b = b->stat.st_atime;

        if (time_a > time_b)
            result = -1;
        else if (time_a < time_b)
            result = 1;
        else
            result = ft_strcmp(a->name, b->name);
    }
    else
        result = ft_strcmp(a->name, b->name);

    return (result);
}

static void swap_files(t_file *a, t_file *b)
{
    char *temp_name;
    char *temp_path;
    struct stat temp_stat;

    temp_name = a->name;
    temp_path = a->path;
    temp_stat = a->stat;

    a->name = b->name;
    a->path = b->path;
    a->stat = b->stat;

    b->name = temp_name;
    b->path = temp_path;
    b->stat = temp_stat;
}

static void bubble_sort(t_file **files, t_options *options)
{
    t_file *current;
    int swapped;

    if (!files || !*files)
        return;

    do
    {
        swapped = 0;
        current = *files;

        while (current && current->next)
        {
            if (compare_files(current, current->next, options) > 0)
            {
                swap_files(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

void reverse_list(t_file **files)
{
    t_file *prev;
    t_file *current;
    t_file *next;

    prev = NULL;
    current = *files;

    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *files = prev;
}

void sort_files(t_file **files, t_options *options)
{
    if (!files || !*files)
        return;

    if (options->flags & OPT_F)
        return;

    bubble_sort(files, options);

    if (options->flags & OPT_REV)
        reverse_list(files);
}
