NAME = pipex
GCC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCSDIR = src
OBJSDIR = obj
SRCSFILES = pipex.c
OBJSFILES = $(SRCSFILES:.c=.o)
SRCS = $(addprefix $(SRCSDIR)/, $(SRCSFILES))
OBJS = $(addprefix $(OBJSDIR)/, $(OBJSFILES))
HEAD = -I inc

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./inc/libft
	$(GCC) $(CFLAGS) $(OBJS) -o $(NAME) ./inc/libft/libft.a

$(OBJS): $(SRCS)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c | obj
	$(GCC) $(CFLAGS) -c $< -o $@ $(HEAD)

debug:
	gcc src/*.c -I inc inc/libft/libft.a -g -o debug

obj:
	mkdir -p $(OBJSDIR)

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re debug

