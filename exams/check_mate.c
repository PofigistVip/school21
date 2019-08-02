#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		ft_strlen(char *str)
{
	int		len;

	len = 0;
	while (*str)
	{
		++str;
		++len;
	}
	return (len);
}

int		ft_is_pawn(char cell)
{
	if (cell == 'P' || cell == 'R' || cell == 'B' || cell == 'Q')
		return (1);
	return (0);
}

int		process_pawn(char **board, int size, int i, int j)
{
	if (i == 0)
		return (0);
	if (j > 0 && board[i - 1][j - 1] == 'K')
		return (1);
	if (j < size - 1 && board[i - 1][j + 1] == 'K')
		return (1);
	return (0);
}

int		rook_left(char **board, int size, int i, int j)
{
	(void)size;
	while (--j >= 0)
		if (board[i][j] == 'K')
			return (1);
		else if (ft_is_pawn(board[i][j]) == 1)
			return (0);
	return (0);
}

int		rook_down(char **board, int size, int i, int j)
{
	while (++i < size)
		if (board[i][j] == 'K')
			return (1);
		else if (ft_is_pawn(board[i][j]) == 1)
			return (0);
	return (0);
}

int		rook_right(char **board, int size, int i, int j)
{
	while (++j < size)
		if (board[i][j] == 'K')
			return (1);
		else if (ft_is_pawn(board[i][j]) == 1)
			return (0);
	return (0);
}

int		rook_up(char **board, int size, int i, int j)
{
	(void)size;
	while (--i >= 0)
		if (board[i][j] == 'K')
			return (1);
		else if (ft_is_pawn(board[i][j]) == 1)
			return (0);
	return (0);
}

int		process_rook(char **board, int size, int i, int j)
{
	if (rook_left(board, size, i, j) == 1)
		return (1);
	if (rook_down(board, size, i, j) == 1)
		return (1);
	if (rook_right(board, size, i, j) == 1)
		return (1);
	if (rook_up(board, size, i, j) == 1)
		return (1);
	return (0);
}

int		bishop_left_up(char **board, int size, int i, int j)
{
	(void)size;
	while (--i >= 0 && --j >= 0)
		if (board[i][j] == 'K')
			return (1);
		else if (ft_is_pawn(board[i][j]) == 1)
			return (0);
	return (0);
}

int		bishop_left_down(char **board, int size, int i, int j)
{
	while (++i < size && --j >= 0)
		if (board[i][j] == 'K')
			return (1);
		else if (ft_is_pawn(board[i][j]) == 1)
			return (0);
	return (0);
}

int		bishop_right_up(char **board, int size, int i, int j)
{
	while (--i >= 0 && ++j < size)
		if (board[i][j] == 'K')
			return (1);
		else if (ft_is_pawn(board[i][j]) == 1)
			return (0);
	return (0);
}

int		bishop_right_down(char **board, int size, int i, int j)
{
	while (++i < size && ++j < size)
		if (board[i][j] == 'K')
			return (1);
		else if (ft_is_pawn(board[i][j]) == 1)
			return (0);
	return (0);
}

int		process_bishop(char **board, int size, int i, int j)
{
	if (bishop_left_up(board, size, i, j) == 1)
		return (1);
	if (bishop_left_down(board, size, i, j) == 1)
		return (1);
	if (bishop_right_up(board, size, i, j) == 1)
		return (1);
	if (bishop_right_down(board, size, i, j) == 1)
		return (1);
	return (0);
}

int		process_queen(char **board, int size, int i, int j)
{
	if (process_rook(board, size, i, j) == 1)
		return (1);
	if (process_bishop(board, size, i, j) == 1)
		return (1);
	return (0);
}

int		process_figures(char **board, int size)
{
	int		i;
	int		j;
	int		result;

	result = 0;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (board[i][j] == 'P')
				result = process_pawn(board, size, i, j);
			else if (board[i][j] == 'R')
				result = process_rook(board, size, i, j);
			else if (board[i][j] == 'B')
				result = process_bishop(board, size, i, j);
			else if (board[i][j] == 'Q')
				result = process_queen(board, size, i, j);
			if (result == 1)
				return (1);
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc != 1)
		ft_putstr(process_figures(argv + 1, ft_strlen(argv[1]))
			== 1 ? "Success" : "Fail");
	ft_putchar('\n');
	return (0);
}