#include "../includes/libft.h"

char *ft_strdup(const char *s) {
  char *dup;
  size_t len;

  len = ft_strlen(s);
  dup = (char *)malloc(len + 1);
  if (!dup)
    return (NULL);
  ft_memcpy(dup, s, len);
  dup[len] = '\0';
  return (dup);
}
