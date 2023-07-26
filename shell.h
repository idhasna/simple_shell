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
 * @sttr: The string .
 * @_next: It points to the next node .
 */

typedef struct listr
{
	int numb;
	char *sttr;
	struct listr *_next;
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
int _isdelime(char, char *);
int is_alpha(int);
int _myatoi(char *);
int _isinteractive(info_t *);

/* help.c */
int change_cd(info_t *);
int get_help(info_t *);
int exit_sh(info_t *);

/* setalias.c */
int m_alias(info_t *);
int _dishistory(info_t *);

/* setenv.c */
int mod_setenv(info_t *);
int rmv_unsetenv(info_t *);
int print_env(info_t *);
char *get_env(info_t *, const char *);
int pop_envlist(info_t *);

/* err.c */
int _myputfd(char charc, int file_des);
int _myputsfd(char *sttr, int file_des);
int _myputchar(char);
void _myputs(char *);

/* err1.c */
void rmv_comments(char *);
void _printerr(info_t *, char *);
char *conv_number(long int, int, int);
int err_atoi(char *);
int write_dec(int, int);

/* strings.c */
char *str_cnct(char *, char *, int);
char *str_cpy(char *, char *, int);
char *str_ch(char *, char);

/* getinput.c */
int get_line(info_t *, char **, size_t *);
ssize_t _getinput(info_t *);
void _siginthandler(int);

/* getenviron.c */
int unset_env(info_t *, char *);
char **get_env_cpy(info_t *);
int set_env(info_t *, char *, char *);

/* setinfo.c */
void _setinfo(info_t *, char **);
void _clearinfo(info_t *);
void _freeinfo(info_t *, int);

/* gethistory.c */
int list_history(info_t *info, char *buf, int linecount);
int print_history(info_t *info);
int _renumbhistory(info_t *info);
int _readhistory(info_t *info);
char *_gethistory(info_t *info);

/* nodes.c */
int _deletenode(list_t **, unsigned int);
list_t *_addnodeend(list_t **, const char *, int);
void list_free(list_t **);
list_t *_addnode(list_t **, const char *, int);
size_t write_sttr_list(const list_t *);

/* Lists.c */
list_t *prefix_node(list_t *, char *, char);
char **conve_list_str(list_t *);
ssize_t node_index(list_t *, list_t *);
size_t length_list(const list_t *);
size_t write_list(const list_t *);

/* Memory.c */
int free_pntr(void **);

/* path.c */
char *_dupcharacter(char *, int, int);
int execut_comnd(info_t *, char *);
char *_findpath(info_t *, char *, char *);

/* setmemory.c */
void str_free(char **);
char *fill_mem(char *, char, unsigned int);
void *_memrealloc(void *, unsigned int, unsigned int);

/* loopsh.c */
int shell_loop(char **);

/* sttr.c */
char *begins_with(const char *, const char *);
int length_str(char *);
char *cnct_str(char *, char *);
int comp_str(char *, char *);

/* str.c */
void _myputs(char *);
char *copy_str(char *, char *);
int _myputchar(char);
char *dup_str(const char *);

/* Token.c */
char **split_str1(char *, char);
char **split_str(char *, char *);

/* alias.c */
int rep_vars(info_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);
int rep_str(char **, char *);
int _ischain(info_t *, char *, size_t *);
int rep_als(info_t *);

/**
 * struct passinfo - Got pseudoarguements which are going to get a function,
 * to allow for a single prototype of the function pointer struct .
 * @f_path: The string path for the existing command .
 * @f_name: The file name of the program .
 * @argv: A set of strings derived from arguments .
 * @_environ: A custom modified copy of the environ .
 * @arg: A string generated with arguments contained in the getline .
 * @_flinecount: Counting this line of input .
 * @_history: The node of the history .
 * @env: A local copy of environ listed in a linked list .
 * @als: The node of the alias .
 * @change_env: The environ changes .
 * @hist_count: The number of history line numbers .
 * @_errnum: The error code for exit .
 * @fd_read: The field from which input lines are read .
 * @argc: The argument count .
 * @_linecount: The error count .
 * @_status: The status of the returned last executed command .
 * @comd_buff_t: The command type .
 * @comand_buf: The address of the command buffer .
 */

typedef struct passinfo
{
	char **comd_buff
	char *f_path;
	char *f_name;
	char **argv;
	char **_environ;
	char *arg;
	unsigned int _linecount;
	list_t *_history;
	list_t *env;
	list_t *als;
	int change_env;
	int hist_count;
	int _errnum;
	int fd_read;
	int argc;
	int comd_buff_t;
	int _flinecount;
	int _status;
} info_t;

#define HIST_FILE "simple_shell_history"
#define HIST_MAX 4096

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

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
