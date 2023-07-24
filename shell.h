#ifndef _SHELL_H_
#define _SHELL_H_


#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

/**
 * struct listr - A singly linked list .
 * @numb: The field of the number .
 * @str: The string .
 * @next: It points to the next node .
 */

typedef struct listr
{
	int numb;
	char *str;
	struct listr *next;
} listr_t;

/**
 * struct builtin - It contains the builtin string and a related function .
 * @fnc: The function points to the builtin commands .
 * @name: The builtin command's name .
 */

typedef struct builtin
{
	char *name;
	int (*fnc)(info_t *);
} builtin_t;

/* interactive.c */
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);

/* help.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

/* setalias.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* setenv.c */
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _myenv(info_t *);
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);

/* err.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _putchar(char);
void _puts(char *);

/* err1.c */
void remove_comments(char *);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);
int _erratoi(char *);
int print_d(int, int);

/* strings.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* getinput.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/* _getenv.c */
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);

/* setinfo.c */
void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);

/* _history.c */
int build_history_list(info_t *info, char *buf, int linecount);
int write_history(info_t *info);
int renumber_history(info_t *info);
int read_history(info_t *info);
char *get_history_file(info_t *info);

/* _node.c */
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node_end(list_t **, const char *, int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
size_t print_list_str(const list_t *);

/* _lists.c */
list_t *node_starts_with(list_t *, char *, char);
char **list_to_strings(list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
size_t print_list(const list_t *);

/* _memory.c */
int bfree(void **);

/* path.c */
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);

/* setmemory.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* _loop.c */
int loophsh(char **);

/* _string.c */
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);

/* str.c */
void _puts(char *);
char *_strcpy(char *, char *);
int _putchar(char);
char *_strdup(const char *);

/* _token.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* alias.c */
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);

/**
 * struct passinfo - Got pseudoarguements which are going to get a function,
 * to allow for a single prototype of the function pointer struct .
 * @path: The string path for the existing command .
 * @fname: The file name of the program .
 * @argv: A set of strings derived from arguments .
 * @environ: A custom modified copy of the environ .
 * @arg: A string generated with arguments contained in the getline .
 * @line_count: Counting this line of input .
 * @history: The node of the history .
 * @env: A local copy of environ listed in a linked list .
 * @alias: The node of the alias .
 * @env_changed: The environ changes .
 * @histcount: The number of history line numbers .
 * @err_num: The error code for exit .
 * @readfd: The field from which input lines are read .
 */

typedef struct passinfo
{
	char **cmd_buf
	char *path;
	char *fname;
	char **argv;
	char **environ;
	char *arg;
	unsigned int line_count;
	list_t *history;
	list_t *env;
	list_t *alias;
	int env_changed;
	int histcount;
	int err_num;
	int readfd;
	int argc;
	int cmd_buf_type;
	int linecount_flag;
	int status;
} info_t;

#define HIST_FILE "simple_shell_history"
#define HIST_MAX 4096

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/* Total environemnt */
extern char **environ;

/* Chaining command */
#define CMD_AND	2
#define CMD_NORM 0
#define CMD_CHAIN 3
#define CMD_OR 1

/* Using geline system */
#define USE_STRTOK 0
#define USE_GETLINE 0

/* Write and read buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Converting numbers */
#define CONVERT_UNSIGNED 2
#define CONVERT_LOWERCASE 1

#endif
