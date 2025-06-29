#include "../include/ft_ls.h"

int	main(int argc, char **argv)
{
	t_options	options;
	char		**paths;
	int			path_count;
	int			i;
	int			j;

	options.flags = 0;
	path_count = parse_options(argc, argv, &options);
	if (path_count == -1)
		return (1);
	
	if (path_count == 0)
	{
		paths = malloc(sizeof(char *) * 2);
		if (!paths)
			return (1);
		paths[0] = ".";
		paths[1] = NULL;
	}
	else
	{
		paths = malloc(sizeof(char *) * (path_count + 1));
		if (!paths)
			return (1);
		j = 0;
		i = 1;
		while (i < argc)
		{
			if (!is_option(argv[i]))
			{
				paths[j] = argv[i];
				j++;
			}
			i++;
		}
		paths[path_count] = NULL;
	}
	
	ft_ls(paths, &options);
	free(paths);
	return (0);
}
