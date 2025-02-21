#include "../includes/ft_ls.h"

int main(int argc, char **argv)
{
    t_options options = {false, false, false, false, false};
    int i;
    int file_count = 0;

    parse_options(argc, argv, &options);

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
            file_count++;
    }

    if (file_count == 0)
        list_directory(".", &options);
    else
    {
        for (i = 1; i < argc; i++)
        {
            if (argv[i][0] != '-')
            {
                struct stat statbuf;
                if (lstat(argv[i], &statbuf) == -1)
                {
                    handle_error(argv[i]);
                    continue;
                }
                if (S_ISDIR(statbuf.st_mode))
                    list_directory(argv[i], &options);
                else
                {
                    t_file_info *file = get_file_info(".", argv[i]);
                    if (file)
                    {
                        print_file_info(file, &options);
                        free_file_info_list(file);
                    }
                }
            }
        }
    }

    return 0;
}