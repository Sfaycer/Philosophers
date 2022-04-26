CC = gcc
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address
NAME = philo
LIBFT_DIR = libft
INCLUDES = -I$(HEADERS_DIR)
HEADERS_LIST = libft.h
HEADERS_DIR = .
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))
SRCS = main.c ft_atoi_and_error.c parse_arguments.c time.c messages.c simulation.c philo_eat.c
TEST_SRCS = test.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

DEP_DIR := $(OBJ_DIR)/.deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
COMPILE.c = $(CC) $(DEPFLAGS) #$(CFLAGS)
POSTCOMPILE = mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d && touch $@

LDFLAGS = 
#-L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include
LDLIBS =  -lpthread #link libft library

 #search for library in ./ path

DEF = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
LYELLOW = \033[0;33m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m

all:
		@$(MAKE) $(NAME)

$(NAME): $(OBJS)
		@echo "$(YELLOW)'$(NAME)' Object files were born!$(DEF)"
		@$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
		@echo "$(GREEN)Program '$@' is ready to be used.$(DEF)"

debug: $(NAME)
		@$(CC) $(LDFLAGS) $(LDLIBS) -o $(NAME) -gdwarf $(SRCS)
		@echo "$(WHITE)Debugging initiated.$(DEF)"

sanitize: $(NAME)
		@$(CC) $(LDFLAGS) $(LDLIBS) -o $(NAME) $(SANITIZE) $(SRCS)
		@echo "$(WHITE)Sanitizer initiated.$(DEF)"

test:	$(TEST_SRCS)
		@$(CC) $(LDFLAGS) $(LDLIBS) -gdwarf $(TEST_SRCS) -o test
		@echo "$(CYAN)Test program is ready.$(DEF)"

$(OBJ_DIR):
		@mkdir -p $@
		@echo "$(CYAN)Folder '$@' was created.$(DEF)"

$(OBJ_DIR)/%.o: %.c $(DEP_DIR)/%.d | $(DEP_DIR)
		@$(COMPILE.c) -c $< -o $@
		@$(POSTCOMPILE)
		@echo "$(RED).$(DEF)\c"

$(DEP_DIR):
		@mkdir -p $@
		@echo "$(CYAN)Folder "$@" was created.$(DEF)"

DEPFILES = $(SRCS:%.c=$(DEP_DIR)/%.d)
$(DEPFILES):

cleandep:
		@rm -rf $(DEP_DIR)

clean:
		@rm -rf $(OBJ_DIR)
		@echo "$(RED)Folder '$(OBJ_DIR)' and all files inside were deleted.$(DEF)"

cleandebug:
		@rm -rf $(NAME).dSYM
		@echo "$(MAGENTA)Debug files were deleted.$(DEF)"

fclean: clean
		@rm -f $(NAME)
		@echo "$(MAGENTA)Program '$(NAME)' was deleted.$(DEF)"

re: fclean all

include $(wildcard $(DEPFILES))

.PHONY: all clean fclean re bonus cleandep debug
