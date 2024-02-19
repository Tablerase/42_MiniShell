/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:30:58 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 19:53:02 by abourgeo         ###   ########.fr       */
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

// heredoc.c

void		ft_free_filling_heredoc(t_filling_heredoc *heredoc);
void		initialize_filling_heredoc(t_filling_heredoc *heredoc);
int			filename(t_shell *shell, t_filling_heredoc *heredoc);
int			add_heredoc_filename(t_shell *shell, char *name);
int			create_new_line(t_filling_heredoc *heredoc, int *i, int j);
int			affect_var_name(t_env_list **env_list, t_filling_heredoc *heredoc, int *i);
int			expanding_line(t_env_list **env_list, t_filling_heredoc *heredoc, int *i);
char		*expand_var_heredoc(t_env_list **env_list, t_filling_heredoc *heredoc);
int			create_heredoc(t_shell *shell, char *lim, bool expand);

// main.c

int			is_builtin(char *cmd);
int			builtin_execution(t_exec *exec_struct, t_table *table);
void		exec_single_cmd(t_exec *exec_struct);
void		starting_execution(t_exec *xec_struct);

// pipex.c

t_pipex		*create_pipex_fds(t_exec *exec_struct, int nb_cmd);
int			builtin_in_pipe(t_pipex *pipex, t_table *table_cmd);
int			command_in_pipe(t_pipex *pipex, t_table *table);
void		start_child_process(t_pipex *pipex, t_table *table_cmd, int nb_child);
void		exec_multiple_cmds(t_exec *exec_struct, int nb_cmd);

// redirection.c

int			redirections(t_shell *shell, t_table *table);
int			add_heredocpath(t_heredocs *heredocs, char *filename);
int			redirect_input(t_shell *shell, t_inf *infile);
int			redirect_output(t_outf *outfile);
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
int			init_exec_struct(t_exec *exec_struct, t_shell *shell, char **envp);
void		sort_export_list(t_env_list **export_list);
int			ft_strcmp(const char *s1, const char *s2);

// utils_pipex.c

void		error_forking(int *pid, int **fd, int i);
void		clear_all_fds(int **fd, int nb_fd);
int			exit_child_process(t_pipex *pipex, int status);
void		redirect_into_pipes(t_pipex *pipex, int nb_child);
int			waiting(t_pipex *pipex, int nb_child);

// single_process.c

int			single_process(t_exec *exec_struct, t_table *table);
int			execve_fail(char *path_cmd, char **args_cmd, char **env);
char		**copy_env(t_env_list **env_list);
char		*get_env_line(t_env_list *line);
char		**get_args_cmd(char **args);

// utils_pipe.c

char		*find_path(t_env_list **env_list, char *cmd);
char		*search_path(char *path, char *cmd);
char		*try_path(char *first_part, char *cmd);
int			size_list(t_env_list **list);

#endif