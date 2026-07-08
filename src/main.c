#include "codexion.h"

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (!init_context(argc, argv, &ctx))
		return (1);
	return (0);
}
