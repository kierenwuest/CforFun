#include <unistd.h>
#include <stdio.h>

int main(void)
{
	
	int		hr, min, sec, mil, val, c;
	
	//Validated inputs
	//scanf using %d will return 1 if input is a valid %d else will return 0 
	//getchar() function in the loop until '\n' or end-of-file (EOF)

	val = 0;

	while (val != 1) 
	{
		printf("Timer Hours: ");
		val = scanf("%d", &hr);
		if (val != 1) 
		{
			printf("\033[2J\033[H");	
			printf("\033[31mError: Please enter numbers.\033[0m\n");
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}

	val = 0;

	while (val != 1) 
	{
		printf("Timer Minutes: ");
		val = scanf("%d", &min);
		if (val != 1) 
		{
			printf("\033[2J\033[H");	
			printf("\033[31mError: Please enter numbers.\033[0m\n");
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}

	//convert mins
	if (min > 60)
	{
		hr += min/60;
		min %= 60;
	}

	val = 0;

	while (val != 1) 
	{
		printf("Timer Seconds: ");
		val = scanf("%d", &sec);
		if (val != 1) 
		{
			printf("\033[2J\033[H");	
			printf("\033[31mError: Please enter numbers.\033[0m\n");
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}	

	//convert secs
	if (sec > 60)
	{
		min += sec/60;
		if (min > 60)
		{	
			hr += min/60;
			min %= 60;
		}
		sec %= 60;
	}

	//clear screen and move cursor with ANSI
	printf("\033[2J\033[H");	

	if (min < 10 && sec < 10)
		printf("\033[31mTIMER SET: %d:0%d:0%d:0000\033[0m \n", hr, min, sec);
	else if (min < 10)
		printf("\033[31mTIMER SET: %d:0%d:%d:0000\033[0m \n", hr, min, sec);
	else if (sec < 10)
		printf("\033[31mTIMER SET: %d:%d:0%d:0000\033[0m \n", hr, min, sec);
	else
		printf("\033[31mTIMER SET: %d:%d:%d:0000\033[0m \n", hr, min, sec);

	//Countdown loop
	mil = 1000;

	while (hr != 0 || min != 0 || sec != 0)
	{
		if (mil == 0)
		{
			sec--;
			if(!(hr == 0 && min == 0 && sec == 0))
				mil = 1000;
		}
		if (sec < 0)
		{
			min--;
			sec = 59;
		}
		if (min < 0)
		{
			hr--;
			min = 59;
		}
		
		if (min < 10 && sec < 10)
			printf("\r\033[32mT - MINUS: %d:0%d:0%d:%d\033[0m", hr, min, sec, mil);
		else if (min < 10)
			printf("\r\033[32mT - MINUS: %d:0%d:%d:%d\033[0m", hr, min, sec, mil);
		else if (sec < 10)
			printf("\r\033[32mT - MINUS: %d:%d:0%d:%d\033[0m", hr, min, sec, mil);
		else
			printf("\r\033[32mT - MINUS: %d:%d:%d:%d\033[0m", hr, min, sec, mil);
		fflush(stdout);
		usleep(1000);
		mil--;
	}

	//Give a result message
	printf("\n\033[31mTime's up!\033[0m\n");

	//Use  ASCII bell character to do a beep sound
	for (int i = 0; i < 10; i++) 
	{
		printf("\a");
		fflush(stdout);
		usleep(500000);
	}

	return (0);
}
