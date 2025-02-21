#include "../includes/ft_ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void handle_error(const char *message)
{
    if (message)
        fprintf(stderr, "ft_ls: %s: %s\n", message, strerror(errno));
    else
        fprintf(stderr, "ft_ls: %s\n", strerror(errno));
}