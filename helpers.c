#include "my_Shell.h"

// 0: the strings are equal
// <0: str1 < str2
// >0: str > str2
int my_strcmp(const char* str1, const char* str2)
{

    while(*str1 && (*str1==*str2))
    {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

int my_strlen(const char* str)
{
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
