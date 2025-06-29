#include "../include/ft_ls.h"

t_file	*create_file_node(char *name, char *path)
{
	t_file	*new_file;

	new_file = malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	
	new_file->name = ft_strdup(name);
	new_file->path = ft_strdup(path);
	if (!new_file->name || !new_file->path)
	{
		free(new_file->name);
		free(new_file->path);
		free(new_file);
		return (NULL);
	}

	if (lstat(path, &new_file->stat) == -1)
	{
		free(new_file->name);
		free(new_file->path);
		free(new_file);
		return (NULL);
	}

	new_file->next = NULL;
	return (new_file);
}

static void	add_file_to_list(t_file **files, t_file *new_file)
{
	t_file	*current;

	if (!*files)
	{
		*files = new_file;
		return;
	}
	
	current = *files;
	while (current->next)
		current = current->next;
	current->next = new_file;
}

t_file	*get_file_list(char *dir_path, t_options *options)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*files;
	t_file			*new_file;
	char			*full_path;

	dir = opendir(dir_path);
	if (!dir)
	{
		print_errno_error("ft_ls", dir_path);
		return (NULL);
	}

	files = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		if (!(options->flags & OPT_A) && is_hidden_file(entry->d_name))
			continue;

		full_path = join_path(dir_path, entry->d_name);
		if (!full_path)
			continue;

		new_file = create_file_node(entry->d_name, full_path);
		free(full_path);
		if (new_file)
			add_file_to_list(&files, new_file);
	}

	closedir(dir);
	return (files);
}

void	free_file_list(t_file *files)
{
	t_file	*current;
	t_file	*next;

	current = files;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->path);
		free(current);
		current = next;
	}
}
