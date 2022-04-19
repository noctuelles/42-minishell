# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/08 10:05:58 by dhubleur          #+#    #+#              #
#    Updated: 2022/04/19 16:53:07 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#								  Utils										   #
################################################################################

NAME		= 	minishell
CC			= 	clang
CFLAGS		=	
LFLAGS		=	-lreadline

RUN_PARAM	=	

VOGSPHERE	=	

################################################################################
#								  Sources									   #
################################################################################

SRCS_EXTENSION	=	.c
SRCS_PATH		=	./srcs
SRCS			=	main.c \
					prompt.c \
					ft_strtrunc.c \
					signals.c \
					signals_utils.c \
					$(addprefix builtins/, \
						ft_cd.c \
						ft_echo.c \
						ft_env.c \
						ft_export.c \
						ft_pwd.c \
						ft_unset.c \
						ft_exit.c) \
					$(addprefix env/, \
						env.c) \
					$(addprefix execution/, \
						path.c \
						builtin.c \
						command_preparator.c \
						executor.c \
						end.c \
						interpret_tree.c) \
					$(addprefix lexer/, \
						lexer_mem_utils.c \
						lexer_utils.c \
						lexer.c) \
					$(addprefix parser/, \
						args.c \
						ast.c \
						parser.c \
						parser_utils.c \
						stack.c \
						pipeline.c \
						pushnstack.c \
						pushnstack_utils.c \
						node_expansion.c \
						simple_command.c) \
					$(addprefix utils/, \
						io_utils.c \
						linked_list_utils.c) \
					$(addprefix var/, \
						var_expansion_post_utils.c \
						var_expansion_utils.c \
						var_expansion.c \
						var_utils.c \
						var.c \
						var_expansion_post.c) \
					$(addprefix wildcard/, \
						wildcard_expansion_utils.c \
						wildcard_expansion.c)
					

################################################################################
#								  Includes									   #
################################################################################

INCLUDE_DIRS		=	./includes

################################################################################
#								  Libft										   #
################################################################################

IS_LIBFT			=	true

LIBFT_DIR			=	./libft
LIBFT_INCLUDE_DIR	=	./libft/includes
LIBFT_NAME			=	libft.a

################################################################################
#								  MiniLibX									   #
################################################################################

IS_MLX				=	false

MLX_DIR				=	./minilibx-linux
MLX_INCLUDE_DIR		=	./minilibx-linux
MLX_NAME			=	minilibx.a

#               /!\ Do not touch the rest of the file /!\ 

################################################################################
#								  Objects									   #
################################################################################

OBJS_PATH		=	./objs

OBJS			=	$(addprefix $(OBJS_PATH)/, ${SRCS:$(SRCS_EXTENSION)=.o})
OBJS_DEPEND		=	$(addprefix $(OBJS_PATH)/, ${SRCS:$(SRCS_EXTENSION)=.d})

################################################################################
#								  Constants									   #
################################################################################

