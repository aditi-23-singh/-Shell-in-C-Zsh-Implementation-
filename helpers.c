#include "my_Shell.h"

// 0: the strings are equal
// <0: str1 < str2
// >0: str > str2
int my_strcmp(const char* str1, const char* str2)
{

    if(str1==NULL || str2==NULL)
        return 1;
    while(*str1 && (*str1==*str2))
    {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

//length of the string 
int my_strlen(const char* str)
{
            if(str==NULL)
                return -1;
    size_t len=0;
    while(*str)
    {
        len++;
        str++;
    }
    return len;
}


//0: strings are equal to n characters
// <0: str1<str2
// >0: str1>str2
int my_strncmp(const char* str1,const char* str2,size_t n)
{

    if(str1==NULL || str2==NULL)
            return 1;
    size_t i=0;
    while(i<n &&str1[i] &&str2[i])
    {
        if(str1[i]!=str2[i])
        {
            return (unsigned char)str1[i]-(unsigned char)str2[i]; // return the difference of the first non matching characters
        }
        i++;
    }

    if(i==n)
    {
        return 0; //success
    }
    return (unsigned char)str1[i]-(unsigned char)str2[i]; // if one string is shorter than the other
}

// search the environement variables for the speicified name and return 
char* my_getenv(const char* name, char** env)
{
    if(name==NULL || env == NULL)
    {
        return NULL;
    }
    size_t name_len=my_strlen(name);

    for(size_t i=0;env[i];i++)
    {
        // check if the curr env variables starts with 'name='
        if(my_strncmp(env[i],name,name_len)==0 && env[i][name_len]=='=')
        {
            return &env[i][name_len+1]; // return the value part after 'name='
        }

    }
    return NULL;

}

// copies the content of the source into the destination string
char* my_strcpy(char* dest, const char* src)
{
    if(src==NULL)
        return NULL;
    char* ret=dest;
        while(*src)
        {
            *dest=*src;
            dest++;
            src++;
        }
        *dest='\0';
        return ret;
}

// create a duplicate of the input string by allocating new memory
char * my_strdup(const char* str)
{
    if(str==NULL)
    {
        return NULL;
    }
    size_t len=my_strlen(str);
    char * duplicated=(char *)malloc((len+1) * sizeof(char));
    if(!duplicated)
    {
        return NULL;
    }
    my_strcpy(duplicated,str);
    return duplicated;

}


// locates the first occurrence of a character in a string 
char* my_strchr(const char* str, char c)
{
    while(*str)
    {
        if(*str==c){
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

// tokenizes a string by splitting it based on aset of deliemter characters
char* my_strtok(char* input_string, const char* delimeter)
{
    static char* next_token=NULL;
    // if input in NULL
    if(input_string==NULL)
    {
        input_string=next_token;
    }
    if(input_string==NULL)
        return NULL;
    
        while(*input_string && my_strchr(delimeter,*input_string))
        {
            input_string++;
        }
        if(*input_string =='\0')
        {
            next_token=NULL;
            return NULL;
        }
        char* token=input_string;
        while(*input_string && !my_strchr(delimeter,*input_string))
        {
            input_string++;
        }
        if(*input_string)
        {
            *input_string='\0';
            next_token=input_string+1;

        }else{
            next_token=NULL;
        }
        return token;

} 


// copies upto n characters from the source string to the destination string, ensuring null-termination
char* my_strncpy(char* dest, const char* src, size_t n)
{
    size_t i;
    for(i=0;i<n && src[i]!='\0';i++)
    {
        dest[i]=src[i];

    }
    for(;i<n;i++)
    {
        dest[i]='\0';
    }
    return dest;
}
