# udf_aspell

A MySQL UDF that wraps Aspell to provide basic spell-check functionality.

    > SELECT aspell_check("Hello");
    +-----------------------+
    | aspell_check("Hello") |
    +-----------------------+
    | Hello                 |
    +-----------------------+

    > SELECT aspell_check("dlvjeqbf");
    +--------------------------+
    | aspell_check("dlvjeqbf") |
    +--------------------------+
    | NULL                     |
    +--------------------------+

Installation (Ubuntu 14.04):

    sudo apt-get install libmysqlclient-dev libaspell-dev

    cd udf_aspell/src
    gcc -fPIC -shared -o udf_aspell.so -DLANGUAGE=\"$LANG\" -I../include \
      udf_aspell.c -laspell $(mysql_config --cflags) $(mysql_config --libs)

    # SHOW GLOBAL VARIABLES LIKE 'plugin_dir' for plugin directory
    sudo cp udf_aspell.so /usr/lib/mysql/plugin

    sudo chown root:root /usr/lib/mysql/plugin/udf_aspell.so
    sudo chmod 644 /usr/lib/mysql/plugin/udf_aspell.so

    # So frustrating!
    sudo aa-complain mysqld

    CREATE FUNCTION aspell_check RETURNS STRING SONAME 'udf_aspell.so';
