/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:28 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 14:36:46 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	g_signal;

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
	shell->std_in = dup(STDIN_FILENO);
	shell->std_out = dup(STDOUT_FILENO);
	shell->exit_code = 0;
}

void	sig_handler_interactive(int signum)
{
	if (signum == SIGINT) //ctrl-C interactive mode
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = SIGINT;
	}
}

void	sig_handler_non_interactive(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		g_signal = SIGINT;
	}
	if (signum == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_signal = SIGQUIT;
	}
}

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
		signal(SIGINT, &sig_handler_interactive);
		signal(SIGQUIT, SIG_IGN);
		input = readline(PROMPT);
		if (input == NULL) // ctrl-D with no text
		{
			write(2, "exit\n", 5);
			break ;
		}
		if (g_signal != 0)
		{
			shell.exit_code = g_signal + 128;
			g_signal = 0;
		}
		if (ft_strlen(input) > 0)
		{
			if (lexer(input, &lexic) == true)
			{
				// print_tokens(lexic.head);
				parser(&lexic, &shell);
				// print_cmds(shell);
				free_tokens(lexic.head);
				starting_execution(&exec_struct);
				ft_free_cmds(&shell);
			}
			else
				shell.exit_code = 1;
			add_history(input);
			free(input);
		}
		dup2(shell.std_in, 0);
		dup2(shell.std_out, 1);
	}
	ft_free_all(&shell);
	free_exec_struct(exec_struct);
	return (0);
}

// EXPORT ISSUE : PATH="DEFRF" est un seul argument. Comme "d"d equivaut a dd
// nl : echo $? reset ?
// heredoc
// wilcards ?