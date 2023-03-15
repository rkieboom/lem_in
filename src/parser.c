#include "header.h"
#include "parse.h"
#include <stdio.h>

/*
**	Count ants amount and add them to the list
*/
static int count_ants_amount(t_list *list, char *buf)
{
	int	amount;

	if (!buf)
		return (ft_putendl_fd("Error: no ants amount!", 2), 1);
	amount = ft_atoi(buf);
	if (amount <= 0)
		return (ft_putendl_fd("Error: invalid ants amount!", 2), 1);
	list->ants = ft_calloc(amount, sizeof(t_ant));
	if (!list->ants)
		return (ft_putendl_fd("Error: malloc went wrong!", 2), 1);

	list->ants_amount = amount;
	return (0);
}


/*
** A after check to make sure that there is a start and end room / rooms at all
*/
static int after_check(t_list *list)
{
	t_room	*room;
	int		has_start = 0;
	int		has_end = 0;

	if (!list->rooms)
		return (ft_putendl_fd("Error: no rooms!", 2), 1);
	while (room)
	{
		if (room->is_start)
			has_start = 1;
		if (room->is_end)
			has_end = 1;
		room = room->next;
	}
	if (!has_start || !has_end)
		return (ft_putendl_fd("Error: no start or end room!", 2), 1);
}

/*
** Parse data from stdin
*/
int	parser(t_list *list)
{
	char	*buf;

	buf = get_next_line(0);
	if (count_ants_amount(list, buf))
		return (free(buf), 1);
	while (buf != NULL)
	{
		free(buf);
		buf = get_next_line(0);
		if (parser_read_data(list, buf))
			return (1);
	}
	if (after_check(list))
		return (1);
	return (0);
}
