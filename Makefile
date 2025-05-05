NAME	= json

INCDIR	= includes/
SRCDIR	= src/
SRC		= $(SRCDIR)json_valid.cpp $(SRCDIR)json.cpp $(SRCDIR)json_srl.cpp
MSRC	= main.cpp


OBJ 	= $(SRC:$(SRCDIR)%.cpp=$(SRCDIR)%.o)
MOBJ	= $(MSRC:%.cpp=%.o)

IFLAG 	= -I$(INCDIR)
STD		= -std=c++17
GPP		= g++ $(STD) $(IFLAG)
RM		= rm -rf

all:			$(NAME)

%.o:			$(SRCDIR)%.cpp
				$(GPP) -c $< -o $@

%.o: 			%.cpp
				$(GPP) -c $< -o $@

$(NAME):		$(OBJ) $(MOBJ)
				$(GPP) $(OBJ) $(MOBJ) -o $(NAME)

clean:
		$(RM) $(OBJ) $(MOBJ)

fclean: clean
		$(RM) $(NAME)

.PHONY: all clean fclean