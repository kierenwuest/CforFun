#include <stdio.h>
#include <unistd.h>

// Char and ANSI code functions
void printChar(char c)
{
	write(1, &c, 1);
}

//delete Char
void del(void)
{
	write(1, "\033[D", 3);
}

//delete line and reset cursor
void deLine(void)
{
	write(1, "\033[D\033[G", 6);
}

//print red character
void rChar(char c)
{
	write(1, "\033[31m", 5);
	write(1, &c, 1);
	write(1, "\033[0m", 4);
}

//print green character
void gChar(char c)
{
	write(1, "\033[32m", 5);
	write(1, &c, 1);
	write(1, "\033[0m", 4);
}

//print yellow character
void yChar(char c)
{
	write(1, "\033[33m", 5);
	write(1, &c, 1);
	write(1, "\033[0m", 4);
}

// Helper function that checks if the number is sorted
int	isSort(char *str)
{
	int	i = 0;
	
	//opposite of the sort condition until the end null char
	while (str[i] && (str[i] >= str[i + 1]))
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

// Compare adjacent elements in the array and swap (less than) based on ascii value
char	*sortNums(char *str, int isSorted)
{
	int		i = 0;
	int		s = isSorted;
	char		swp;
	
	while (str[i])
	{	
		if (str[i] < str[i + 1])
		{
			rChar(str[i + 1]);
			usleep(10000);
			swp = str[i];
			yChar(swp);
			usleep(150000);
			del();
			str[i] = str[i + 1];
			str[i + 1] = swp;
		}
		else
		{
			usleep(30000);
			gChar(str[i]);
		}
		i++;
	}
	usleep(100000);
	deLine();
	//printf("\n");

	// check if string is sorted and flag
	s = isSort(str);	
	
	//if flag is not sorted (0), then do recursion
	if (s == 0)
		sortNums(str, 0);
	return (str);
}

// Appropiately take a string of numbers in a char array
int	main(int argc, char **argv)
{
	int std = 0;
	
	// check for correct arguments
	if (argc != 2) 
	{
		printf("Usage: %s <string>\n", argv[0]);
		return 1;
	}
	
	//check and flag if number is sorted
	std = isSort(argv[1]);
	
	//show input and output values
	printf("\033[2J\033[H"); //ANSI codes to clear terminal
	printf("Input : %s \n", argv[1]);
	printf("\033[2K\rOutput: \033[32m%s \n", sortNums(argv[1], std));

	return(0);
}
