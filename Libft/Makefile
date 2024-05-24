# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 10:39:42 by bgoron            #+#    #+#              #
#    Updated: 2024/04/02 07:16:39 by bgoron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

IFLAGS = -I ./include

SRCS = alloc/ft_bzero.c       \
alloc/ft_calloc.c             \
alloc/ft_free_tab.c           \
is/ft_isalnum.c               \
is/ft_isalpha.c               \
is/ft_isascii.c               \
is/ft_isdigit.c               \
is/ft_isprint.c               \
is/ft_is_white_space.c        \
lst/ft_lstadd_back.c          \
lst/ft_lstadd_front.c         \
lst/ft_lstclear.c             \
lst/ft_lstdelone.c            \
lst/ft_lstiter.c              \
lst/ft_lstlast.c              \
lst/ft_lstmap.c               \
lst/ft_lstnew.c               \
lst/ft_lstsize.c              \
math/ft_nbrlen.c              \
math/ft_longlonglen.c         \
mem/ft_memchr.c               \
mem/ft_memcmp.c               \
mem/ft_memcpy.c               \
mem/ft_memmove.c              \
mem/ft_memset.c               \
put/ft_printf_fd.c            \
put/ft_putchar_fd.c           \
put/ft_putendl_fd.c           \
put/ft_putnbr_fd.c            \
put/ft_putstr_fd.c            \
str/ft_ctabjoin.c             \
str/ft_expand_str.c           \
str/ft_extand_tab.c           \
str/ft_replace_by.c           \
str/ft_replace_str.c          \
str/ft_shrink_str.c           \
str/ft_split.c                \
str/ft_strchr.c               \
str/ft_strcspn.c              \
str/ft_strdup.c               \
str/ft_striteri.c             \
str/ft_strjoin.c              \
str/ft_strjoin_char.c         \
str/ft_strlcat.c              \
str/ft_strlcpy.c              \
str/ft_strlen.c               \
str/ft_strmapi.c              \
str/ft_strncmp.c              \
str/ft_strndup.c              \
str/ft_strnstr.c              \
str/ft_strrchr.c              \
str/ft_strcpy.c               \
str/ft_strtrim.c              \
str/ft_substr.c               \
str/ft_tolower.c              \
str/ft_toupper.c              \
to/ft_atoi.c                  \
to/ft_atoll.c                 \
to/ft_itoa.c                  \

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)

.c.o :
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -I.

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

all: $(NAME)

.PHONY: all clean fclean re
