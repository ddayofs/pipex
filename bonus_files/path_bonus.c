/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:05:56 by donglee2          #+#    #+#             */
/*   Updated: 2023/07/13 20:37:21 by donglee2         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_err(char *extracted_cmd)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(extracted_cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

char	*find_cmd_path(char *extracted_cmd, char **envp)
{
	char	*path;
	char	**split_path;
	int		i;
	char	*ret;

	path = find_path(envp);
	if (!path)
		exit(1);
	split_path = ft_split(path, ':');
	if (!split_path)
		exit (1);
	i = -1;
	while (split_path[++i])
	{
		split_path[i] = add_cmd_to_path(split_path[i], extracted_cmd);
		if (!access(split_path[i], X_OK))
		{
			ret = ft_strdup(split_path[i]);
			free_all_splits(split_path);
			return (ret);
		}
	}
	print_err(extracted_cmd);
	exit(127);
}
