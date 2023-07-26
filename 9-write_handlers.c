#include "main.h"

/****** WRITE HANDLERS ******/
/**
 * handle_write_char - program that prints a string
 * @c: characters types
 * @buffer: buffer array to handle print
 * @flags: calculates it active flags
 * @width: width
 * @precision: precision specifier
 * @size: Size of specifier
 * Return: Number of characters printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* character is stored at left and paddind at buffers right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/****** WRITE NUMBER ******/
/**
 * write_number - program that Prints a string
 * @negative: arguments lists
 * @ind: types of characters
 * @buffer: buffer array to handle print
 * @flags: calculates its active flags
 * @width: width
 * @precision: precision specifier
 * @size: Size of specifier
 * Return: Number of characters printed
 */
int write_number(int negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		len, padd, extra_ch));
}
/**
 * write_num - program that Writes a number using a bufffer
 * @ind: Index number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @precision: Precision specifier
 * @length: Number of length
 * @padd: Padding character
 * @more_c: more characters
 * Return: Number of printed characters
 */
int write_num(int ind, char buffer[], int flags, int width, int precision,
	int length, char padd, char more_c)
{
	int i, padd_start = 1;

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0'
			&& width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
		buffer[--ind] = '0', length++;
	if (more_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign more char to left of buffer */
		{
			if (more_c)
				buffer[--ind] = more_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* more char to left of buffer */
		{
			if (more_c)
				buffer[--ind] = more_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* more char to left of padd */
		{
			if (more_c)
				buffer[--padd_start] = more_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (more_c)
		buffer[--ind] = more_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - program that writes an unsigned number
 * @negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of characters
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size of specifier
 * Return: Number of written characters
 */
int write_unsgnd(int negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffers right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0) no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Assign more char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Assign more char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - program that Write a memory address
 * @buffer: Arrays of characters
 * @ind: Index number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Characters representing the padding
 * @more_c: Characters representing more char
 * @padd_start: Index at which padding should start
 * Return: Number of written characters
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char more_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Assign more char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (more_c)
				buffer[--ind] = more_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* more char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (more_c)
				buffer[--ind] = more_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* more char to left of padd */
		{
			if (more_c)
				buffer[--padd_start] = more_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (more_c)
		buffer[--ind] = more_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
