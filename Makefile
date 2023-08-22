NAME			= philo
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

SRC				= $(addprefix $(SRC_DIR),$(addsuffix .c, $(SRC_FILES)))
SRC_DIR			=
SRC_FILES		= habits philo philosophers time utils

OBJ_DIR			=	obj/
ALL_OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
ALL_OBJ_DIR		=	$(sort $(dir $(ALL_OBJ)))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(ALL_OBJ_DIR) $(ALL_OBJ)
	$(CC) $(ALL_OBJ) -o $(NAME)

$(ALL_OBJ_DIR):
	@mkdir -p $(ALL_OBJ_DIR)

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)

fclean:	clean
	@${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
