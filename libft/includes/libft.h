#ifndef LIBFT_H
#define LIBFT_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *ft_memcpy(void *dst, const void *src, size_t n);
size_t ft_numlen(size_t n);
void ft_putchar(int c);
void ft_putnbr(int n);
void ft_putstr_fd(const char *s, int fd);
void ft_putstr(const char *s);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strcpy(char *dst, const char *src);
char *ft_strdup(const char *s);
size_t ft_strlen(const char *s);

#endif