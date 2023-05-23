#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_PATH_LENGTH 100
#define MAX_EXECUTABLE_LENGTH 100
/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;



/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for the function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on, count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @environ: custom modified copy of environ from LL env
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
} info_t;

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Macro definitions */

/* for read/write buffers */
#define READ_BUF_SIZE 1024 /*Size of read buffer*/
#define WRITE_BUF_SIZE 1024 /*Size of write buffer*/
#define BUF_FLUSH -1 /* Buffer flush constant */

/* for command chaining */
#define CMD_NORM 0 /* Normal command chaining type */
#define CMD_OR 1 /* Command chaining with "||" type */
#define CMD_AND 2 /* Command chaining with "&&" type */
#define CMD_CHAIN 3/*General command chaining type  */

/* for convert_number() */
#define CONVERT_LOWERCASE 1 /* Flag for converting to lowercase */
#define CONVERT_UNSIGNED 2 /* Flag for converting to unsigned */
/* 1 if using system getline() */
#define USE_GETLINE 0 /*Flag for using system getline() function  */
#define USE_STRTOK 0 /* Flag for using strtok() function */

#define HIST_FILE ".simple_shell_history" /*  Shell history file name */
#define HIST_MAX 4096 /* Maximum history size */

/* shloop.c */
int hsh(info_t *info, char **args);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);


int shell_loop(void);
void handle_signal(int signum);
char *parse_command(char *input);
char *find_executable(char *command);
int execute_command(char *command);
void display_error(char *message);




/* parser.c */
int is_cmd(info_t *info, char *cmd);
char *dup_chars(char *str, int start, int end);
char *find_path(info_t *info, char *cmd, char *dir);

/* loophsh.c */
int loophsh(char **args);

/* getline.c */
ssize_t get_input(info_t *info);
int _getline(info_t *info, char **line, size_t *line_len);
void sigintHandler(int sig);

/* getinfo.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **args);
void free_info(info_t *info, int free_args);

#endif /* _SHELL_H_ */
