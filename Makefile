######################## SETTINGS ########################
NAME = cub3d

CC = cc

FLAGS = -Wall -Wextra -Werror

LINKFLAGS = -lm -lmlx -lXext -lX11 -L minilibx-linux

CPPFLAGS = -I minilibx

INCLUDES =	includes \
			libft \
			libft/includes

VALGRIND = valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all

######################## SOURCES ########################

PARSING =	parsing.c

RAYCASTING =	

UTILS =	

SRCS_NAMES =	 main.c \
				${addprefix parsing/, ${PARSING}} \
				${addprefix raycasting/, ${BUILTIN}} \
				${addprefix utils/, ${UTILS}}

SRCS_DIR = srcs/

SRCS = ${addprefix ${SRCS_DIR}, ${SRCS_NAMES}}

OBJS_DIR = objs/

OBJS = ${addprefix ${OBJS_DIR}, ${SRCS_NAMES:.c=.o}}

HEADERS =	includes/cub3d.h

######################## BASIC RULES ########################

.PHONY: all re clean fclean norm test leak

all : ${NAME}

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
	mkdir $@parsing
	mkdir $@raycasting
	mkdir $@utils

${OBJS_DIR}%.o : ${SRCS_DIR}%.c ${HEADERS}
	${CC} ${FLAGS} ${CPPFLAGS} ${foreach include, ${INCLUDES},-I ${include}} -c $< -o $@

SUB_MODULE :
	git submodule update --init

######################## TEST ########################

test : all
	clear
	./${NAME}

leak : all
	${valgrind} ./${NAME}