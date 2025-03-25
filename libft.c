#include "sh.h"

static int	ft_wordcount(char const *s, char c)
{
	int	step;
	int	word_count;

	step = 0;
	word_count = 0;
	while (s[step] != '\0')
	{
		if (s[step] != c)
		{
			word_count++;
			while (s[step] != c && s[step] != '\0')
				step++;
			if (s[step] == '\0')
				return (word_count);
		}
		step++;
	}
	return (word_count);
}

static void	ft_strcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	while (src[count] != '\0' && count < size)
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
}

static char	*ft_wordcpy(const char *s, char c, int *head)
{
	int		len;
	int		start_index;
	char	*str;

	len = 0;
	while (s[*head] != '\0')
	{
		if (s[*head] != c)
		{
			start_index = *head;
			while (s[*head] != c && s[*head] != '\0')
			{
				len++;
				*head = *head + 1;
			}
		}
		break ;
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strcpy(str, &s[start_index], len);
	return (str);
}

char	**ft_split(const char *s, char c)
{
	int		step;
	int		head;
	int		word_count;
	char	**result;

	head = 0;
	step = 0;
	word_count = ft_wordcount(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[head] != '\0' && step < word_count)
	{
		if (s[head] != c)
		{
			result[step] = ft_wordcpy(s, c, &head);
			step++;
		}
		if (s[head] == '\0')
			break ;
		head++;
	}
	result[step] = NULL;
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s && s[count])
	{
		count++;
	}
	return (count);
}

static int	ft_cmpchar(char c1, char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	while (s1[count] && s2[count] && count < n)
	{
		if (ft_cmpchar(s1[count], s2[count]))
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	if (count < n)
		return (ft_cmpchar(s1[count], s2[count]));
	return (0);
}
