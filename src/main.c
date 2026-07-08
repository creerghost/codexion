#include "codexion.h"

void	init_sim(t_sim *sim)
{
	sim->num_coders = 0;
	sim->time_to_burnout = 0;
	sim->time_to_compile = 0;
	sim->time_to_debug = 0;
	sim->time_to_refactor = 0;
	sim->num_compiles_req = 0;
	sim->dongle_cooldown = 0;
	sim->scheduler = 0;
	sim->coders = NULL;
	sim->dongles = NULL;
	sim->active_coders = 0;
	sim->start_time = 0;
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	init_sim(&sim);
	return (!parse_args(argc, argv, &sim));
}
