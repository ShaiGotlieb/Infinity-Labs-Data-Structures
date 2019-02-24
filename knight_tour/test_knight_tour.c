#include <stdio.h> /* printf */
#include <time.h> /* time_t */

#include "knight_tour.h"

#define BOARD_SIZE (64)

int main()
{
	int route[BOARD_SIZE];
	int index = 0;
	int status;
	unsigned long board = 0;
	time_t start_time = time(NULL);

	InitLUT();

	status = KnightTourHeuristic(index, board, route, start_time);
	PrintTour(route);
	
	status = KnightTour(index, board, route, start_time);
	PrintBoard();

	return (status);
}