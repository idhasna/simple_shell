#include "shell.h"

/**
 * conv_number - The converter function, a clone of integer to ASCII .
 * @base: The base of the number system .
 * @numb: The number to be converted .
 * @flg: The flags of arguments .
 * Return: Return to the string .
 */
char *conv_number(long int numb, int base, int flg)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pntr;
	unsigned long nb = numb;

	if (!(flg & CONVERT_UNSIGNED) && numb < 0)
	{
		nb = -numb;
		sign = '-';

	}
	array = flg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pntr = &buffer[49];
	*pntr = '\0';

	do	{
		*--pntr = array[nb % base];
		nb /= base;
	} while (nb != 0);

	if (sign)
		*--pntr = sign;
	return (pntr);
}

/**
 * _printerr - Writes the error message .
 * @err_sttr: The string that contains the specified error type .
 * @info: The return information structure and the parameter .
 * Return: Nothing .
 */

void _printerr(info_t *info, char *err_sttr)
{
	my_eputs(info->f_name);
	my_eputs(": ");
	write_dec(info->_linecount, STDERR_FILENO);
	my_eputs(": ");
	my_eputs(info->argv[0]);
	my_eputs(": ");
	my_eputs(err_sttr);
}

/**
 * rmv_comment - A function that change the first instance of '#' by '\0' .
 * @buff: The address of the string to modify .
 * Return: All the times 0 .
 */

void rmv_comment(char *buff)
{
	int index;

	for (index = 0; buff[index] != '\0'; index++)
		if (buff[index] == '#' && (!index || buff[index - 1] == ' '))
		{
			buff[index] = '\0';
			break;
		}
}

/**
 * err_atoi - The string is converted to an integer .
 * @sttr: The string to convert .
 * Return:  0 if there are no numbers in the string, -1 on error .
 */

int err_atoi(char *sttr)
{
	int index = 0;
	unsigned long int output = 0;

	if (*sttr == '+')
		sttr++;  /* TODO: why it's this making the main return 255? */
	for (index = 0;  sttr[index] != '\0'; index++)
	{
		if (sttr[index] >= '0' && sttr[index] <= '9')
		{
			output *= 10;
			output += (sttr[index] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * write_dec - A function that prints a decimal number .
 * @number: The number to print .
 * @file_des: The file descriptor to use for writing .
 * Return: To the number of printed characters .
 */

int write_dec(int number, int file_des)
{
	int (*__putchar)(char) = _myputchar;
	int index, count = 0;
	unsigned int abs_value, latest;

	if (file_des == STDERR_FILENO)
		__putchar = my_eputchar;
	if (number < 0)
	{
		abs_value = -number;
		__putchar('-');
		count++;
	}
	else
		abs_value = number;
	latest = abs_value;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (abs_value / index)
		{
			__putchar('0' + latest / index);
			count++;
		}
		latest %= index;
	}
	__putchar('0' + latest);
	count++;

	return (count);
}
