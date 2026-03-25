# =========================================================
# Name des finalen Binaries
# =========================================================
NAME		= minishell

# =========================================================
# Compiler und Flags
# =========================================================
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP -g -O0

# =========================================================
# Ordner
# =========================================================
SRC_DIR		= src
OBJ_DIR		= build
INC_DIR		= include
LIBFT_DIR	= $(SRC_DIR)/libft

# =========================================================
# OS-Erkennung
# =========================================================
UNAME_S := $(shell uname -s)

# =========================================================
# Readline-Erkennung
# 1) zuerst pkg-config
# 2) dann Fallback für macOS über Homebrew
# 3) Linux-Fallback mit ncurses
# =========================================================

READLINE_CFLAGS := $(shell pkg-config --cflags readline 2>/dev/null)
READLINE_LIBS   := $(shell pkg-config --libs readline 2>/dev/null)

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS  =
LDLIBS   =

INCLUDES += $(READLINE_CFLAGS)
LDLIBS   += $(READLINE_LIBS)

ifeq ($(strip $(READLINE_CFLAGS) $(READLINE_LIBS)),)
	ifeq ($(UNAME_S),Darwin)
		READLINE_DIR := $(shell brew --prefix readline 2>/dev/null)
		ifneq ($(READLINE_DIR),)
			INCLUDES += -I$(READLINE_DIR)/include
			LDFLAGS  += -L$(READLINE_DIR)/lib
			LDLIBS   += -lreadline
		else
			LDLIBS   += -lreadline
		endif
	endif
	ifeq ($(UNAME_S),Linux)
		LDLIBS += -lreadline -lncurses
	endif
endif

# =========================================================
# Projekt-Sources
# =========================================================
SRCS		= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/error_handling/brackets_quotes_syntax.c \
	$(SRC_DIR)/error_handling/core_syntax.c \
	$(SRC_DIR)/error_handling/op_syntax.c \
	$(SRC_DIR)/error_handling/print_syntax_error.c \
	$(SRC_DIR)/error_handling/redir_syntax.c \
	$(SRC_DIR)/env/env_utils.c \
	$(SRC_DIR)/env/env_utils2.c \
	$(SRC_DIR)/env/init_env.c \
	$(SRC_DIR)/env/set_env.c \
	$(SRC_DIR)/env/unset_env.c \
	$(SRC_DIR)/exec/collect_heredocs.c \
	$(SRC_DIR)/exec/exec_cmd.c \
	$(SRC_DIR)/exec/exec_cmd_unit.c \
	$(SRC_DIR)/exec/exec.c \
	$(SRC_DIR)/exec/exec_heredoc.c \
	$(SRC_DIR)/exec/exec_redir.c \
	$(SRC_DIR)/exec/exec_helpers.c \
	$(SRC_DIR)/exec/exec_helpers2.c \
	$(SRC_DIR)/exec/exec_pipe.c \
	$(SRC_DIR)/exec/builtins/builtin_cd.c \
	$(SRC_DIR)/exec/builtins/builtin_echo.c \
	$(SRC_DIR)/exec/builtins/builtin_env.c \
	$(SRC_DIR)/exec/builtins/builtin_exit.c \
	$(SRC_DIR)/exec/builtins/builtin_export.c \
	$(SRC_DIR)/exec/builtins/builtin_export_print.c \
	$(SRC_DIR)/exec/builtins/builtin_shell_vars.c \
	$(SRC_DIR)/exec/builtins/builtin_pwd.c \
	$(SRC_DIR)/exec/builtins/builtin_unset.c \
	$(SRC_DIR)/exec/builtins/identify_exp_mode.c \
	$(SRC_DIR)/exec/builtins/builtins.c \
	$(SRC_DIR)/gc/gc_alloc.c \
	$(SRC_DIR)/gc/gc_free.c \
	$(SRC_DIR)/gc/gc_split.c \
	$(SRC_DIR)/gc/gc_strtrim.c \
	$(SRC_DIR)/gc/gc_utils.c \
	$(SRC_DIR)/parser/parse.c \
	$(SRC_DIR)/parser/parse_helpers.c \
	$(SRC_DIR)/parser/expansions/expand_argv.c \
	$(SRC_DIR)/parser/expansions/expansions_helper.c \
	$(SRC_DIR)/parser/expansions/quote_removal.c \
	$(SRC_DIR)/parser/expansions/variable_expansion.c \
	$(SRC_DIR)/parser/expansions/wildcards_expansion.c \
	$(SRC_DIR)/parser/expansions/wildcards_helper.c \
	$(SRC_DIR)/parser/expansions/wildcards_match_list.c \
	$(SRC_DIR)/parser/expansions/wildcards_new_argv.c \
	$(SRC_DIR)/parser/redirections/redirs.c \
	$(SRC_DIR)/parser/redirections/redirs_helpers.c \
	$(SRC_DIR)/parser/redirections/redirs_helpers2.c \
	$(SRC_DIR)/parser/handle_missing_token.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/utils/wrapper.c \
	$(SRC_DIR)/utils/skip_quotes_and_split.c \
	$(SRC_DIR)/utils/exit_and_status.c \
	$(SRC_DIR)/utils/signals.c

