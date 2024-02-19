/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:30:58 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 11:54:05 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define FT_ECHO "echo"
# define EXIT "exit"
# define ENV "env"

# include "minishell.h"
# include <limits.h>
# include <dirent.h>

/**
 * Structure that stores the list of environment variables.
 * Used by export, env and unset.
 * @param name The name of the variable.
 * @param value The expansion of the associated variable.
 * @param next The next node of the list.
*/
typedef struct s_env_list	t_env_list;

/**
 * Structure that stores all the program's data.
 * @param env_list The list containing the environment variables.
 * @param export_list The list containing the environment variables (also 
 * the non-initialized variables).
 * @param shell The data returned by the parser.
 * @param exit_status The expansion of '?'
*/
typedef struct s_exec		t_exec;

struct s_env_list
{
	char		*name;
	char		*value;
	t_env_list	*next;
};

struct s_exec
{
	t_env_list	**env_list;
	t_env_list	**export_list;
	t_shell		*shell;
	int			exit_status;
};

// builtin.c

int			ft_cd(t_exec *exec_struct, t_table *table);
int			ft_echo(t_table *table);
int			ft_pwd(t_table *table);
int			ft_env(t_exec *exec_struct, t_table *table);
int			ft_unset(t_exec *exec_struct, t_table *table);

// create_env_list.c

t_env_list	*init_list(t_env_list *list, char **env);
int			add_node(t_env_list **list, char *name, char *value);
int			search_char(char *str, char c);
void		print_list(t_env_list *list, int export);

// exit.c

int			ft_exit(t_exec *exec_struct, t_table *table);
int			ft_strnum(char *str);
int			number_too_big(char *str);
long long	ft_atoll(char *str);
int			exit_code_exit(char *str);

// export.c

int			ft_export(t_exec *exec_struct, t_table *table);
int			add_new_var(t_exec *exec_struct, char *name, char *value, int sep);
int			fill_lists(t_exec *exec_struct, char *var_expr);
int			name_exists(t_exec *exec_struct, char *name, char *value, int sep);
void		change_list_value(t_env_list **list, char *name, char *value);

// free.c

void		free_process(t_exec exec_struct, char *path, char **arg,
				char **env);
void		free_tabtab(char **str);
void		free_exec_struct(t_exec exec_struct);
void		free_list(t_env_list **list);
void		free_shell(t_shell *shell);

// main.c

int			is_builtin(char *cmd);
int			builtin_execution(t_exec *exec_struct, t_table *table);
void		exec_single_cmd(t_exec *exec_struct);
void		starting_execution(t_exec *xec_struct);

// redirection.c

int			redirections(t_table *table);
int			redirect_input(char **infile);
int			redirect_output(t_outf **outfile);
int			is_a_directory(char *filename);

// utils_builtin.c

int			check_name(char *name, char *value);
int			check_if_option_export(char *arg);
int			ft_echo_option(char **args);
char		*ft_getenv(char *var_name, t_env_list **env);
void		ft_unset_list(t_env_list **list, char *name);

// utils_exec_struct.c

void		init_table(t_table *table);
void		init_shell(t_shell *shell, char **envp);
int			init_exec_struct(t_exec *exec_struct, char **envp);
void		sort_export_list(t_env_list **export_list);
int			ft_strcmp(const char *s1, const char *s2);

// single_process.c

int			single_process(t_exec *exec_struct, t_table *table);
int			execve_fail(char *path_cmd, char **args_cmd, char **env);
char		**copy_env(t_env_list **env_list);
char		*get_env_line(t_env_list *line);
char		**get_args_cmd(char *cmd, char **args);

// utils_pipe.c

char		*find_path(t_env_list **env_list, char *cmd);
char		*search_path(char *path, char *cmd);
char		*try_path(char *first_part, char *cmd);
int			size_list(t_env_list **list);

#endif