#include "include/config.h"

#include <stdlib.h>
#include <string.h>

config_file config_open(const char *path)
{
    config_file res = {.path = path};

    res.file = fopen(path, "r");
    if (res.file == NULL)
    {
        printf("%s: %s not found\n", __FUNCTION__, path);
        exit(1);
    }

    return res;
}

void config_close(config_file config)
{
    fclose(config.file);
}

char *config_read_string(config_file config, char const *key)
{
    char name[128];
    char val[128];

    while (fscanf(config.file, "%127[^=]=%127[^\n]%*c", name, val) == 2)
    {
        if (0 == strcmp(name, key))
        {
            return strdup(val);
        }
    }
    return NULL;
}

int config_read_int(config_file config, char const *key)
{
    // read key as string
    char *temp = config_read_string(config, key);
    if (!temp)
        return __INT_MAX__;

    // parse string & ensure entire value is parsed; eg fail on 1234abcd
    int ret;
    char *stop;
    ret = strtol(temp, &stop, 10);
    free(temp);

    return stop == temp ? __INT_MAX__ : ret;
}