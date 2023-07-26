#include "main.h"

/****** PRINT CONVERSION SPECIFIER u ******/

/**
 * print_unsigned - program that prints an unsigned number
 * @types: arguments lists
 * @buffer: buffer arrays to handle print
 * @flags: calculates its active flags
 * @width: width
 * @precision: specify precision
 * @size: size of specifier
 * Return: number of characters printed
 */
int print_unsigned(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/****** PRINT CONVERSION SPECIFIER o ******/

/**
 * print_octal - program that prints an unsigned number in octal
 * @types: arguments lists
 * @buffer: buffer arrays to handle print
 * @flags: calculates its active flags
 * @width: width
 * @precision: specify precision
 * @size: size of specifier
 * Return: number of characters printed
 */
int print_octal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/****** PRINT CONVERSION SPECIFIER x ******/

/**
 * print_hexadecimal - program that prints an unsigned number in hexadecimal
 * @types: arguments lists
 * @buffer: buffer arrays to handle print
 * @flags: calculates its active flags
 * @width: width
 * @precision: specify precision
 * @size: size of specifier
 * Return: number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer, flags, 'x',
				width, precision, size));
}

/****** PRINT UNSIGNED NUMBER IN UPPER HEXA ******/

/**
 * print_hexa_upper - program that prints an unsigned num in upper hexa
 * @types: arguments lists
 * @buffer: buffer arrays to handle print
 * @flags: calculates its active flags
 * @width: width
 * @precision: specify precision
 * @size: size of specifier
 * Return: number of characters printed
 */
int print_hexa_upper(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer, flags, 'X',
				width, precision, size));
}

/****** PRINT HEXA NUMBER IN LOWER OR UPPER ******/

/**
 * print_hexa - program that hexadecimal number in upper or lower
 * @types: arguments lists
 * @map_to: array values to map the numbers to
 * @buffer: buffer arrays to handle print
 * @flags: calculates its active flags
 * @flag_ch: calculates it active flags
 * @width: width
 * @precision: specify precision
 * @size: size of specifier
 * Return: number of characters printed
 */
int print_hexa(va_list types, char map_to[],  char buffer[], int flags,
		char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
