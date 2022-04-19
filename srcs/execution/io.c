/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:01:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/04/19 18:09:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_dprintf.h"
#include <readline/readline.h>

void	*add_io(t_arg *node, t_command *command)
{
	t_dlist	**dest_io;
	t_dlist	*elem;

	if (node->type == ARG_REDIRECT_STDIN)
	{
		dest_io = &command->io_in;
		if (command->here_doc > 0)
		{
			close(command->here_doc);
			command->here_doc = -1;
		}
	}
	if (node->type == ARG_REDIRECT_FILE
		|| node->type == ARG_REDIRECT_FILE_APPEND)
		dest_io = &command->io_out;
	elem = ft_dlstnew(node);
	if (!elem)
		return (NULL);
	ft_dlstadd_back(dest_io, elem);
	return (elem);
}

static int	treat_line(char *line, t_arg *node, int pipefd[2],
		t_command *command)
{
	if (ft_strnstr(line, node->value, ft_strlen(line)) == NULL)
	{
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		return (0);
	}
	else
	{
		command->here_doc = pipefd[0];
		free(line);
		return (1);
	}
}

static void	here_doc_read(t_arg *node, int pipefd[2], t_command *command)
{
	char	*line;
	int		count;

	count = 1;
	while (1)
	{
		line = readline("> ");
		if (line != NULL)
		{
			if (treat_line(line, node, pipefd, command))
				break ;
			count++;
		}
		else
		{
			if (g_sigint)
			{
				ft_dprintf(1, "\n");
				break ;
			}
			ft_dprintf(1, HERE_DOC_EOF, count, node->value);
			break ;
		}
	}
}

void	here_doc_logic(t_arg *node, t_command *command)
{
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		ft_dprintf(STDOUT_FILENO, PIPE_ERROR);
		exit(1);
	}
	set_signals_as_here_doc();
	here_doc_read(node, pipefd, command);
	set_signals_as_prompt();
	close(pipefd[1]);
	command->here_doc = pipefd[0];
}
