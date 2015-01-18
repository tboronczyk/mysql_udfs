#include <stdlib.h>
#include <string.h>
#include "mysql.h"

typedef struct s_benford_data benford_data;

my_bool benford_init(UDF_INIT *, UDF_ARGS *, char *);
void benford_deinit(UDF_INIT *);
void benford_clear(UDF_INIT *, UDF_ARGS *, char *, char *);
void benford_add(UDF_INIT *, UDF_ARGS *, char *, char *);
double benford(UDF_INIT *, UDF_ARGS *, char *, char *, char *);

struct s_benford_data
{
    int seen;  /* count of times the digit is seen */
    int rows;  /* the number of rows processed */
};

my_bool benford_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
    if (args->arg_count != 2) {
        strcpy(message, "function expects two arguments.");
        return 1;
    }
    /* coerse arguments - first arg to string will allow us to accept INT, 
       DOUBLE, and REAL values (and also easier to extract most-significant
       digit), the second arg must be INT to compare */
    args->arg_type[0] = STRING_RESULT;
    args->arg_type[1] = INT_RESULT;

    benford_data *data = (benford_data *)malloc(sizeof(benford_data));
    if (!data) {
        strcpy(message, "Couldn't allocate memory");
        return 1;
    }
    data->seen = 0;
    data->rows = 0;
    initid->ptr = (char *)data;

    /* function will return 2 decimal places */
    initid->decimals = 2;

    return 0;
}

void benford_deinit(UDF_INIT *initid)
{
    free(initid->ptr);
}

void benford_clear(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
    benford_data *data = (benford_data *)initid->ptr;
    data->seen = 0;
    data->rows = 0;
}

void benford_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
    benford_data *data = (benford_data *)initid->ptr;
    data->rows++;

    if (args->args[0] && args->args[1]) {
        /* extract the leading digit */
        char *str = args->args[0];
        int i = str[0] - '0';

        int j = *((int *)args->args[1]);
        if (i && i == j) {
            data->seen++;
        }
    }
}

double benford(UDF_INIT *initid, UDF_ARGS *args, char* result, char *is_null, char *error)
{
    benford_data *data = (benford_data *)initid->ptr;
    if (data->rows) { /* no divide by zero! */
        return data->seen / (double)data->rows;
    }
    return 0.0;
}
