ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LINK = libft_malloc.so

LIBFTDIR = libft/

INCSDIR = includes/

SRCSDIR = srcs/

OBJSDIR = objs/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS =  malloc.c \
		free.c \
		realloc.c \
		show_alloc_mem.c \
		tools.c \
		reallocf.c \
		calloc.c \
		tools2.c

OBJS = $(addprefix $(OBJSDIR),$(SRCS:.c=.o))

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -fPIC -I $(INCSDIR) -I $(LIBFTDIR)$(INCSDIR) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) -L./libft -lft
	ln -sf $(NAME) $(LINK)

clean:
	rm -rf $(OBJSDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME) $(LINK)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
