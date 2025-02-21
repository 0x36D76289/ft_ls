#include "../includes/ft_ls.h"

void sort_file_list(t_file_info **head, t_options *options)
{
    if (*head == NULL || (*head)->next == NULL)
        return;

    t_file_info *sorted = NULL;
    t_file_info *current = *head;
    t_file_info *next;

    while (current != NULL)
    {
        next = current->next;
        // Insert current node into sorted list
        if (sorted == NULL || (options->opt_t ? compare_time(current, sorted) <= 0 : compare_names(current, sorted) <= 0))
        {
            if (options->opt_r && sorted != NULL)
            {
                if (options->opt_t ? compare_time(current, sorted) > 0 : compare_names(current, sorted) > 0)
                {
                    current->next = sorted;
                    sorted = current;
                }
                else
                {
                    current->next = sorted;
                    sorted = current;
                }
            }
            else
            {
                current->next = sorted;
                sorted = current;
            }
        }
        else
        {
            t_file_info *temp = sorted;
            while (temp->next != NULL && (options->opt_t ? compare_time(current, temp->next) > 0 : compare_names(current, temp->next) > 0))
            {
                if (options->opt_r)
                {
                    if (options->opt_t ? compare_time(current, temp->next) < 0 : compare_names(current, temp->next) < 0)
                        break;
                }
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    *head = sorted;
}

int compare_names(t_file_info *a, t_file_info *b)
{
    return strcmp(a->name, b->name);
}

int compare_time(t_file_info *a, t_file_info *b)
{
    if (a->stat_info.st_mtime == b->stat_info.st_mtime)
        return compare_names(a, b);
    return a->stat_info.st_mtime > b->stat_info.st_mtime ? 1 : -1;
}
