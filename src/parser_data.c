#include "header.h"
#include "parse.h"
#include <stdio.h>

static int	array_len(char **arr)
{
	int	i = 0;

	while (arr[i])
		i++;
	return (i);
}

static void	free_array(char **arr)
{
	int	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}


/*
** Function to get the type of data
** Can either be a room(COMMON, START, END), a link, a comment or an error
*/
static int	get_type_of_data(t_list *list, char *buf)
{
	if (buf[0] == '#')
	{
		if (buf[1] == '#')
		{
			if (ft_strncmp(buf, "##start", ft_strlen(buf) + 1) == 0)
				return (START);
			else if (ft_strncmp(buf, "##end", ft_strlen(buf) + 1) == 0)
				return (END);
			else
				return (ERROR);
		}
		else
			return COMMENT;
	}
	if (ft_strchr(buf, ' '))
		return (NORMAL);
	else if (ft_strchr(buf, '-'))
		return (LINK);
	return (ERROR);
}

/*
** Function to add a room
*/
static int	ladd_room(t_list *list, enum e_room_type type, char *line)
{
	int		x,y;
	char	**splitted;

	if (!line)
	{
		line = get_next_line(0);
		if (!line)
			return (1);
	}
	splitted = ft_split(line, ' ');
	if (!splitted || array_len(splitted) != 3)
		return (free(line), free_array(splitted), 1);
	free(line);
	line = ft_strdup(splitted[0]);
	x = ft_atoi(splitted[1]);
	y = ft_atoi(splitted[2]);
	if (!line || x < 0 || y < 0 || add_room(list, line, x, y))
		return (free(line), free_array(splitted), 1);
	//Setting room to start or end if needed
	t_room *room = last_room(list);
	if (type == START)
		room->is_start = 1;
	else if (type == END)
		room->is_end = 1;
	return (free(line), free_array(splitted), 0);
}

/*
** Function to add a link
*/
static int	ladd_link(t_list *list, char *line)
{
	t_room	*room;
	char	**splitted;

	splitted = ft_split(line, '-');
	if (array_len(splitted) != 2)
		return (free_array(splitted), 1);
	room = find_room(list->rooms, splitted[0]);
	if (!room || !find_room(list->rooms, splitted[1]))
		return (free_array(splitted), 1);
	
	if (!room->links)
	{
		room->links = ft_calloc(sizeof(2), sizeof(char *));
		if (!room->links)
			return (1);
		room->links[0] = line;
		room->links[1] = 0;
		return 0;
	}
	else
	{
		int i = 0;
		while (room->links[i])
			i++;
		char **new_links = ft_calloc(sizeof(i + 2), sizeof(char *));
		if (!new_links)
			return (1);
		new_links[i + 1] = line;
		new_links[i + 2] = NULL;
		while (i >= 0)
		{
			new_links[i] = room->links[i];
			i--;
		}
		free(room->links);
		room->links = new_links;
	}
	return (0);
}

/*
** Adds room and links to the list
*/
int	parser_read_data(t_list *list, char *buf)
{
	enum e_room_type type;

	if (!buf)
		return (0);
	type = get_type_of_data(list, buf);
	if (type == ERROR)
		return (ft_putendl_fd("Error: input not in correct format!", 2), 1);
	else if (type == COMMENT)
		return (0);
	else if (type == NORMAL)
	{
		if (ladd_room(list, type, ft_strdup(buf)))
			return (ft_putendl_fd("Error: something went wrong adding room!", 2), 1);
	}
	else if (type == START || type == END)
	{
		if (ladd_room(list, type, NULL))
			return (ft_putendl_fd("Error: something went wrong adding room!", 2), 1);
	}
	else if (type == LINK)
		if (ladd_link(list, buf))
			return (ft_putendl_fd("Error: something went wrong adding link!", 2), 1);
	return (0);
}
