#include "get_next_line.h"
#include <stdio.h>

char *read_more(int fd, char *stored, char **nl_found)
{
	int bytes;
	char *buffer;
	int stored_bytes;
	int malloc_size;

	if(!stored)
		return NULL;
	stored_bytes = ft_strlen(stored);
	malloc_size = stored_bytes;
	*nl_found = ft_strchr(stored, '\n');
	while(*nl_found == NULL)
	{
		buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
		if(buffer == NULL)
			return NULL;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if(bytes == 0)
		{	if(stored[0] != '\0')
				return (free(buffer), stored);
			return (free(buffer), NULL);
		}
		if(bytes == -1)
			return (free(buffer), NULL);
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

	i = 0;
	line = NULL;
	if(nl_found == NULL && stored != NULL)
		return stored;
	if(nl_found == NULL && stored == NULL)
		return NULL;
	line = malloc(sizeof(*line) * (ft_strlen(stored) - ft_strlen(nl_found) + 2));
	if(!line)
		return NULL;
	while(*stored != '\n')
	{
		line[i] = *stored;
		i++;
		stored++;
	}
	if(*stored == '\n')
		line[i] = '\n';
	line[i] = '\0';
	return line;
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
	t_book *start;
	char *str;

	current = *library;
	start = *library;
	while(current != NULL)
	{
		if(current->fd == fd)
			return current;
		current = current->next;
	}
	current = malloc(sizeof(t_book));
	if(!current)
		return (free_all_nodes(library), NULL);
	current->fd = fd;
	str = malloc(1);
	if(!str)
		return (free_all_nodes(library), NULL);
	str[0] = '\0';
	current->str = str;
	current->next = start;
	return current;
}

char *get_next_line(int fd)
{
	static t_book *book = NULL;
	t_book *current;
	char *line;
	char *nl_found;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	nl_found = NULL;
	current = find_book(fd, &book);
	if(current == NULL)
		return (NULL);
	current->str = read_more(fd, current->str, &nl_found);
	if(current->str == NULL)
	{
		printf("here\n");
		return (free_node(&book, current), NULL);
	}
	line = find_line(current->str, nl_found);
	if(line == NULL)
		return (free_node(&book, current), NULL);
	current->str = update_stored(current->str, nl_found);

	return line;
}
