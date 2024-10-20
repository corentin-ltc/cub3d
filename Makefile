######################## SETTINGS ########################

NAME = fdf

CC = cc

FLAGS = -Wall -Wextra -Werror

LINKFLAGS = -lm -lmlx -lXext -lX11 -L minilibx

CPPFLAGS = -I minilibx

LIBS = libft \

INCLUDES =includes \
${foreach lib, ${LIBS}, ${lib} ${lib}/includes}

######################## SOURCES ########################

SRCS_NAMES =main.c \
exit.c \
parsing.c \
init.c \
handler.c \
handler_utils.c \
draw.c \
draw_utils.c \
transform_pos.c \
utils.c \
colors.c \
debug.c

SRCS_DIR = srcs/

SRCS = ${addprefix ${SRCS_DIR}, ${SRCS_NAMES}}

OBJS_DIR = objs/

OBJS = ${addprefix ${OBJS_DIR}, ${SRCS_NAMES:.c=.o}}

######################## BASIC RULES ########################

all : ${NAME}

re : fclean
${MAKE} all

clean :
${foreach lib, ${LIBS}, ${MAKE} clean -C ${lib}}
rm -rf ${OBJS_DIR}

fclean : clean
${foreach lib, ${LIBS}, ${MAKE} fclean -C ${lib}}
rm -f ${NAME}

norm :
${foreach lib, ${LIBS}, ${MAKE} norm -C ${lib}}
norminette -R CheckForbiddenSourceHeader ${SRCS}
norminette -R CheckDefine ${INCLUDES}

######################## COMPILATION ########################

${NAME} : ${OBJS_DIR} ${OBJS}
${foreach lib, ${LIBS}, ${MAKE} -C ${lib}}
${CC} ${FLAGS} ${OBJS} ${foreach lib, ${LIBS},${lib}/${lib}.a} -o $@ ${LINKFLAGS}

debug : ${OBJS_DIR} ${OBJS}
${foreach lib, ${LIBS}, ${MAKE} -C ${lib}}
${CC} ${FLAGS} -g3 -fsanitize=address ${OBJS} ${foreach lib, ${LIBS},${lib}/${lib}.a} -o ${NAME} ${LINKFLAGS}

${OBJS_DIR} :
mkdir $@

${OBJS_DIR}%.o : ${SRCS_DIR}%.c
${CC} ${FLAGS} ${CPPFLAGS} ${foreach include, ${INCLUDES},-I ${include}} -c $< -o $@

######################## TEST ########################

test : square

42 : all
./${NAME} 42.fdf

square : all
./${NAME} square.fdf

long : all
./${NAME} long.fdf

error : all
./${NAME} invalid.fdf

pylone : all
./${NAME} test_maps/pylone.fdf

pyramide : all
./${NAME} test_maps/pyramide.fdf