# =========================================================
# Libft-Sources
# =========================================================
LIBFT_SRCS	= \
	$(LIBFT_DIR)/ft_atoi.c \
	$(LIBFT_DIR)/ft_bzero.c \
	$(LIBFT_DIR)/ft_calloc.c \
	$(LIBFT_DIR)/ft_isalnum.c \
	$(LIBFT_DIR)/ft_isalpha.c \
	$(LIBFT_DIR)/ft_isascii.c \
	$(LIBFT_DIR)/ft_isdigit.c \
	$(LIBFT_DIR)/ft_isprint.c \
	$(LIBFT_DIR)/ft_itoa.c \
	$(LIBFT_DIR)/ft_memchr.c \
	$(LIBFT_DIR)/ft_memcmp.c \
	$(LIBFT_DIR)/ft_memcpy.c \
	$(LIBFT_DIR)/ft_memmove.c \
	$(LIBFT_DIR)/ft_memset.c \
	$(LIBFT_DIR)/ft_putchar_fd.c \
	$(LIBFT_DIR)/ft_putendl_fd.c \
	$(LIBFT_DIR)/ft_putnbr_fd.c \
	$(LIBFT_DIR)/ft_putstr_fd.c \
	$(LIBFT_DIR)/ft_split.c \
	$(LIBFT_DIR)/ft_strchr.c \
	$(LIBFT_DIR)/ft_strcmp.c \
	$(LIBFT_DIR)/ft_strdup.c \
	$(LIBFT_DIR)/ft_striteri.c \
	$(LIBFT_DIR)/ft_strjoin.c \
	$(LIBFT_DIR)/ft_strlcat.c \
	$(LIBFT_DIR)/ft_strlcpy.c \
	$(LIBFT_DIR)/ft_strlen.c \
	$(LIBFT_DIR)/ft_strmapi.c \
	$(LIBFT_DIR)/ft_strncmp.c \
	$(LIBFT_DIR)/ft_strnstr.c \
	$(LIBFT_DIR)/ft_strrchr.c \
	$(LIBFT_DIR)/ft_strtrim.c \
	$(LIBFT_DIR)/ft_substr.c \
	$(LIBFT_DIR)/ft_tolower.c \
	$(LIBFT_DIR)/ft_toupper.c

# =========================================================
# Objekte
# =========================================================
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT_OBJS	= $(LIBFT_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ALL_OBJS	= $(OBJS) $(LIBFT_OBJS)
DEPS		= $(ALL_OBJS:.o=.d)

# =========================================================
# Default-Target
# =========================================================
all: $(NAME)

# =========================================================
# Kompilieren
# =========================================================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =========================================================
# Linken
# =========================================================
$(NAME): $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# =========================================================
# Aufräumen
# =========================================================
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re