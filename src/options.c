#include "../include/ft_ls.h"

static int parse_option_char(char c, t_options *options)
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
    else if (c == 'u')
        options->flags |= OPT_U;
    else if (c == 'f')
    {
        options->flags |= OPT_F;
        options->flags |= OPT_A;  // -f enables -a
        options->flags &= ~OPT_L; // -f disables -l
        options->flags &= ~OPT_COLOR; // -f disables --color
    }
    else if (c == 'g')
    {
        options->flags |= OPT_G;
        options->flags |= OPT_L;  // -g enables long format like -l
    }
    else if (c == 'd')
        options->flags |= OPT_D;
    else if (c == 'G')
        options->flags |= OPT_COLOR;
    else
    {
        ft_putstr_fd("ft_ls: invalid option -- '", STDERR_FILENO);
        ft_putchar_fd(c, STDERR_FILENO);
        ft_putstr_fd("'\n", STDERR_FILENO);
        return (-1);
    }
    return (0);
}

static int parse_option_string(char *arg, t_options *options)
{
    int i;

    i = 1;
    while (arg[i])
    {
        if (parse_option_char(arg[i], options) == -1)
            return (-1);
        i++;
    }
    return (0);
}

int is_option(char *arg)
{
    return (arg && arg[0] == '-' && arg[1]);
}

int parse_options(int argc, char **argv, t_options *options)
{
    int i;
    int path_count;

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
