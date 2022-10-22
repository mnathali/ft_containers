# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 23:01:24 by mnathali          #+#    #+#              #
#    Updated: 2022/10/16 03:25:00 by mnathali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	subject_test
NAME_V	=	vector_test
NAME_M	=	map_test
NAME_S	=	set_test
NAME_U	=	utils_test

CC		=	c++
STD		=	-std=c++98
FLAGS	=	-Wall -Wextra -Werror

SRC		=	main.cpp
SRC_V	=	main_vector.cpp
SRC_M	=	main_map.cpp
SRC_S	=	main_set.cpp
SRC_U	=	main_utils.cpp
		
TEMPLATES =	templates/Vector.hpp			\
			templates/Set.hpp 				\
			templates/Map.hpp				\
			templates/Stack.hpp				\
			templates/Algorithm.hpp			\
			templates/Iterator_traits.hpp	\
			templates/Iterator.hpp			\
			templates/Type_traits.hpp		\
			templates/Utility.hpp

OBJ = $(patsubst %.cpp, %.o, $(SRC))


all : $(NAME)
	
vector :
	@make NAME="$(NAME_V)" SRC="$(SRC_V)" all

map :
	@make NAME="$(NAME_M)" SRC="$(SRC_M)" all

set :
	@make NAME="$(NAME_S)" SRC="$(SRC_S)" all

utils :
	@make NAME="$(NAME_U)" SRC="$(SRC_U)" all

$(OBJ) : $(TEMPLATES)

%.o : %.cpp
	$(CC) $(FLAGS) $(STD) -c $<

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(STD) $(OBJ) -o $@

clean: 
	rm -f $(patsubst %.cpp, %.o, $(SRC)) $(patsubst %.cpp, %.o, $(SRC_V)) $(patsubst %.cpp, %.o, $(SRC_S)) $(patsubst %.cpp, %.o, $(SRC_M)) $(patsubst %.cpp, %.o, $(SRC_U))

fclean: clean
	rm -f $(NAME) $(NAME_V) $(NAME_M) $(NAME_S) $(NAME_U)

re: fclean all

.PHONY : all re clean fclean