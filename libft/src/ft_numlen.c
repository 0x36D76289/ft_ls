#include "../includes/libft.h"

size_t ft_numlen(size_t n) {
	size_t len;

	len = 1;
	while (n /= 10)
		len++;
	return len;
}
