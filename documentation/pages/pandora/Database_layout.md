Database layout    {#pandora_database}
===============

\tableofcontents

\section pandora_database_rake Rake tasts

In order to get a list of available Rake tasks, run

    rake -T db

from the top-directory of you \ref pandora installation.

\section pandora_database_explore Exploring the database

You can explore the contents of your database - including the various tables
contained therein - directly: after starting up the \ref mysql command line
tool via

    $ mysql -u <login> -p

you can inspect the available databases:

    mysql> SHOW DATABASES;

Depending on the population of your database the result might look something
like this:

\verbatim
  +---------------------+
  | Database            |
  +---------------------+
  | information_schema  |
  | mysql               |
  | pandora_development |
  +---------------------+
  3 rows in set (0.11 sec)
\endverbatim

  \subsection database_explore_tables List of tables

  Having identified the database used by \ref pandora, we now can obtain a listing
  of the tables contained therein:

  \verbatim
  mysql> SHOW TABLES IN `pandora_development`;
  \endverbatim

  If the database has been initialized, the output will look like this:

  \verbatim
    +-------------------------------+
    | Tables_in_pandora_development |
    +-------------------------------+
    | accounts                      |
    | accounts_groups               |
    | accounts_images               |
    | accounts_institutions         |
    | accounts_permissions          |
    | accounts_roles                |
    | announcements                 |
    | ar_mails                      |
    | bounce_emails                 |
    | brain_busters                 |
    | change_sets                   |
    | changes                       |
    | client_applications           |
    | collections                   |
    | collections_collaborators     |
    | collections_images            |
    | collections_keywords          |
    | collections_viewers           |
    | comments                      |
    | ...                           |
    +-------------------------------+
    51 rows in set (0.00 sec)
  \endverbatim

  \subsection database_explore_columns Table columns

  In order to list the columns within a given table, use the ``SHOW COLUMNS`` command:

  \verbatim
  mysql> SHOW COLUMNS IN pandora_development.accounts;
  \endverbatim

  which will list the columns:

  \verbatim
    +--------------------------------+--------------+------+-----+---------+----------------+
    | Field                          | Type         | Null | Key | Default | Extra          |
    +--------------------------------+--------------+------+-----+---------+----------------+
    | id                             | int(11)      | NO   | PRI | NULL    | auto_increment |
    | email                          | varchar(255) | YES  | MUL | NULL    |                |
    | login                          | varchar(255) | YES  | MUL | NULL    |                |
    | firstname                      | varchar(255) | YES  |     | NULL    |                |
    | lastname                       | varchar(255) | YES  |     | NULL    |                |
    | title                          | varchar(255) | YES  |     | NULL    |                |
    | addressline                    | varchar(255) | YES  |     | NULL    |                |
    | postalcode                     | varchar(255) | YES  |     | NULL    |                |
    | city                           | varchar(255) | YES  |     | NULL    |                |
    | country                        | varchar(255) | YES  |     | NULL    |                |
    | institution_id                 | int(11)      | YES  | MUL | NULL    |                |
    | crypted_password               | varchar(40)  | YES  |     | NULL    |                |
    | salt                           | varchar(40)  | YES  |     | NULL    |                |
    | created_at                     | datetime     | YES  |     | NULL    |                |
    | updated_at                     | datetime     | YES  |     | NULL    |                |
    | ...                            | ...          | ...  |     | ...     |                |
    +--------------------------------+--------------+------+-----+---------+----------------+
    37 rows in set (0.00 sec)
  \endverbatim

  If we now want to retrieve more information on the actual contents stored within
  table columns, we can do so using the \c SELECT command:

  \verbatim
  mysql> SELECT * FROM pandora_development.accounts LIMIT 0,10;
  \endverbatim

  In order to have a closer look at e.g. the information related to a specific account
  you can utilize the additional \c WHERE parameter to narrow down the displayed
  selection:

  \verbatim
  mysql> SELECT * FROM pandora_development.accounts WHERE `firstname`="<name>";
  \endverbatim
