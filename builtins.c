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