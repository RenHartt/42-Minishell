# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:46:56 by bgoron            #+#    #+#              #
#    Updated: 2024/04/05 16:09:28 by bgoron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I./include -I./Libft/include

SRCS = src/builtins/ft_cd.c                  \
src/builtins/ft_echo.c                       \
src/builtins/ft_env.c                        \
src/builtins/ft_exit.c                       \
src/builtins/ft_export_utils.c               \
src/builtins/ft_export.c                     \
src/builtins/ft_pwd.c                        \
src/builtins/ft_unset.c                      \
src/execution/command/command_utils.c        \
src/execution/command/execute_builtin.c      \
src/execution/command/execute_command.c      \
src/execution/command/execute_utils.c        \
src/execution/command/init_command.c         \
src/execution/command/set_command.c          \
src/execution/command/permission.c           \
src/execution/heredoc/heredoc.c              \
src/execution/heredoc/heredoc_utils.c        \
src/execution/redirection/init_redirection.c \
src/execution/redirection/set_redirection.c  \
src/global/exit_code.c                       \
src/main/main.c                              \
src/parsing/exit/exit_minishell.c            \
src/parsing/exit/ft_free.c                   \
src/parsing/init_env/init_env.c              \
src/parsing/init_token/check_line.c          \
src/parsing/init_token/check_token.c         \
src/parsing/init_token/init_token.c          \
src/parsing/init_token/parse_line.c          \
src/parsing/init_token/set_var.c             \
src/signal/signal.c                          \
src/signal/ignore_signal.c                   \

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@make -s -C Libft
	@$(CC) $(CLAGS) $(IFLAGS) $(OBJS) -lreadline -o $(NAME) Libft/libft.a

.c.o :
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS)

fclean : clean
	@make -s -C Libft fclean
	@rm -rf $(NAME)

re : fclean all

all: $(NAME)

.PHONY: all clean fclean re
