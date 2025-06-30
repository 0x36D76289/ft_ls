#include "../include/ft_ls.h"

void print_error(char *program, char *file, char *message)
{
    ft_putstr_fd(program, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    if (file)
    {
        ft_putstr_fd(file, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putstr_fd(message, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

void print_errno_error(char *program, char *file)
{
    ft_putstr_fd(program, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    if (file)
    {
        ft_putstr_fd(file, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putstr_fd(strerror(errno), STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}
