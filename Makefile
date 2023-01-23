NAME=minirt
CC=gcc
CFLAGS=-Wall -Werror -Wextra  -I$(PWD)/MLX42/include
# LFLAGS=-ldl -L/Users/$(USER)/.brew/Cellar/glfw/3.3.8/lib -lglfw -pthread -lm 
LFLAGS=-ldl -L$(HOME)/goinfre/.brew/Cellar/glfw/3.3.8/lib -lglfw -pthread -lm 


# rm -rf $HOME/.brew && rm -rf $HOME/goinfre/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew && echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
# brew install glfw


MLX=libmlx42.a

inputsources=input_check_element.c input_check_element2.c input_utils.c input.c ft_atod.c in_range.c get_field.c get_scene.c get_objects.c scene_settings.c alloc_mem.c \

utilitysources=long_atoi.c ft_isalpha.c ft_split.c ft_strlen.c ft_strcmp.c ft_substr.c ft_calloc.c ft_bzero.c get_next_line_utils.c get_next_line.c \
	ft_isdigit.c ft_strncmp.c free_1.c ft_free_split_void.c ft_memset.c ft_objnew.c ft_objsfree.c ft_objadd_back.c ft_objat.c ft_lstsize.c d_nearly_equal.c\

vectorsources=vecoperations1.c vecoperations2.c vecoperations3.c print_utils.c\

rendersources=main.c obj_intersection.c hook.c light_ray.c cylinder_intersection.c color_calcs.c move_by_vec_ratio.c hittable_utils.c obj_intersection2.c\

objectsources=object_matrix.c get_obj_position.c get_surface_normal.c\

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

debug:
	cd ./MLX42 && make
	mv ./MLX42/$(MLX) .
	$(CC) $(CFLAGS) -g $(inputsourcespath) $(utilitsourcesspath) $(vectorsourcespath) $(rendersourcespath) $(objectsourcespath) $(MLX) -o $(NAME) $(LFLAGS)


fclean: clean
	rm -rf $(MLX)
	rm -rf $(NAME)

re: fclean all