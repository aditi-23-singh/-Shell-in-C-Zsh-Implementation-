#ifndef MY_SHELL_H
#define MY_SHELL_H 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stddef.h>
#include<string.h>


#define MAX_INPUT 1024
#define MAX_PATH 256

char** parse_input(char* input);
void free_tokens(char **tokens);
int shell_builts(char **args, char **env, char *initial_directory);

//built_in function implementations
int command_cd(char** args, char* initial_directory);
int command_pwd();
int command_echo(char** args, char** env);
int command_env(char** env);
int command_which(char **args, char **env);

char** command_setenv(char** args, char** env);
char** command_unsetenv(char** args, char** env);
int my_strcmp(const char *s1,const char *s2);
char *my_getenv(const char *name, char **env);
int my_strlen(const char *str);
#endif




