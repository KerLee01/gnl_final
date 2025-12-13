#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destination;
	const char	*source;
	int			i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	destination = (char *)dest;
	source = (const char *)src;
	if (n == 0)
		return (dest);
	while (n != 0)
	{
		destination[i] = *source;
		i++;
		source++;
		n--;
	}
	return (dest);
}

char *join_str(char *stored, char *buffer, int *malloc_size, int s_length, int b_length)
{
	char *result;
	int needed;

	needed = s_length + b_length;
	if(*malloc_size <= needed)
	{
		if(*malloc_size == 0)
			*malloc_size = s_length + b_length;
		else
			*malloc_size *= 2;
		if(*malloc_size < needed)
			*malloc_size = needed;
		result = malloc(sizeof(*result) * (*malloc_size + 1));
		if(!result)
			return NULL;
		ft_memcpy(result, stored, s_length);
		free(stored);
		while(b_length > 0)
		{
			result[s_length] = *buffer;
			s_length++;
			buffer++;
			b_length--;
		}
		result[s_length] = '\0';
		return result;
	}
	while(b_length > 0)
	{
		stored[s_length] = *buffer;
		s_length++;
		buffer++;
		b_length--;
	}
	stored[s_length] = '\0';
	return stored;
}

void free_node(t_book **library, t_book *node_to_free)
{
	t_book *current;
	t_book *prev;

	current = *library;
	prev = NULL;
	while(current && current != node_to_free)
	{
		prev = current;
		current = current->next;
	}
	if(!current)
		return;
	if(prev == NULL)
		*library = current->next;
	else
		prev->next = current->next;

	free(current->str);
	free(current);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;
	char			*str;

	str = (char *)s;
	uc = (unsigned char)c;
	while (*str)
	{
		if (*str == uc % 256)
			return (str);
		str++;
	}
	if (*str == '\0' && uc == '\0')
		return (str);
	return (NULL);
}
