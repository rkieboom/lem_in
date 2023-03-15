# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkieboom <rkieboom@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/25 11:00:12 by rkieboom       #+#    #+#                 #
#    Updated: 2019/11/29 16:06:44 by rkieboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

CFLAGS = -Iinc #-Wall -Werror -Wextra

SRCDIR	= src/
OBJDIR	= bin/
HDRDIR	= inc/

LIBFTDIR = libft/
LIBFT = libft/libft.a

#Add rule for debugging
ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(DEBUG), 2)
	CFLAGS += -g3 -fsanitize=address
endif

INCLUDES = $(addprefix $(HDRDIR), \
	header.h parse.h \
)

SRCS = $(addprefix $(SRCDIR), \
	main.c parser.c parser_data.c rooms.c\
)

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.c=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES) $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJDIR)%.o : $(SRCDIR)%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C libft/

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft/

re: fclean all

.PHONY	= all run clean fclean re