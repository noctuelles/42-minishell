/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:01:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/02/11 19:02:08 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>

# define TRUE  1
# define FALSE 0

# define STDIN  0
# define STDOUT 1
# define STDERR 2

typedef uint8_t		t_bool;
typedef uint64_t	t_index;
typedef int64_t		t_sindex;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/* ###### Memory related functions ###### */

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);

/* Allocation related functions */

void	*ft_calloc(size_t nmemb, size_t size);

/* Un-official additional functions */

/* ###### String related functions ###### */

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strncat(char *dest, const char *src, size_t nb);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);

char	*ft_straddc(char **s, char stop, char c, size_t n);
char	*ft_straddbc(char **s, char c, size_t n);
char	*ft_straddec(char **s, char c, size_t n);

char	*ft_straddbs(char **s, const char *add);
char	*ft_straddes(char **s, const char *add);

char	*ft_strnew_nchar(char c, size_t n);
char	*ft_strnew_chars(size_t n, ...);

char	*ft_itoa(int n);
char	*ft_itoa_base(int64_t n, const char *base);
char	*ft_itoa_ubase(uint64_t n, const char *base);

int		ft_atoi(const char *nptr);

/* Official additional functions (on libft's pdf) */

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinc(const char *s1, const char *s2, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/* Un-official additional custom functions */

/* ###### Input / Input functions ###### */

void	ft_putchar_fd(char c, int fd);
void	ft_putchar(int c);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putstr(const char *s);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_base_fd(int64_t n, const char *base, int fd);
void	ft_putbin_fd(int64_t n, size_t nbits, int fd);

/* Un-official additional custom functions */

/* ###### ASCII functions ###### */

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_toupper(int c);
int		ft_tolower(int c);

/* Un-official additional custom functions */

/* ###### Bonus - List functions ###### */

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstadd_back_ret_last(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstclear_nocnt_alloc(t_list **lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
