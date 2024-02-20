/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:30:58 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 18:12:04 by abourgeo         ###   ########.fr       */
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

# include <limits.h>
# include <dirent.h>
# include "minishell.h"

typedef struct s_filling_heredoc
{
	int		fd;
	int		expand;
	char	*line;
	char	*limiter;
	char	*filename;
	char	*var_name;
	char	*expanded_var;
}	t_filling_heredoc;

typedef struct s_pipex
{
	int		*pid;
	int		**fd;
	int		nb_cmd;
	int		nb_child;
	t_exec	*exec_struct;
}	t_pipex;

// -------------------------------- EXECUTION --------------------------------

// execution_init.c

t_env_list		*init_list(t_env_list *list, char **env);
t_pipex			*init_pipex(t_exec *exec_struct, int nb_cmd);
int				init_exec_struct(t_exec *exec_struct, t_shell *shell,
					char **envp);
void			init_filling_heredoc(t_filling_heredoc *heredoc);

// execution_start.c

void			starting_execution(t_exec *exec_struct, char *input);
void			exec_single_cmd(t_exec *exec_struct, char *input);
void			executing_single_builtin(t_exec *exec_struct);
void			executing_no_command(t_exec *exec_struct);
void			update_exit_code_single_child_process(t_exec *exec_struct,
					int status);

// execution_heredoc.c

int				create_heredoc(t_shell *shell, char *lim, bool expand);
int				filename(t_shell *shell, t_filling_heredoc *heredoc);
int				add_heredoc_filename(t_shell *shell, char *name);
void			ft_free_here_docs(t_shell *shell);
void			ft_free_filling_heredoc(t_filling_heredoc *heredoc);

// execution_expand_line_heredoc.c

char			*expand_var_heredoc(t_shell *shell, t_filling_heredoc *heredoc);
int				expanding_line(t_shell *shell, t_filling_heredoc *heredoc,
					int *i);
int				affect_var_name(t_shell *shell, t_filling_heredoc *heredoc,
					int *i);
int				expand_exit_code_var_heredoc(t_shell *shell,
					t_filling_heredoc *heredoc, int *i, int j);
int				create_new_line(t_filling_heredoc *heredoc, int *i, int j);

// execution_redirections.c

int				redirections(t_table *table);
int				redirect_input(t_inf *infile);
int				redirect_output(t_outf *outfile);
int				is_a_directory(char *filename);

// execution_free.c

void			free_process(t_exec exec_struct, char *path, char **arg,
					char **env);
void			free_tabtab(char **str);
void			free_exec_struct(t_exec exec_struct);
void			free_list(t_env_list **list);

// --------------------------------- BUILTIN ---------------------------------

// builtin_call_builtins.c

int				is_builtin(char *cmd);
int				builtin_execution(t_exec *exec_struct, t_table *table);

// builtin_create_list.c

void			sort_export_list(t_env_list **export_list);
int				add_node(t_env_list **list, char *name, char *value);
int				search_char(char *str, char c);
void			print_list(t_env_list *list, int export);

// builtin_pwd_cd_echo.c

int				ft_pwd(t_table *table);
int				ft_cd(t_exec *exec_struct, t_table *table);
int				ft_echo(t_table *table);
int				ft_echo_option(char **args);

// builtin_exit.c

int				ft_exit(t_exec *exec_struct, t_table *table);
int				ft_strnum(char *str);
int				number_too_big(char *str);
long long int	ft_atoll(char *str);
int				exit_code_exit(char *str);

// builtin_export.c

int				ft_export(t_exec *exec_struct, t_table *table);
int				fill_lists(t_exec *exec_struct, char *var_expr);
int				add_new_var(t_exec *exec_struct, char *name, char *value,
					int sep);
void			change_list_value(t_env_list **list, char *name, char *value);

// builtin_utils_export.c

int				name_exists(t_exec *exec_struct, char *name, char *value,
					int sep);
int				check_name(char *name, char *value);
int				check_if_option_export(char *arg);

// builtin_env_unset.c

int				ft_unset(t_exec *exec_struct, t_table *table);
void			ft_unset_list(t_env_list **list, char *name);
int				ft_env(t_exec *exec_struct, t_table *table);
char			*ft_getenv(char *var_name, t_env_list **env);

// ---------------------------------- PIPES ----------------------------------

// pipes_execve_path.c

char			*find_path(t_env_list **env_list, char *cmd);
char			*search_path(char *path, char *cmd);
char			*try_path(char *first_part, char *cmd);

// pipes_execve_args_env.c

char			**get_args_cmd(char **args);
char			**copy_env(t_env_list **env_list);
char			*get_env_line(t_env_list *line);

// pipes_multipipes.c

void			exec_multiple_cmds(t_exec *exec_struct, int nb_cmd,
					char *input);
void			start_child_process(t_pipex *pipex, t_table *table_cmd,
					int nb_child, char *input);
int				**create_pipex_fd(int *pid, int nb_cmd);
void			redirect_into_pipes(t_pipex *pipex, int nb_child);
int				waiting(t_pipex *pipex, int nb_child);

// pipes_utils.c

int				execve_fail(char *path_cmd, char **args_cmd, char **env);
int				size_list(t_env_list **list);
int				command_not_found(t_exec *exec_struct, t_table *table,
					char *path_cmd);
int				ft_strcmp(char *s1, char *s2);

// pipes_clear_exit.c

void			clear_all_fds(int **fd, int nb_fd);
int				exit_child_process(t_pipex *pipex, int status);
void			error_forking(int *pid, int **fd, int i);
void			error_mallocing_fd(int *pid, int **fd, int i);

// pipes_execve_call.c

int				single_process(t_exec *exec_struct, t_table *table,
					char *input);
int				command_in_pipe(t_pipex *pipex, t_table *table);
int				builtin_in_pipe(t_pipex *pipex, t_table *table_cmd);

// --------------------------------- SIGNALS ---------------------------------

// signals handler

void			sig_handler_interactive(int signum);
void			sig_handler_non_interactive(int signum);

#endif