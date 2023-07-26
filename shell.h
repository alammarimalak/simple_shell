#ifndef SHEL_LIB_H
#define SHEL_LIB_H
#define EXIT_SUCCESS 0
#define SHELL_HEADER "Shell@"
#define SEQ_START_BYTE ('\x1b')
#define INTRPT -20
#define ENV_MAX 255

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

typedef enum state_action_e
{
	INIT,
	GET,
	INC,
	SET
} state_action_t;
/**
 * struct map_t - struct
 * @keys: key
 * @values: value
 * @all: all
 * @size: size
 * @cap: cap
*/
typedef struct map_t
{
	char **keys;
	char **values;
	char **all;
	int size;
	int cap;
} map_t;
/**
 * enum env_action_t - enum
 * @PRINT_ENV: print env
 * @INIT_ENV: init
 * @SET_ENTRY: set
 * @GET_VALUE: set
 * @GET_KEYS: set
 * @GET_MAP: comment
 * @DELETE_ENTRY: comment
 * @CLEAR_ENV: comment
*/
typedef enum env_action_t
{
	PRINT_ENV,
	INIT_ENV,
	SET_ENTRY,
	GET_VALUE,
	GET_KEYS,
	GET_MAP,
	DELETE_ENTRY,
	CLEAR_ENV
} env_action_t;
/**
 * enum path_action_t - enum
 * @PRINT_PATH: cmnt
 * @INIT_PATH: cmnt
 * @FIND_CMD: cmnt
 * @CLEAR_PATH: cmnt
*/
typedef enum path_action_t
{
	PRINT_PATH,
	INIT_PATH,
	FIND_CMD,
	CLEAR_PATH
} path_action_t;

int   _putchar(char c);
int   _getline(char **buff, size_t *size, int fd);
void  prompt_user(void);
void  free_2d(char **Array);
void  free_n2d(char **Array, int n);
void  print_2d(char **Array);
void  terminate_incoming_str(char *s, int *size);
int   trim(char **s);
char **split_by_delim(const char *buffer, const char *delim);
char  **parse_command(char *buff);
char  *_getpath();
char  **get_tokenized_path();
int   _exec(char **argv, char *uinput);
void  increment_it(void);
void  deinit_env_map(void);
char  *_get_env(const char *key);
void  _set_env(const char *key, const char *value);
char *get_value(const map_t *m, const char *key);
void set_value(map_t *m, const char *key, const char *value);
void  print_env(void);
void print_env_internal(map_t *m);
map_t *get_envp_map(void);
void  loginfo(const char *s);
map_t *create_map(size_t size);
void  distroy_map(map_t *m);
void  append_entry(map_t *m,
const char *entry, const char *key, const char *value);
void  map_cpy(map_t *m, char **src);
void find_cmd(char **cmd_loc, char **paths, int *result_);

void path_manager(path_action_t action, char **cmd_loc, int *res);
void *env_manager(env_action_t action, const char *key, const char *value);

void init_path_manager(void);
void  release_path(void);
void  print_path(void);
void resolve_command_path(char **old_path, int *res);
int state_manager(state_action_t a);
int signal_manager(state_action_t a);
int match_char(char c, char *buff, int *idx);
#endif
