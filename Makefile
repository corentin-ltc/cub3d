######################## SETTINGS ########################
NAME = cub3d

CC = clang -g3

FLAGS = -Wall -Wextra -Werror

LINKFLAGS = -lm -lmlx -lXext -lX11 -L minilibx-linux

CPPFLAGS = -I minilibx

INCLUDES =	includes \
			libft/includes \
			libft

VALGRIND = valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all

######################## SOURCES ########################

INIT =	init.c \
		checker.c \
		parser.c \
		hooks.c

RAYCASTING =	minimap.c \
				draw.c

UTILS =	utils.c \
		exit.c

SRCS_NAMES =	 main.c \
				${addprefix init/, ${INIT}} \
				${addprefix raycasting/, ${RAYCASTING}} \
				${addprefix utils/, ${UTILS}}

SRCS_DIR = srcs/

SRCS = ${addprefix ${SRCS_DIR}, ${SRCS_NAMES}}

OBJS_DIR = objs/

OBJS = ${addprefix ${OBJS_DIR}, ${SRCS_NAMES:.c=.o}}

HEADERS =	includes/cub3d.h

######################## BASIC RULES ########################

.PHONY: all re clean fclean norm test leak

all : clear ${NAME}

re : fclean
	${MAKE} all

clean :
	${MAKE} clean -C libft
	${MAKE} clean -C minilibx-linux
	rm -rf ${OBJS_DIR}

fclean : clean
	${MAKE} fclean -C libft
	rm -f ${NAME}

norm :
	${MAKE} clean -C libft
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCLUDES}

clear :
	clear

######################## COMPILATION ########################

${NAME} : SUB_MODULE ${OBJS_DIR} ${OBJS}
	${MAKE} -C libft
	${MAKE} -C minilibx-linux
	${CC} ${FLAGS} ${OBJS} libft/libft.a -o $@ ${LINKFLAGS}

debug : ${OBJS_DIR} ${OBJS}
	${MAKE} -C libft
	${MAKE} -C minilibx-linux
	${CC} ${FLAGS} -g3 -fsanitize=address ${OBJS} libft/libft.a -o ${NAME} ${LINKFLAGS}

${OBJS_DIR} :
	mkdir $@
	mkdir $@init
	mkdir $@raycasting
	mkdir $@utils

${OBJS_DIR}%.o : ${SRCS_DIR}%.c ${HEADERS}
	${CC} ${FLAGS} ${CPPFLAGS} ${foreach include, ${INCLUDES},-I ${include}} -c $< -o $@

SUB_MODULE :
	git submodule update --init

######################## TEST ########################

test : all
	./${NAME} maps/map.cub

empty : all
	./${NAME} maps/empty.cub

invalid : all
	./${NAME} maps/invalid.cub

rights : all
	./${NAME} maps/no_rights.cub

leak : all
	${VALGRIND} ./${NAME} maps/map.cub

x:
	./${NAME} maps/map.cub