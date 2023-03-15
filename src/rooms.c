#include "header.h"


/*
** Gets the end room
*/
t_room *get_end_room(t_room *rooms)
{
	t_room *tmp;

	tmp = rooms;
	while (tmp)
	{
		if (tmp->is_end == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_room *get_start_room(t_room *rooms)
{
	t_room *tmp;

	tmp = rooms;
	while (tmp)
	{
		if (tmp->is_start == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_room	*find_room(t_room* head, char *find)
{
	while (head)
	{
		if (ft_strncmp(find, head->name, ft_strlen(find) + 1) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}
