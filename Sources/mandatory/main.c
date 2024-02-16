/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:28 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/16 16:34:00 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_shell_init(t_shell *shell, char **envp)
{
	shell->env = ft_strs_dup(envp);
	if (!shell->env)
	{
		ft_putstr_fd("Error: env malloc failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	shell->table_head = NULL;
	shell->heredocs = NULL;
	shell->stdin = STDIN_FILENO;
	shell->stdout = STDOUT_FILENO;
}

int	main(int ac, char **av, char **envp)
{
	char* 		input;
	t_shell 	shell;
	t_lexer 	lexic;

	(void)ac;
	(void)av;
	ft_shell_init(&shell, envp);
    while(1)
	{
        input = readline(PROMPT);
        if (ft_strlen(input) > 0)
		{
			if (lexer(input, &lexic) == true)
			{
				print_tokens(lexic.head);
				parser(&lexic, &shell);
				print_cmds(shell);
				free_tokens(lexic.head);
				// TODO: exec
				// TODO: wait and signal
				ft_free_cmds(&shell);
			}
			add_history(input);
			free(input);
        }

    }
	ft_free_all(&shell);
    return 0;
}
