#include "sh.h"

int ft_strcmp(const char* s1, const char* s2)
{
	size_t	len;

	len = ft_strlen(s2);
	return (ft_strncmp(s1, s2, len));
}
