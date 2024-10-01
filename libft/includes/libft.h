/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdessoy- <fdessoy-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:48:59 by fdessoy-          #+#    #+#             */
/*   Updated: 2024/08/29 13:04:56 by fdessoy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
t_list	*ft_lstnew(void *content);
int		ft_atoi(const char *s);
void	ft_bzero(void *s, size_t n);
void	free_array(char **array);
int		ft_isalnum(int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *str, int c, size_t len);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isdigit(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strncat(char *dst, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strnstr(const char *s, const char *find, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_mod(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
char	*ft_strsjoin(const char *s1, const char *s2, const char sep);

/* gnl */
# ifndef GET_NEXT_LINE_H
#  define GET_NEXT_LINE_H

#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 10
#  endif

typedef struct s_lista
{
	char			*str_buf;
	struct s_lista	*next;
}					t_lista;
char	*get_next_line(int fd);
int		len_till_nl(t_lista *list);
int		got_new_line(t_lista *list);
char	*get_line(t_lista *list);
void	ft_append(t_lista **list, char *buf);
void	copy_str(t_lista *list, char *str);
void	create_list(t_lista **list, int fd);
void	clean_the_list(t_lista **list);
void	dealloc(t_lista **list, t_lista *clean_node, char *buf);
t_lista	*ft_listlast(t_lista *list);

# endif

/* ft_printf */
# ifndef FT_PRINTF_H
#  define FT_PRINTF_H

int		ft_printf(const char *format, ...);
int		ft_str(char *s, int *check);
int		ft_char(int c, int *check);
int		ft_nbr(int n, int *check);
int		ft_unsig_nbr(unsigned int n, int *check);
int		format_check(const char *format, va_list args, int *check);
int		ft_hex(unsigned long n, int caps, int *check);
int		ft_pointer(void *ptr, int *check);

# endif
#endif
