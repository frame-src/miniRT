NAME=minirt
CC=gcc
# CFLAGS=-Wall -Werror -Wextra -I/Users/frame/Desktop/miniRT_with_Marius/MLX42/include 
CFLAGS=-Wall -Werror -Wextra  -I/Users/mawinter/Desktop/projects/miniRT/MLX42/include
# LFLAGS=-ldl -L/Users/frame/.brew/Cellar/glfw/3.3.8/lib -lglfw -pthread -lm  
LFLAGS=-ldl -L/Users/mawinter/.brew/Cellar/glfw/3.3.8/lib -lglfw -pthread -lm 

MLX=libmlx42.a

inputsources=input_check_element.c input_check_element2.c input_utils.c input.c ft_atod.c in_range.c get_field.c get_scene.c \

utilitysources=long_atoi.c ft_isalpha.c ft_split.c ft_strlen.c ft_strcmp.c ft_substr.c ft_calloc.c ft_bzero.c get_next_line_utils.c get_next_line.c \
	ft_isdigit.c ft_strncmp.c free_1.c ft_free_split_void.c ft_memset.c ft_objnew.c ft_objsfree.c ft_objadd_back.c ft_objat.c ft_lstsize.c\

vectorsources=vecoperations1.c vecoperations2.c vecoperations3.c print_utils.c\

rendersources=main.c obj_intersection.c\

objectsources=object_matrix.c print_objects.c\

inputsourcespath=$(addprefix ./input/, $(inputsources))
utilitsourcesspath=$(addprefix ./utility/, $(utilitysources))
vectorsourcespath=$(addprefix ./vector/, $(vectorsources))
rendersourcespath=$(addprefix ./render/, $(rendersources))
objectsourcespath=$(addprefix ./objects/, $(objectsources))

inputobjs=$(inputsources:.c=.o)
utilityobjs=$(utilitysources:.c=.o)
renderobjs=$(rendersources:.c=.o)
vectorobjs=$(vectorsources:.c=.o)
objectobjs=$(objectsources:.c=.o)

inputobjspath=$(inputsourcespath:.c=.o)
utilityobjspath=$(utilitsourcesspath:.c=.o)
vectorobjspath=$(vectorsourcespath:.c=.o)
renderobjspath=$(rendersourcespath:.c=.o)
objectobjspath=$(objectsourcespath:.c=.o)

all: $(NAME)

$(NAME): $(inputobjspath) $(utilityobjspath) $(vectorobjspath) $(renderobjspath) $(objectobjspath)
	cd ./MLX42 && make
	mv ./MLX42/$(MLX) .
	$(CC) $(CFLAGS) $(inputobjspath) $(utilityobjspath) $(vectorobjspath) $(renderobjspath) $(objectobjspath) $(MLX) -o $(NAME) $(LFLAGS)

clean:
	cd ./MLX42 && make clean
	rm -rf $(inputobjspath) $(utilityobjspath) $(vectorobjspath) $(renderobjspath) $(objectobjspath)

fclean: clean
	rm -rf $(MLX)
	rm -rf $(NAME)

re: fclean all