/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:28 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 18:56:46 by rcutte           ###   ########.fr       */
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
