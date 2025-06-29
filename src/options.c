#include "../include/ft_ls.h"

static int	parse_option_char(char c, t_options *options)
{
	if (c == 'l')
		options->flags |= OPT_L;
	else if (c == 'R')
		options->flags |= OPT_R;
	else if (c == 'a')
		options->flags |= OPT_A;
	else if (c == 'r')
		options->flags |= OPT_REV;
	else if (c == 't')
		options->flags |= OPT_T;
	else
	{
		ft_putstr_fd("ft_ls: invalid option -- '", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
		return (-1);
	}
	return (0);
}

static int	parse_option_string(char *arg, t_options *options)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (parse_option_char(arg[i], options) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	is_option(char *arg)
{
	return (arg && arg[0] == '-' && arg[1]);
}

int	parse_options(int argc, char **argv, t_options *options)
{
	int	i;
	int	path_count;

	i = 1;
	path_count = 0;
	while (i < argc)
	{
		if (is_option(argv[i]))
		{
			if (parse_option_string(argv[i], options) == -1)
				return (-1);
		}
		else
			path_count++;
		i++;
	}
	return (path_count);
}
