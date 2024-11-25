#include "../includes/libft.h"

void *ft_memcpy(void *dst, const void *src, size_t n) {
  unsigned char *d;
  const unsigned char *s;

  d = dst;
  s = src;
  while (n--)
    *d++ = *s++;
  return (dst);
}
