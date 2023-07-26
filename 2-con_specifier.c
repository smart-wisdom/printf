#include "main.h"

/****** PRINT POINTER ******/

/**
 * print_pointer - program that prints value of a pointer
 * @types: list arguments
 * @buffer: buffer array to handle the print
 * @flags: calculates it active flags
 * @width: width
 * @precision: precision specification
 * @size: size of specifier
 * Return: Number of characters printed
 */
int print_pointer(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char more_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, len = 2, padd_start = 1;
	/* len = 2, for '0x' */
	unsigned long num_add;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_add = (unsigned long) addrs;

	while (num_add > 0)
	{
		buffer[ind--] = map_to[num_add % 16];
		num_add /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		more_c = '+', len++;
	else if (flags & F_SPACE)
		more_c = ' ', len++;

	ind++;

	/* return (write(1, &buffer[i], BUFF_SIZE - i - 1)); */
	return (write_pointer(buffer, ind, len, width, flags,
				padd, more_c, padd_start));
}

/****** PRINTING A NON-PRINTABLE ******/

/**
 * print_non_printable - program that prints ASCII codes in
 * hexa of non-printable characters
 * @types: list arguments
 * @buffer: buffer array to handle print
 * @flags: calculates it active flags
 * @width: width
 * @precision: precision specifier
 * @size: size of specifier
 * Return: number of characters printed
 */
int print_non_printable(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/****** PRINTING REVERSE ******/

/**
 * print_reverse - program that prints reverse string
 * @types: list arguments
 * @buffer: buffer array to handle print
 * @flags: calculates it active flags
 * @width: width
 * @precision: precision specifier
 * @size: size of specifier
 * Return: number of characters printed
 */
int print_reverse(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/****** PRINTING A STRING IN ROT13 ******/

/**
 * print_rot13 - program that print a string in rot13
 * @types: list arguments
 * @buffer: buffer arrays to handle print
 * @flags: calculates it active flags
 * @width: width
 * @precision: precision specifier
 * @size: size of specifier
 * Return: numbers of characters printed
 */
int print_rot13(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
