#include "shell.h"

/**
 * free_recurrent_data - free the flds needed each loop
 * @data: struct of the program's data
 * Return: Nada
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);
	
	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - free the flds needed each loop
 * @data: struct of the program's data
 * Return: Nada
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - free the flds needed for pointer
 * @array: array of pointers
 * Return: Nada
 */
void free_array_of_pointers(char **array)
{
	int i;
	
	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);
		
		free(array);
		array = NULL;
	}
}

/**
 * long_to_string - converts a number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @base: base to convert number
 *
 * Return: Nada
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};
	
	if (cociente == 0)
		string[index++] = '0';
	
	if (string[0] == '-')
		inNegative = 1;
	
	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';
	
	string[index] = '\0';
	str_reverse(string);
}

/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 * Return: int of string or nil
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}
	
	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		
		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}