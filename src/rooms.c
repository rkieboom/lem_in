#include "header.h"
#include "parse.h"

static t_room	*create_room(char *name, int x, int y)
{
	t_room	*room;

	room = ft_calloc(1, sizeof(t_room));
	if (!room)
		return (NULL);
	room->name = ft_strdup(name);
	if (!room->name)
		return (NULL);
	room->x = x;
	room->y = y;
	return (room);
}

int		add_room(t_list *list, char *name, int x, int y)
{
	t_room	*room;
	t_room	*last;

	room = create_room(name, x, y);
	if (!room)
		return (ft_putendl_fd("Error: malloc went wrong!", 2), 1);
	if (!list->rooms)
		return (list->rooms = room, 0);
	last = last_room(list);
	last->next = room;
	return (0);
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

t_room	*last_room(t_list *list)
{
	t_room	*room;

	room = list->rooms;
	while (room->next)
		room = room->next;
	return (room);
}

