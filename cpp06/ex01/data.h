#ifndef DATA_H
# define DATA_H

typedef struct s_Data
{
    int value;
    struct s_Data *next;
}               Data;

#endif