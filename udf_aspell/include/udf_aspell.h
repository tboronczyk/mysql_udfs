#ifndef UDF_ASPELL_H
#define UDF_ASPELL_H

#include "mysql.h"

#ifndef LANGUAGE
#define LANGUAGE "en_US"
#endif

my_bool aspell_check_init(UDF_INIT *, UDF_ARGS *, char *);
void aspell_check_deinit(UDF_INIT *);
char *aspell_check(UDF_INIT *, UDF_ARGS *, char *, unsigned long *, char *, char *);

#endif
