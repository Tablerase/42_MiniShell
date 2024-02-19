/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:01:17 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 18:59:29 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

// /**
//  * TEMP FUNCTION
// */
// void	init_table(t_table *table)
// {
// 	table->cmd = "ls";
// 	table->args = malloc(6 * sizeof(char *));
// 	table->args[0] = ft_strdup("hello");
// 	table->args[1] = NULL;
// 	table->infd_head = NULL;
// 	// table->infile = malloc(2 * sizeof(char *));
// 	// table->infile[0] = ft_strdup("hello");
// 	// table->infile[1] = NULL;
// 	table->outfd_head = NULL;
// 	// table->outfile = malloc(10 * sizeof(t_outf *));
// 	// table->outfile[0] = malloc(sizeof(t_outf));
// 	// table->outfile[0]->file = ft_strdup("out.txt");
// 	// table->outfile[0]->append = 0;
// 	// table->outfile[1] = malloc(sizeof(t_outf));
// 	// table->outfile[1]->file = ft_strdup("out2.txt");
// 	// table->outfile[1]->append = 0;
// 	// table->outfile[2] = NULL;
// 	table->next = NULL;
// }

// /**
//  * TEMP FUNCTION
// */
// void	init_shell(t_shell *shell, char **envp)
// {
// 	shell->env = envp;
// 	shell->std_in = dup(0);
// 	shell->std_out = dup(1);
// 	shell->table_head = malloc(sizeof(t_table));
// 	init_table(shell->table_head);
// 	shell->heredocs = NULL;
// }

/**
 * Initialize our execution structure.
 * @param exec_struct The execution struction we are initializing.
 * @param envp TEMP PARAM BCS IN t_struct.
*/
int	init_exec_struct(t_exec *exec_struct, char **envp)
{
	exec_struct->env_list = NULL;
	exec_struct->export_list = NULL;
	exec_struct->shell = NULL;
	exec_struct->exit_status = 0;
	exec_struct->shell = malloc(sizeof(t_shell));
	if (exec_struct->shell == NULL)
		return (0);
	init_shell(exec_struct->shell, envp);
	exec_struct->env_list = malloc(sizeof(t_env_list *));
	if (exec_struct->env_list == NULL)
		return (0);
	*(exec_struct->env_list) = init_list(*(exec_struct->env_list),
			exec_struct->shell->env);
	if (*(exec_struct->env_list) == NULL && *envp != NULL)
		return (0);
	exec_struct->export_list = malloc(sizeof(t_env_list *));
	if (exec_struct->export_list == NULL)
		return (0);
	*(exec_struct->export_list) = init_list(*(exec_struct->export_list),
			exec_struct->shell->env);
	if (*(exec_struct->export_list) == NULL && *envp != NULL)
		return (0);
	sort_export_list(exec_struct->export_list);
	return (1);
}

/**
 * Sorts the export_list which will be printed when the
 * export command is called.
 * @param export_list The list we are sorting.
*/
void	sort_export_list(t_env_list **export_list)
{
	t_env_list	*tmp_list;
	t_env_list	*new_pos;
	t_env_list	*min;
	char		*tmp_val;

	tmp_list = *export_list;
	while (tmp_list != NULL)
	{
		new_pos = tmp_list->next;
		min = tmp_list;
		while (new_pos != NULL)
		{
			if (ft_strcmp(min->name, new_pos->name) > 0)
				min = new_pos;
			new_pos = new_pos->next;
		}
		tmp_val = min->name;
		min->name = tmp_list->name;
		tmp_list->name = tmp_val;
		tmp_val = min->value;
		min->value = tmp_list->value;
		tmp_list->value = tmp_val;
		tmp_list = tmp_list->next;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
