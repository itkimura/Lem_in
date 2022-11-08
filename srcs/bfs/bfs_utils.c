/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:15:03 by thle              #+#    #+#             */
/*   Updated: 2022/11/08 18:48:21 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*pop(t_que **head)
{
	t_que	*tmp;
	t_room	*room;

	if (!head || !(*head))
		return (NULL);
	tmp = *head;
	*head = (*head)->next;
	tmp->next = NULL;
	room = tmp->room;
	free(tmp);
	tmp = NULL;
	return (room);
}

void	push(t_que **tail, t_que **head, t_que *new)
{
	if (!tail)
		return ;
	if (*head == NULL)
	{
		*tail = new;
		*head = *tail;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

t_que	*create(t_room *room)
{
	t_que	*new;

	new = (t_que *)malloc(sizeof(t_que));
	if (new)
	{
		new->room = room;
		new->next = NULL;
	}
	return (new);
}

/* push the new room and update path_nb in t_room struct*/
t_bool	push_and_update(t_bfs *b, t_room *curr, t_room *next, t_bool is_inverse)
{
	t_que	*new;

	new = create(next);
	if (new == NULL)
		return (FALSE);
	push(&(b->tail), &(b->head), new);
	b->prev[next->path_nb]->path[next->index] = curr;
	if (is_inverse == TRUE)
		b->prev[curr->path_nb]->inverse = TRUE;
	b->visited[next->index] = TRUE;
	return (TRUE);
}
