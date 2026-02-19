#include "utils.h"
// BORRAR
int	read_int()
{
	int	res, val;

	do
	{
		res = scanf("%d", &val);
	} while (res != 1);

	return val;
}

void 	read_filename(char *filename)
{
	int	res;

	do
	{
		res = scanf("%s", filename);
	} while (res != 1);
}

int	max(int	a, int	b)
{
	return (a > b ? a : b);
}

int	min(int	a, int	b)
{
	return (a < b ? a : b);
}

bool	is_valid(FILE *file)
/*
	this function to validate the file that	is passed as
	load file to check if just contain the expected characters
	and the header is correct also, we make sure to rewind the file.
*/
{
	int		score, level, rows, columns;
	int		count_player = 0;
	int		count_boxes = 0;
	int		count_goals = 0;
	char	c;

	if (file == NULL)
		return false;

	if (fscanf(file, "Score: %d\n", &score) != 1) return false;
	if (fscanf(file, "Level: %d\n", &level) != 1) return false;
	if (fscanf(file, "State:\n") != 0) return false;
	if (fscanf(file, "rows: %d\n", &rows) != 1) return false;
	if (fscanf(file, "columns: %d\n", &columns) != 1) return false;

	if (rows <= 0 || columns <= 0)
		return false;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (fscanf(file, "%c", &c) != 1)
				return false;

			if (c != '#' && c != '.' && c != 'A' && c != 'G'
			    && c != 'Y' && c != 'X' && c != 'B')
				return false;

			if (c == 'A' || c == 'Y')
				count_player++;
			if (c == 'B')
				count_boxes++;
			if (c == 'G' || c == 'Y')
				count_goals++;
		}

		if (fscanf(file, "\n") != 0)
			return false;
	}

	if (count_player != 1)
		return false;
	if (count_boxes != count_goals)
		return false;

	rewind(file);
	return true;
}
