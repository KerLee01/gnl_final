#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char *line;
	int fd;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	while(line != NULL)
	{
		printf("line: %s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}
