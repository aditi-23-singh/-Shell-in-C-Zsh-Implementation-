#include"my_Shell.h"


//cd, cd [path], cd - (previous directory), cd ~ (home directory), cd .., handle non existing directory , permission issues
int command_cd(char** args, char* initial_directory)
{
    // if no argument is provided, change to home directory
    if(args[1]==NULL)
    {
        printf("cd: expected argument\"cd [path]\"\n"); 
    }
    else if(chdir(args[1]) == 0)
    {
        printf("CD worked!\n");

    }else{
        perror("CD");
    }   
    return 0;
}

int command_pwd()
{
    char* cwd=NULL;
   
    //Use dynamic memory allocation to get the current working directory
    cwd = getcwd(NULL, 0);
    if(cwd)
    {
        printf("%s\n",cwd);
        free(cwd);
    }else{
        perror("getcwd");
    }
    return 0;
}


// exho Hello World, exho -n Hello, echo $PATH, 
int command_echo(char** args, char** env)
{
    // echo [args]
    int newline=1; // default echo prints new line
    size_t i=1; //skipping the -n
    if(args[1]!=NULL && my_strcmp(args[1], "-n")==0)
    {
        newline=0;
        i++; // skip the -n argument
    }
    
    //process remaianing arguments
    for(;args[i];i++)
    {
        if(args[i][0]=='$') // handles environment variables
        {
            char* value=my_getenv(args[i]+1, env); // skip $ and get the variable 
            if(value){
                printf("%s",value);
            }else{
                printf(" ");
            }
        }
        else{
        printf("%s",args[i]);
        }

        if(args[i+1]!=NULL)
        {
            newline=0; 
            printf(" ");
    
        }
        if(newline)
        {
            printf("\n");
        }
        newline=1;
    }        
  
    return 0;
}

int command_env(char** env)
{
    size_t index=0;
    while(env[index])
    {
        printf("%s\n",env[index]);
        index++;
    }
    return 0;
}

int command_which(char **args, char **env)
{
    if(args[1]==NULL)
    {
        printf("which: expected argument \"which [command]\"\n");
        return 1;
    }
    char* path=my_getenv("PATH", env);
    if(path==NULL)
    {
        printf("PATH variable not found\n");
        return 0;
    }
    
    //List of the builtins
    const char* built_in_commands[8]={"cd","pwd","env","echo","setenv","unsetenv","exit",NULL};
    for(size_t i=0;built_in_commands[i];i++)
    {
        if(my_strcmp(args[1],built_in_commands[i])==0)
        {
            printf("%s: shell built in command\n",args[1]);
            return 0;
        }
    }
    // check external commands
    char* full_path= find_command_in_path(args[1],env);

    if(full_path!=NULL)
    {
        printf("%s\n",full_path);
        free(full_path);
        return 0;
    }else{
        printf("which: %s command not found\n",args[1]);
        return 1;
    }


}

// function to search for the command in PATH
char* find_command_in_path(const char* command,char**  env)
{
    char* path_env=NULL; // store the PATH environment variable
    char* path=NULL; // duplicate of PATH
    char* token=NULL; // tokenized dirs from the PATH
    char full_path[1024]; // BUFFER to construct full PATHS

    //locate the PATH
    for(size_t i=0;env[i];i++)
    {
        if(my_strncmp(env[i],"PATH=",5)==0)
        {
            path_env=env[i]+5; //skip PATH= prefix
            break;
        }
    }

    if(path_env==NULL)
    {
        return NULL; //no PATH
    }

    //Duplicate the PATH avoiding modifying the original PATHS
    path= my_strdup(path_env);
    
    if(path==NULL)
    {
        perror("my_strdup");
        return NULL;
    }
    //split PATH into individual directories using ':' delimeter
    token=my_strtok(path,":");
    while(token!=NULL)
    {
        //cosnstruct full path, check for '/'
        size_t len=my_strlen(token);
        if(token[len-1]!='/'){
        snprintf(full_path,sizeof(full_path), "%s%s%s",token,"/",command); 
        } else{
            snprintf(full_path, sizeof(full_path), "%s%s", token,command);
        }
        
        // check if the command exists as executables
        if(access(full_path,X_OK)==0)
        {
            free(path);
            return my_strdup(full_path); // found commands path
        } //mode tothe nect dir
        token=my_strtok(NULL,":");


    }


    free(path);
    
    return NULL;

}