#include <stdio.h> /* printf */
#include <time.h> /* time_t */

#include "bits_array.h"
#include "knight_tour.h"

#define BOARD_IS_FULL (0xFFFFFFFFFFFFFFFF)
#define BOARD_SIZE (64)
#define COL (8)
#define FAILURE (1)
#define FALSE (0)
#define FIVE_MINUTES (300)
#define ROW (8)
#define SUCCESS (0)
#define TIME_OVER (2)
#define TRUE (1)

int moves_table[2][COL] = { {-2,-1, 1,  2,  2,  1, -1, -2}, 
                          {   1, 2, 2,  1, -1, -2, -2, -1} };

int path_board[ROW][COL] = {0};
int board_lut[ROW][COL];

static int GetBitArrayIndex(int row, int col);
static int IsValidMove(int x, int y, unsigned long board);
static int FindIndexWithMinOptions(int moves_number, int *set_of_options, unsigned long board, unsigned long options_index_visited);
static int GetNextIndexToMove(int index, int *set_of_options, unsigned long board);
static int KnightTourClockWise(int index, unsigned long board, int step, int *route, time_t time_start);
static void GetMatrixIndex(int index, int *row, int *col);

int KnightTourHeuristic(int index, unsigned long board, int *route, time_t time_start)
{
	int *set_of_options = malloc(sizeof(int) * ROW);
	int i = 0;
	int index_to_move = 0;
	int moves_number = 0;
	unsigned long options_index_visited = 0;

	board = SetBitOn(board, (size_t)index);
	*route = index;

	if (time(NULL) > time_start + FIVE_MINUTES)
	{
		free(set_of_options);
		set_of_options = NULL;
		
		return (TIME_OVER);
	}

	if (board == BOARD_IS_FULL)
	{
		free(set_of_options);
		set_of_options = NULL;

		return (SUCCESS);
	}

	moves_number = GetNextIndexToMove(index, set_of_options, board);

	for (i = 0; i < moves_number; ++i)
	{
		index_to_move = FindIndexWithMinOptions(moves_number, set_of_options, board, options_index_visited);
		options_index_visited = SetBitOn(options_index_visited, index_to_move);
		route++;

		if (SUCCESS == KnightTourHeuristic(index_to_move, board, route, time_start))
		{
			free(set_of_options);
			set_of_options = NULL;

			return (SUCCESS);
		}

		route--;
	}

	free(set_of_options);
	set_of_options = NULL;

	return (FAILURE);
}
int KnightTour(int index, int board, int *route, time_t start_time)
{
	int step = 0;

	return (KnightTourClockWise(index, board, step, route, start_time));
}

static int KnightTourClockWise(int index, unsigned long board, int step, int *route, time_t time_start)
{
	int i = 0;
	int row, col;

	board = SetBitOn(board, index);
	*route = index;

	GetMatrixIndex(index, &row, &col);
	path_board[row][col] = step;

	if (time(NULL) > time_start + FIVE_MINUTES)
	{
		return (TIME_OVER);
	}

	if (board == BOARD_IS_FULL)
	{
		return (SUCCESS);
	}

	for (i = 0; i < ROW; ++i)
	{
		if (IsValidMove(row + moves_table[0][i], col + moves_table[1][i], board))
		{
			index = GetBitArrayIndex(row + moves_table[0][i], col + moves_table[1][i]);

			if (KnightTourClockWise(index, board, step + 1, route, time_start) == SUCCESS)
			{
				return (SUCCESS);
			}
		}
	}

	return (FAILURE);
}

static int GetNextIndexToMove(int index, int *set_of_options, unsigned long board)
{
	int possible_moves_number = 0;
	int index_to_move = 0;
	int row_move_index = 0;
	int col_move_index = 0;
	int col, row;
	int i;

	GetMatrixIndex(index, &row, &col);

	for (i = 0; i < COL; ++i)
	{
		row_move_index = row + moves_table[0][i];
		col_move_index = col + moves_table[1][i];
		index_to_move = GetBitArrayIndex(row_move_index, col_move_index);

		if (IsValidMove(row_move_index, col_move_index, board))  
		{
			set_of_options[possible_moves_number] = index_to_move;
			possible_moves_number++; 
		}
	}

	return (possible_moves_number);
}

static int FindIndexWithMinOptions(int moves_number, int *set_of_options, unsigned long board, unsigned long options_index_visited)
{
	int hold_options_temp[ROW];
	int option_num = 0;
	int min = ROW + 1;
	int index_of_min_moves = 0;
	int i;

	for (i = 0; i < moves_number; ++i)
	{
		if (IsBitOff(options_index_visited, set_of_options[i]) && IsBitOff(board, set_of_options[i]))
		{
			option_num = GetNextIndexToMove(set_of_options[i], hold_options_temp, board);
		}
		
		if (option_num < min )
		{
			min = option_num;
			index_of_min_moves = set_of_options[i];
		}
	}

	return (index_of_min_moves);
} 

static int IsValidMove(int row, int col, unsigned long board)
{
    if (row < ROW && row >= 0 && col < COL && 
    	col >= 0 && path_board[row][col] == 0 && 
    	IsBitOff(board, GetBitArrayIndex(row, col)))
    {
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}

static void GetMatrixIndex(int index, int *row, int *col)
{
	*row = index / ROW;
	*col = index % COL;
}

static int GetBitArrayIndex(int row, int col)
{
	return ((row * ROW) + (col % COL));
}

void InitLUT()
{
	int row, col, num = 0;
	
	for (row = 0; row < ROW; ++row)
	{ 
		for (col = 0; col < COL; ++col, num++)
		{
			board_lut[row][col] = num;
		}
	}
}

void PrintTour(int *route)
{
	int i;

	printf("\n===============KNIGHT'S TOUR HEURISTIC===============\n");

	for (i = 0; i < BOARD_SIZE; ++i)
	{

		printf("%d->", route[i]);
		
		if (i % ROW == 0)
		{
			printf("\n");
		}
	}

	printf("|||END|||\n");
	printf("======================================================\n");
}

void PrintBoard()
{
	int i, j;

	printf("\n===============KNIGHT'S TOUR CLOCK WISE===============\n");

	for (i = 0; i < ROW; ++i)
	{
		for (j = 0; j < COL; ++j)
		{
			printf("%d  |  ", path_board[i][j]);
		}

		if (j % ROW == 0)
		{
			printf("\n");
		}
	}

	printf("======================================================\n");
}