BLUE		=	\033[1;34m
CYAN		=	\033[0;36m
GREEN		=	\033[0;32m
ORANGE  	=	\033[0;33m
NO_COLOR	=	\033[m

################################################################################
#								  Makefile									   #
################################################################################

INCLUDE_FLAGS 	=	$(addprefix -I , ${INCLUDE_DIRS})

LIBFT_COMPLETE	=	$(LIBFT_DIR)/${LIBFT_NAME}
MLX_COMPLETE	=	$(LIBFT_DIR)/${LIBFT_NAME}

ifeq ($(IS_LIBFT),true)
	INCLUDE_FLAGS	+=	$(addprefix -I , ${LIBFT_INCLUDE_DIR})
	ALL_LIBS		+=	$(LIBFT_COMPLETE)
endif

ifeq ($(IS_MLX),true)
	INCLUDE_FLAGS	+=	$(addprefix -I , ${MLX_INCLUDE_DIR})
	ALL_LIBS		+=	$(MLX_COMPLETE)
endif

ifeq (noflag, $(filter noflag,$(MAKECMDGOALS)))
	CFLAGS	+=	-Wall -Wextra
else
	CFLAGS	+=	-Wall -Wextra -Werror -g3
endif
ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS	+=	-g3
endif
ifeq (sanadd, $(filter sanadd,$(MAKECMDGOALS)))
	CFLAGS	+=	-fsanitize=address
endif
ifeq (santhread, $(filter santhread,$(MAKECMDGOALS)))
	CFLAGS	+=	-fsanitize=thread
endif

define count_files
	TOTAL_FILES=`bash -c 'make -n | grep -- "-c.*-o" | wc -l'`; \
	TOTAL_FILES=$$((TOTAL_FILES-1)); \
	if [ $$TOTAL_FILES -ne 0 ]; then \
		echo -n $$TOTAL_FILES > .MAKEFILE_total_files; \
		echo -n "0" > .MAKEFILE_compiled_files; \
		tput civis; \
	fi;
endef

define file_compiled
	COMPILED=`bash -c 'cat .MAKEFILE_compiled_files'`; \
	COMPILED=$$((COMPILED+1)); \
	echo -n $$COMPILED > .MAKEFILE_compiled_files; \
	sleep 0.1;
endef

define draw_bar
	TOTAL_FILES=`bash -c 'cat .MAKEFILE_total_files'`; \
	COMPILED=`bash -c 'cat .MAKEFILE_compiled_files'`; \
	TOTAL_LENGTH=52; \
	if [ $$COMPILED -eq 0 ]; then \
		COMPLETED_LENGTH=0; \
	else \
		INCREMENT=$$((TOTAL_LENGTH/TOTAL_FILES)); \
		COMPLETED_LENGTH=$$((INCREMENT*COMPILED)); \
	fi; \
	PRINT=0; \
	printf "\r"; \
	while [ $$PRINT -ne $$COMPLETED_LENGTH ]; do \
		printf "\e[0;32m█\e[0m"; \
		PRINT=$$((PRINT+1)); \
	done; \
	if [ $$COMPILED -eq $$TOTAL_FILES ]; then \
		while [ $$PRINT -ne $$TOTAL_LENGTH ]; do \
			printf "\e[0;32m█\e[0m"; \
			PRINT=$$((PRINT+1)); \
		done; \
	fi; \
	while [ $$PRINT -ne $$TOTAL_LENGTH ]; do \
		printf "\e[0m▒\e[0m"; \
		PRINT=$$((PRINT+1)); \
	done; \
	if [ $$COMPILED -eq $$TOTAL_FILES ]; then \
		printf "\n"; \
		tput cvvis; \
	fi;
endef

define clean
	rm -f .MAKEFILE_total_files; \
	rm -f .MAKEFILE_compiled_files; \
	tput cvvis;
endef

################################################################################
#								  Rules										   #
################################################################################

all:	header message
		@make -s $(NAME) || $(MAKE) reset

#beautiful
header:
		@echo -n "${BLUE}"
		@echo "  _  _ ___                    _         __ _ _      "
		@echo " | || |__ \                  | |       / _(_) |     "
		@echo " | || |_ ) |  _ __ ___   __ _| | _____| |_ _| | ___ "
		@echo " |__   _/ /  | '_ \` _ \ / _\` | |/ / _ \  _| | |/ _ \\"
		@echo "    | |/ /_  | | | | | | (_| |   <  __/ | | | |  __/"
		@echo "    |_|____| |_| |_| |_|\__,_|_|\_\___|_| |_|_|\___|"
		@echo "                                         by dhubleur"
		@echo -n "${NO_COLOR}"

message:
		@make -q $(NAME) && echo "$(GREEN)Everything is already up to date ! No work for me$(NO_COLOR)" || true
		@$(call count_files)

#Compilation
$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%$(SRCS_EXTENSION)
			@mkdir -p $(dir $@)
			@$(call draw_bar)
			@echo "\r$(CYAN)Compiling $(BLUE)$@ ...$(NO_COLOR)                             "
			@$(call draw_bar)
			@$(CC) $(CFLAGS) -MMD -MF $(@:.o=.d)  ${INCLUDE_FLAGS} -c $< -o $@
			@$(call file_compiled)
			@$(call draw_bar)

$(LIBFT_COMPLETE):
		@make -C $(LIBFT_DIR) all
		@echo "$(GREEN)Compiled libft !$(NO_COLOR)"
			
#Link
-include $(OBJS_DEPEND)
$(NAME):	${OBJS} ${ALL_LIBS}
		@echo "$(ORANGE)Linking $(BLUE)$@ ...$(NO_COLOR)"
		@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(LFLAGS) -o $@ ${OBJS} ${ALL_LIBS}
		@$(call clean)
		@echo "$(GREEN)$@ created !$(NO_COLOR)"

#clean
clean:		header
		@rm -rf $(OBJS_PATH)
		@echo "$(GREEN)Removed objects !$(NO_COLOR)"

fclean:		header clean
		@rm -f $(NAME)
		@echo "$(GREEN)Removed $(NAME) !$(NO_COLOR)"

fcleanlib:	header fclean
ifeq ($(IS_LIBFT),true)
		make -C $(LIBFT_DIR) fclean
endif
ifeq ($(IS_MLX),true)
		make -C $(MLX_DIR) fclean
endif

re:			header fclean all

relib:		header fcleanlib all

#test
run:		header all
		@echo "$(BLUE)Executing...$(NO_COLOR)"
		@echo ""
		@./$(NAME) $(RUN_PARAM)

show:		header
		@echo "$(CYAN)Compilator: $(GREEN)$(CC)$(NO_COLOR)"
		@echo "$(CYAN)Flags: $(GREEN)$(CFLAGS)$(NO_COLOR)"
		@echo "$(CYAN)Includes: $(GREEN)$(INCLUDE_FLAGS)$(NO_COLOR)"
		@echo ""
		@echo "$(CYAN)Sources:$(NO_COLOR)"
		@echo "$(GREEN)$(MAIN) ${addprefix $(SRCS_PATH)/, $(SRCS)}$(NO_COLOR)"
		@echo ""
		@echo "$(CYAN)Libs:$(NO_COLOR)"
		@echo "$(GREEN)$(ALL_LIBS)$(NO_COLOR)"

#do nothing
noflag: 	all
		@echo -n ""
debug:		all
		@echo -n ""
sanadd:		all
		@echo -n ""
santhread:	all
		@echo -n ""

reset:
		@$(call clean)

vogpush: header
		@rm -rf /tmp/push_$(NAME)
		@git clone --quiet $(VOGSPHERE) /tmp/push_$(NAME)
		@echo "$(GREEN)Cloned repository !$(NO_COLOR)"
		@rm -rf /tmp/push_$(NAME)/*
		@cp -r * /tmp/push_$(NAME)/.
		@echo "$(GREEN)Updated repository !$(NO_COLOR)"
		@cd /tmp/push_$(NAME)
		@git add .
		@git commit --quiet -m "Automatic commit"
		@git push --quiet --set-upstream origin master
		@echo "$(GREEN)Pushed repository !$(NO_COLOR)"
		
.PHONY:		all header clean fclean re run fcleanlib relib noflag debug sanadd santhread show reset vogpush
