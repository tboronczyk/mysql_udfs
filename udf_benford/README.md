# udf_benford

A MySQL UDF that calculates a digit's Benford value across a set of inputs.
See http://en.wikipedia.org/wiki/Benford%27s_law for more info regarding
Benford's Law.


    > SELECT BENFORD(columnA, 7) FROM table GROUP BY columnB;
    +---------------------+
    | BENFORD(columnA, 7) |
    +---------------------+
    |                5.76 |
    +---------------------+

Installation (Ubuntu 14.04):

    sudo apt-get install libmysqlclient-dev

    autoreconf --install
    ./configure
    make

    # SHOW GLOBAL VARIABLES LIKE 'plugin_dir' for plugin directory
    sudo cp src/.libs/udf_benford.so /usr/lib/mysql/plugin

    sudo chown root:root /usr/lib/mysql/plugin/udf_benford.so
    sudo chmod 644 /usr/lib/mysql/plugin/udf_benford.so

    # So frustrating!
    sudo aa-complain mysqld

    CREATE FUNCTION benford RETURNS REAL SONAME 'udf_benford.so';
