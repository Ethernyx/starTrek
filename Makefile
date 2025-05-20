
CXX				= clang++

NAME			= star_trek

NAME_DEBUG 		= star_trek_debug

NAME_TEST		= star_trek_test

RM				= rm -f

SRCS  			= $(shell find *.cpp )
SRCS  			+= $(shell find lib_func/*.cpp)
SRCS  			+= $(shell find object/*.cpp)

HEADS 			= $(shell find include/*.hh)
HEADS  			+= $(shell find lib_func/*.hh)
HEADS  			+= $(shell find include/object/*.hh)

SRCSTEST  		= $(shell find *.cpp )
SRCSTEST  		+= $(shell find lib_func/*.cpp)
SRCSTEST  		+= $(shell find object/*.cpp)
SRCSTEST		+= $(shell find test/*.cpp)

OBJS 			= $(SRCS:.cpp=.o)
OBJSTEST		= $(SRCSTEST:.cpp=.o)

CXXFLAGS		= -W -O2 -Werror -Wextra -pedantic -std=c++1z

LDFLAGS 		= -lm -lpthread -lboost_json -lssl -lcrypto



all:			$(NAME)

test:			$(NAME_TEST)

$(NAME_TEST):	$(OBJSTEST) $(HEADS)
				$(CXX) $(LDFLAGS) -o $@ $(OBJSTEST)

$(NAME): 		$(OBJS) $(HEADS)
				$(CXX) $(LDFLAGS) -o $@ $(OBJS)

debug:			CXXFLAGS = -g -W -O2 -Werror -Wall -Wextra -pedantic -std=c++1z -DDEBUG
debug:			$(NAME_DEBUG)

$(NAME_DEBUG):	$(OBJS) $(HEADS)
				$(CXX) $(DEBUG) $(LDFLAGS) -o $@ $(OBJS)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJSTEST)
				$(RM) *~

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(NAME_DEBUG)
				$(RM) $(NAME_TEST)

re:				fclean all
