#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	t_heap heap;
	int i;
	int popped_id;

	if (argc < 2)
		return (1);
	
	if (!ft_heap_new(&heap, argc - 1))
		return (1);
	
	i = 1;
	while (i < argc)
	{
		ft_heappush(&heap, atoi(argv[i]), atoi(argv[i]));
		i++;
	}
	
	while (ft_heappop(&heap, &popped_id))
	{
		printf("%d ", popped_id);
	}
	printf("\n");
	ft_heapfree(&heap);
	return (0);
}
