/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:22:59 by bgoron            #+#    #+#             */
/*   Updated: 2024/04/05 15:54:46 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef long long	t_elodie;

/* ************************************************************************** */
/*                                 Allocation                                 */
/* ************************************************************************** */

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_free_tab(void **tab);

/* ************************************************************************** */
/*                                     Is                                     */
/* ************************************************************************** */

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_is_white_space(char c);

/* ************************************************************************** */
/*                                     List                                   */
/* ************************************************************************** */

void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

/* ************************************************************************** */
/*                                    Math                                    */
/* ************************************************************************** */

size_t		ft_nbrlen(int n);
int			ft_longlonglen(long long nb);

/* ************************************************************************** */
/*                                   Memory                                   */
/* ************************************************************************** */

void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

/* ************************************************************************** */
/*                                     Put                                    */
/* ************************************************************************** */

void		ft_printf_fd(int fd, char *format, ...);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* ************************************************************************** */
/*                                     Str                                    */
/* ************************************************************************** */

char		*ft_ctabjoin(char **tab, char *sep, int f);
char		*ft_expand_str(char *str, char *to_add, int index);
void		ft_extand_tab(char ***tab, char *add);
char		*ft_replace_by(char **str, char *supp, char *add, int f);
char		*ft_replace_str(char *old, char *new);
char		*ft_shrink_str(char *str, int index, int len);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
size_t		ft_strcspn(char *s, char *reject);
char		*ft_strdup(char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char *s1, char *s2, int i);
char		*ft_strjoin_char(char *s1, char c);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strndup(char *s1, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strcpy(char *dst, char *src);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);

/* ************************************************************************** */
/*                                     To                                     */
/* ************************************************************************** */

char		*ft_itoa(int n);
int			ft_atoi(const char *nptr);
t_elodie	ft_atoelodie(char *str);

#endif
