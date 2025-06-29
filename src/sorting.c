#include "../include/ft_ls.h"

static int	compare_files(t_file *a, t_file *b, t_options *options)
{
	int	result;

	if (options->flags & OPT_T)
	{
		if (a->stat.st_mtime > b->stat.st_mtime)
			result = -1;
		else if (a->stat.st_mtime < b->stat.st_mtime)
			result = 1;
		else
			result = ft_strcmp(a->name, b->name);
	}
	else
		result = ft_strcmp(a->name, b->name);

	return (result);
}

static void	swap_files(t_file *a, t_file *b)
{
	char		*temp_name;
	char		*temp_path;
	struct stat	temp_stat;

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

static void	bubble_sort(t_file *files, t_options *options)
{
	int		swapped;
	t_file	*current;
	t_file	*last;

	if (!files)
		return;

	last = NULL;
	do
	{
		swapped = 0;
		current = files;
		while (current->next != last)
		{
			if (compare_files(current, current->next, options) > 0)
			{
				swap_files(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	} while (swapped);
}

void	reverse_list(t_file **files)
{
	t_file	*prev;
	t_file	*current;
	t_file	*next;

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

void	sort_files(t_file **files, t_options *options)
{
	if (!files || !*files)
		return;

	bubble_sort(*files, options);

	if (options->flags & OPT_REV)
		reverse_list(files);
}
