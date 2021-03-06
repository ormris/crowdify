#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../disk-read-ng/configsql.h"


char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = (char**) malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int main(int argc, char *argv[]){
	char* add_dirs_string = argv[1];
	char* userName = argv[2];
	char* addr = argv[3];
	char** dirs;
	
	dirs = str_split(add_dirs_string, ',');

    if (dirs)
    {
		ClientConfig* cc = new ClientConfig(addr, userName);
        int i;
        for (i = 0; *(dirs + i); i++)
        {
			cc->insertDirectory(*(dirs + i));
            free(*(dirs + i));
        }
        free(dirs);
    }
}