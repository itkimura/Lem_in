/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/02 11:44:17 by itkimura         ###   ########.fr       */
=======
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/04 12:24:50 by itkimura         ###   ########.fr       */
>>>>>>> origin/itoe_bfs2
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

<<<<<<< HEAD
=======
void free_bfs(t_bfs *b)
{
	free(b->visited);
	b->visited = NULL;
	free(b->prev);
	b->prev = NULL;
}

>>>>>>> origin/itoe_bfs2
void free_path(t_path *path)
{
	free(path->path);
	free(path);
	path = NULL;
}

<<<<<<< HEAD
=======
void free_paths(t_path *path)
{
	while (path)
	{
		free_path(path);
		path = path->next;
	}
}

>>>>>>> origin/itoe_bfs2
void free_que(t_que *head)
{
	t_que *next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}
