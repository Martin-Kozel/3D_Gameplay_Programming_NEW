#include "./include/debug.h"

#include "./include/game.h"

/**
 * Main entry point for the OpenGL cube program
 * Allocates game structure and starts the game loop
 *
 * @return int Returns 0 on successful execution
 */
int main(void)
{
	// Allocate memory for the game structure
	// Cast to Game* to ensure proper pointer type
	Game *game = (Game *)malloc(sizeof(Game));

	// Check if memory allocation was successful
	if (game == NULL)
	{
		DEBUG_MSG("Failed to allocate memory for game structure\n");
		return EXIT_FAILURE;
	}

	// Start the game loop by calling run function
	run(game);

	// Free allocated memory to prevent memory leaks
	free(game);

	return EXIT_SUCCESS;
}