#include"my_shell.h"

char** parse_input(char* input)
{
    size_t buffer_size=MAX_INPUT;
    char** tokens=malloc(buffer_size * sizeof(char*));
    char* token=NULL;
    size_t position=0;
    size_t token_length=0;
    if(!tokens)
    {
        perror("Malloc");
        exit(EXIT_FAILURE);
    }

    for(size_t i=0;i<input[i];i++)
    {
        token=&input[i];
        while(input[i] && input[i]!=' ')
        {
            token_length++;
            i++;
        }
        tokens[position]=malloc((token_length+1)*sizeof(char));  
        if(!tokens[position])
        {
            perror("Malloc");
            exit(EXIT_FAILURE);
        }  
        for(size_t j=0;j<token_length;j++)
        {
            tokens[position][j]=token[j];
        }
        tokens[position][token_length]='\0'; //null terminate token
        position++;
        token_length=0; // reset for next token
        


    }
    tokens[position]=NULL; //terminate the array with null
    return tokens;
}

// free allocated tokens
void free_tokens(char** tokens)
{
    if(tokens)
    {
        return;
    }
    for(size_t i=0;tokens[i];i++)
    {
        free(tokens[i]); // free each token 
    }
    free(tokens); // free the tokens array
}