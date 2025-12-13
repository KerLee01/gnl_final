#include "get_next_line.h"
#include <stdio.h>

char *read_more(int fd, char *stored, char **nl_found)
{
	int bytes;
	char *buffer;
	int stored_bytes;
	int malloc_size;

	if(!stored)
	{
		stored = malloc(1);
		stored[0] = '\0';
	}
	stored_bytes = ft_strlen(stored);
	malloc_size = stored_bytes;
	*nl_found = ft_strchr(stored, '\n');
	while(*nl_found == NULL)
	{
		buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
		if(buffer == NULL)
			return (free(stored), NULL);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if(bytes == 0)
		{	if(stored[0] != '\0')
				return (free(buffer), stored);
			return (free(buffer), free(stored), NULL);
		}
		if(bytes == -1)
			return (free(buffer), free(stored), NULL);
		buffer[bytes] = '\0';
		stored = join_str(stored, buffer, &malloc_size, stored_bytes, bytes);
		if(!stored)
			return NULL;
		free(buffer);
		*nl_found = ft_strchr(stored + stored_bytes, '\n');
		stored_bytes += bytes;
	}
	return stored;
}

char *find_line(char *stored, char *nl_found)
{
    char *line;
    int i;
    int len;

    if (!stored || !*stored)
        return (NULL);

    if (nl_found)
        len = (int)(nl_found - stored) + 1;
    else
        len = ft_strlen(stored);

    line = malloc(sizeof(char) * (len + 1));
    if (!line)
        return (NULL);

    i = 0;
    while (i < len)
    {
        line[i] = stored[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char *update_stored(char *stored, char *nl_found)
{
	char *updated;
	int i;

	i = 0;
	if(nl_found == NULL)
		return (free(stored), NULL);
	nl_found++;
	if(nl_found[0] == '\0')
		return (free(stored), NULL);
	updated = malloc(sizeof(*updated) * (ft_strlen(nl_found) + 1));
	if(updated == NULL)
		return (free(stored), NULL);
	while(*nl_found != '\0')
	{
		updated[i] = *nl_found;
		i++;
		nl_found++;
	}
	updated[i] = '\0';
	free(stored);
	return updated;
}

t_book *find_book(int fd, t_book **library)
{
	t_book *current;

	current = *library;
	while(current != NULL)
	{
		if(current->fd == fd)
			return current;
		current = current->next;
	}
	current = malloc(sizeof(t_book));
	if(!current)
		return (NULL);
	current->fd = fd;
	current->str = malloc(1);
	if(current->str == NULL)
	{
		free(current);
		return (NULL);
	}
	current->str[0] = '\0';
	current->next = *library;
	*library = current;
	return current;
}

char *get_next_line(int fd)
{
	static t_book *book = NULL;
	t_book *current;
	char *line;
	char *nl_found;
	char *buffer;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	nl_found = NULL;
	current = find_book(fd, &book);
	if(current == NULL)
		return (NULL);
	buffer = read_more(fd, current->str, &nl_found);
	if(buffer == NULL)
	{
		current->str = NULL;
		return (free_node(&book, current), NULL);
	}
	line = find_line(buffer, nl_found);
	if(line == NULL)
		return (free_node(&book, current), NULL);
	current->str = update_stored(buffer, nl_found);

	return line;
}
