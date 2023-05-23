#include "shell.h"



/**
 * shell_loop - Starts the main loop of the shell
 *
 * Description: This function displays a prompt, reads user input,
 * parses commands, finds executables, and executes them.
 *
 * Return: The exit status of the shell.
 */
int shell_loop(void)
{
	char input[MAX_INPUT_LENGTH];
	int exit_status = 0;

	while (1)
	{
		printf(">> ");  /* Display the prompt */
		fgets(input, sizeof(input), stdin);  /* Read user input */
		/* Remove the trailing newline character */
		input[strcspn(input, "\n")] = '\0';

		/* Handle end of file condition (Ctrl+D) */
		if (feof(stdin))
		{
			printf("\n");
			break;
		}
		/* Execute the command */
		if (strlen(input) > 0)
		{
			char *command = parse_command(input);
			char *executable = find_executable(command);

			if (executable != NULL)
			{
				int execution_status = execute_command(executable);

				if (execution_status != 0)
					display_error("Command execution failed");
			}
			else
			{
				display_error("Command not found");
			}
			free(command);
			free(executable);
		}
	}
	return (exit_status);
}


/**
 * handle_signal - Handles the signal interrupt (Ctrl+C)
 * @signum: The signal number
 *
 * Description: This function handles the signal interrupt (SIGINT)
 * and performs the necessary actions when the signal is received.
 */
void handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		printf("\nCtrl+C (SIGINT) received. Exiting...\n");
		exit(0);
	}
}


/**
 * parse_command - Parses the command from the user input
 * @input: The input string
 *
 * Description: This function takes the user input and extracts
 * the first word (command) from it.
 *
 * Return: A dynamically allocated string containing the command.
 */
char *parse_command(char *input)
{
	int result;
	char *command;

	/* Allocate memory for the command string */
	command = (char *)malloc(strlen(input) + 1);

	if (command == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	/* Copy the first word (command) from the input */
	result = sscanf(input, "%s", command);

	if (result != 1)
	{
		fprintf(stderr, "Error parsing command\n");
		free(command);
		return (NULL);
	}

	return (command);
}

