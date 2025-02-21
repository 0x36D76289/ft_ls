#include "../includes/ft_ls.h"

void parse_options(int argc, char **argv, t_options *options)
{
    int i, j;

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            for (j = 1; argv[i][j] != '\0'; j++)
            {
                switch (argv[i][j])
                {
                case 'l':
                    options->opt_l = true;
                    break;
                case 'R':
                    options->opt_R = true;
                    break;
                case 'a':
                    options->opt_a = true;
                    break;
                case 'r':
                    options->opt_r = true;
                    break;
                case 't':
                    options->opt_t = true;
                    break;
                default:
                    fprintf(stderr, "ft_ls: illegal option -- %c\n", argv[i][j]);
                    fprintf(stderr, "usage: ft_ls [-lRart] [file ...]\n");
                    exit(1);
                }
            }
        }
    }
}