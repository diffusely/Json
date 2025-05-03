NAME = json

SRC = main.cpp json.cpp json_valid.cpp

OBJ = $(SRC:%.cpp=%.o)

STD = -std=c++17
GPP = g++ $(STD)
RM	= rm -rf

all		:	$(NAME)

%.o		:	%.cpp
			$(GPP) -c $< -o $@


$(NAME)	:	$(OBJ)
			$(GPP) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

.PHONY: all clean fclean