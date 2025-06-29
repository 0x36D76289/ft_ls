#include "../include/ft_ls.h"

char	*join_path(char *dir, char *name)
{
	char	*result;
	char	*temp;
	int		dir_len;

	if (!dir || !name)
		return (NULL);

	dir_len = ft_strlen(dir);
	
	if (dir_len > 0 && dir[dir_len - 1] == '/')
		return (ft_strjoin(dir, name));
	else
	{
		temp = ft_strjoin(dir, "/");
		if (!temp)
			return (NULL);
		result = ft_strjoin(temp, name);
		free(temp);
		return (result);
	}
}

int	is_hidden_file(char *name)
{
	return (name && name[0] == '.');
}

char	get_file_type(mode_t mode)
{
	if (S_ISDIR(mode))
		return (TYPE_DIR);
	else if (S_ISLNK(mode))
		return (TYPE_LINK);
	else if (S_ISCHR(mode))
		return (TYPE_CHR);
	else if (S_ISBLK(mode))
		return (TYPE_BLK);
	else if (S_ISFIFO(mode))
		return (TYPE_FIFO);
	else if (S_ISSOCK(mode))
		return (TYPE_SOCK);
	else
		return (TYPE_REG);
}
