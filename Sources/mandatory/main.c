/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:28 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/21 09:26:45 by abourgeo         ###   ########.fr       */
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

void	init_minishell(t_shell *shell, t_exec *exec_struct, char **envp)
{
	if (isatty(STDIN_FILENO) == 0)
	{
		write(2, "Error: not a terminal\n", 22);
		exit(1);
	}
	ft_shell_init(shell, envp);
	init_exec_struct(exec_struct, shell, envp);
	rl_catch_signals = 0;
}

void	handle_input(
			t_shell *shell,
			t_exec *exec_struct,
			t_lexer *lexic,
			char *input)
{
	if (lexer(input, lexic) == true)
	{
		parser(lexic, shell);
		free_tokens(lexic->head);
		if (g_signal != SIGINT)
			starting_execution(exec_struct, input);
		ft_free_here_docs(shell);
		ft_free_cmds(shell);
	}
	else
		shell->exit_code = 1;
}
// print_tokens(lexic.head);
// print_cmds(shell);

int	check_readline_and_signals(t_shell *shell, char *input, int ac, char **av)
{
	(void)ac;
	(void)av;
	if (input == NULL)
	{
		write(2, "exit\n", 5);
		return (0);
	}
	if (g_signal != 0)
	{
		shell->exit_code = g_signal + 128;
		g_signal = 0;
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	shell;
	t_lexer	lexic;
	t_exec	exec_struct;

	init_minishell(&shell, &exec_struct, envp);
	while (1)
	{
		signal(SIGINT, &sig_handler_interactive);
		signal(SIGQUIT, SIG_IGN);
		input = readline(PROMPT);
		if (check_readline_and_signals(&shell, input, ac, av) == 0)
			break ;
		if (ft_strlen(input) > 0)
		{
			handle_input(&shell, &exec_struct, &lexic, input);
			add_history(input);
			free(input);
		}
		dup2(shell.std_in, 0);
		dup2(shell.std_out, 1);
	}
	ft_free_all(&shell);
	free_exec_struct(exec_struct);
	return (shell.exit_code);
}

// echo "$PATH$USER" not working
// wilcards ?
// faut-il verif token->next == NULL ? parser.c line 62 (syntax error a priori)