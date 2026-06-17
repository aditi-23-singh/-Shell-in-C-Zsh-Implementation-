#include<stdio.h>
#include"my_Shell.h"

// shell loop 
//input parsing 
//command execution exp. cd,pwd, echo, setenv, unsetenv, exit, which
// execute external commands
// manage environment variables
// manage path
// error handling


//Built-ins: echo, cd, pwd, env, unsetenv,setenv, exit,which,
// Binary ls,cat,..
int shell_builts(char **args, char **env, char *initial_directory)
{
    
    if (my_strcmp(args[0], "cd")==0)
    {
        return command_cd(args, initial_directory);
    }
    else if (my_strcmp(args[0], "pwd")==0)
    {
        return command_pwd();
    }
    else if (my_strcmp(args[0], "echo")==0)
    {
        return command_echo(args, env);
    }
    else if (my_strcmp(args[0], "env")==0)
    {
        return command_env(env);
    }
    else if (my_strcmp(args[0], "which")==0)
    {
        return command_which(args, env);
    }
    else if (my_strcmp(args[0], "exit")==0 || (my_strcmp(args[0], "quit")==0))
    {
        printf("I am exiting\n");
        exit(EXIT_SUCCESS);
    }else{
        //not a built in command, execute as external command

        return executor(args,env);
    }
   
}


void shell_loop(char** env)
{
    char* input=NULL;
    size_t input_size=0;
    char** args;

    char* initial_directory=getcwd(NULL,0);
    while(1)
    {
        printf("[my_shell]>");
        if(getline(&input, &input_size, stdin)==-1) //end of the file(EOP), ctrl+ D
        {
            perror("getline");
            break;
        }
        input[strcspn(input, "\n")] = '\0';

        //printf("Input: %s",input);

        args=parse_input(input);

        // for(size_t i=0;args[i];i++)
        // {
        //     printf("Args: %s\n",args[i]);
        
        // }
        if(!args[0])
        {
            return;
        }
        else if(my_strcmp(args[0],"setenv")==0){
            env=command_setenv(args,env);
        }
        else if (my_strcmp(args[0], "unsetenv") == 0){
            env=command_unsetenv(args,env);
        }else
        shell_builts(args,env,initial_directory);        

    }

    free_tokens(args);
    free(env);
}
int main(int argc,char** argv, char** env)
{
    (void)argc;
    (void)argv;
    shell_loop(env);
    
}