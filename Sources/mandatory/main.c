/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:28 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 09:19:08 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_shell_init(t_shell *shell, char **envp)
{
	shell->env = malloc(sizeof(t_env_list *));
	if (shell->env == NULL)
	{
		ft_putstr_fd("Error: malloc shell failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	*shell->env = init_list(*shell->env, envp);
	shell->table_head = NULL;
	shell->heredocs = NULL;
	shell->std_in = STDIN_FILENO;
	shell->std_out = STDOUT_FILENO;
	shell->exit_code = 0;
}

char	*get_current_dir(void)
{
	int		i;
	char	*temp;
	char	*current_dir;

	temp = getcwd(NULL, 0);
	if (temp == NULL)
		return (NULL);
	i = ft_strlen(temp);
	while (i >= 0 && temp[i] != '/')
		i--;
	if (i == -1 || temp[i + 1] == '\0')
	{
		free(temp);
		return (ft_strdup("/"));
	}
	current_dir = ft_strdup(&temp[i + 1]);
	free(temp);
	return (current_dir);
}

char	*get_prompt(void)
{
	char	*current_dir;
	char	*old_prompt;
	char	*prompt;

	current_dir = get_current_dir();
	prompt = ft_strjoin(current_dir, "\e[1;33m ➜ \033[0m");
	free(current_dir);
	old_prompt = prompt;
	prompt = ft_strjoin("\e[1;38;5;141mMiniShell\001\e[37;0m\002:\001\e[34;1m\002", old_prompt);
	free(old_prompt);
	return (prompt);
}

// cat (without options) not working

int	main(int ac, char **av, char **envp)
{
	char* 		input;
	t_shell 	shell;
	t_lexer 	lexic;
	t_exec		exec_struct;

	(void)ac;
	(void)av;
	if (isatty(STDIN_FILENO) == 0)
	{
		write(2, "Error: not a terminal\n", 22);
		return (1);
	}
	ft_shell_init(&shell, envp);
	init_exec_struct(&exec_struct, &shell, envp);
	while(1)
	{
		input = readline(PROMPT);
		if (ft_strlen(input) > 0)
		{
			if (lexer(input, &lexic) == true)
			{
				// print_tokens(lexic.head);
				parser(&lexic, &shell);
				// print_cmds(shell);
				free_tokens(lexic.head);
				starting_execution(&exec_struct);
				// TODO: exec
				// TODO: wait and signal
				ft_free_cmds(&shell);
			}
			add_history(input);
			free(input);
		}
	}
	ft_free_all(&shell);
	free_exec_struct(exec_struct);
	return 0;
}

// EXPORT ISSUE : PATH="DEFRF" est un seul argument. Comme "d"d equivaut a dd