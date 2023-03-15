#include "header.h"

static void free_list(void)
{
	
}

int main(void)
{
	t_list list;

	ft_bzero(&list, sizeof(t_list));
	if (parser(&list))
		return (ft_putendl_fd("Error: parser went wrong!", 2), 1);



	system("leaks lem_in");
	return (0);
}
