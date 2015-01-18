#include <string.h>
#include "aspell.h"
#include "mysql.h"

#ifndef LANGUAGE
#define LANGUAGE "en_US"
#endif

my_bool aspell_check_init(UDF_INIT *, UDF_ARGS *, char *);
void aspell_check_deinit(UDF_INIT *);
char *aspell_check(UDF_INIT *, UDF_ARGS *, char *, unsigned long *, char *, char *);

my_bool aspell_check_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
    if (args->arg_count != 1) { 
        strcpy(message, "function expects one argument.");
        return 1;
    }
    if (args->arg_type[0] != STRING_RESULT) {
        strcpy(message, "y u spellcheck not string?");
        return 1;
    }

    /* configure Aspell */
    AspellConfig *config = new_aspell_config();
    aspell_config_replace(config, "lang", LANGUAGE);
    AspellCanHaveError * speller = new_aspell_speller(config);
    delete_aspell_config(config);

    if (aspell_error_number(speller)) {
        strcpy(message, aspell_error_message(speller));
        return 1;
    }
    initid->ptr = (char *)to_aspell_speller(speller);

    return 0;
}

void aspell_check_deinit(UDF_INIT *initid)
{
    if (initid->ptr) {
       delete_aspell_speller((AspellSpeller *)initid->ptr);
    }
}

char* aspell_check(UDF_INIT *initid, UDF_ARGS *args, char* result, unsigned long* length, char *is_null, char *error)
{
    *is_null = 1;
    char *str = args->args[0];
    int len = args->lengths[0];

    if (str && len) {
        if (aspell_speller_check((AspellSpeller *)initid->ptr, str, len)) {
            *is_null = 0;
            strcpy(result, str);
            *length = len;
        }
    }

    return result;
}
