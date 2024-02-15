/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:29 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/15 19:16:19 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

// TODO: heredoc gestion - The below functions are temporary

static void ft_here_doc_add(t_shell *shell, char *filename_path)
{
	t_heredocs	*new;
	t_heredocs	*tmp;

	new = malloc(sizeof(t_heredocs));
	if (!new)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	new->heredoc_path = filename_path;
	new->next = NULL;
	if (!shell->heredocs)
	{
		shell->heredocs = new;
		return ;
	}
	tmp = shell->heredocs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// TODO: heredoc gestion
static void	ft_here_doc_loop(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		write(1, HBLU, ft_strlen(HBLU));
		write(1, "📬 ", 6);
		write(1, "➜ ", 5);
		write(1, RESET, ft_strlen(RESET));
		line = get_next_line(0, 0);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			write(1, "📪\n", 6);
			get_next_line(0, 1);
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

/**
 * * Here_doc
 * @return 0 on success, 1 on failure
 * @note Write the heredoc in a file called "here_doc"
*/
static int	ft_here_doc_temporaire(t_shell *shell, t_token *word)
{
	int		fd;
	char	*filename;
	
	filename = "here_doc";
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Couldn't create here_doc\n", 2);
		return (EXIT_FAILURE);
	}
	ft_here_doc_loop(word->value, fd);
	ft_here_doc_add(shell, filename);
	return (EXIT_SUCCESS);
}

/**
 * @brief Parse the tokens
 * @param lexic: Token list
 * @param shell: Shell structure
 * @note This function will parse the tokens and create the commands table
 */
void	parser(
	t_lexer *lexic,
	t_shell *shell
)
{
	// (void)lexic;
	// (void)shell;
	t_token	*tmp;
	t_table	*cmd;

	tmp = lexic->head;
	cmd = new_cmd();
	cmd_add(&shell->table_head, cmd);
	while (tmp != NULL)
	{
		if (tmp->type == pipe_token)
		{
			cmd = new_cmd();
			cmd_add(&shell->table_head, cmd);
		}
		// else if (tmp->type == greater)
		// {
		// 	add_outfd(&shell->table_head, &tmp);
		// }
		// else if (tmp->type == dgreater)
		// {
		// 	add_outfd(&shell->table_head, &tmp);
		// }
		else if (tmp->type == less)
		{
			tmp = tmp->next;
			cmd_infile(cmd, shell, inf_file, tmp->value);
		}
		else if (tmp->type == dless)
		{
			tmp = tmp->next;
			// TODO: heredoc gestion
			ft_here_doc_temporaire(shell, tmp);
			cmd_infile(cmd, shell, inf_heredoc, "here_doc");
		}
		// else
		// {
		// 	add_arg(&shell->table_head, &tmp);
		// }
		tmp = tmp->next;
	}
}
