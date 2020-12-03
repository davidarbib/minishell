/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:15:53 by darbib            #+#    #+#             */
/*   Updated: 2020/08/05 15:13:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** max decimal number to preserve precision
*/
# define F_DIG 6

# include <stdlib.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
int					putstr_fd(char *s, int fd);
size_t				ft_strlen(const char *s);
void				ft_bzero(void *s, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
double				ft_atof(char *str);
double				ft_atof_mv(char **str);
int					ft_atoi_mv(char **str);
void				ft_putendl_fd(char *s, int fd);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strdelchar(char *s, char c);
char				**ft_split(char const *s, char c);
char				**ft_split_blank(char const *s);
void				ft_putnbr_fd(int n, int fd);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, char *base);
char				*ft_ptoa(unsigned long ptr);
char				*ft_utoa(unsigned int n);
char				*ft_utoa_base(unsigned int n, char *base);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
void				*ft_lsttotab(t_list *lst, size_t type_size,
					int *array_size);
char				*ft_pass_spaces(char *s);
int					ft_isblank(int c);
int					ft_abs(int x);
double				ft_double_abs(double x);
int					ft_min(int a, int b);
int					ft_max(int a, int b);

#endif
