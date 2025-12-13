#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_book
{
   int fd;
   char *str;
   struct s_book *next;
} t_book;

char *join_str(char *stored, char *buffer, int *malloc_size, int s_length, int b_length);
void free_node(t_book **library, t_book *node_to_free);
void free_all_nodes(t_book **library);
void *ft_memcpy(void *dest, const void *src, size_t n);
char *ft_strchr(const char *s, int c);
size_t ft_strlen(const char *s);
char *get_next_line(int fd);

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#endif

