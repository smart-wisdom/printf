#include "main.h"
/**
 * get_length - program that calculates the lengths to the arguments
 * @format: formatted strings that print the arguments
 * @i: arguments to be printed
 * Return: the size
 */
int get_length(const char *format, int *i)
{
	int curr_i = *i + 1;
	int length = 0;

	if (format[curr_i] == 'I')
		length = L_LONG;
	else if (format[curr_i] == 'h')
		length = L_SHORT;

	if (length == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (length);
}
