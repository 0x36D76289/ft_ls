#include "includes/ft_ls.h"

int main(int argc, char **argv)
{
    t_ls ls;
    int start_index;

    init_ls(&ls);
    start_index = parse_options(argc, argv, &ls);
    
    if (start_index >= argc) {
        // No arguments provided, list current directory
        handle_directory(&ls, ".");
    } else {
        parse_arguments(argc, argv, &ls, start_index);
    }

    free_files(ls.files);
    return (0);
}