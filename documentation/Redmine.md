
# Redmine

## Installation

### Requirements

#### Operating system

Redmine should run on most Unix, Linux, {http://www.redmine.org/projects/redmine/wiki/RedmineInstallOSX Mac}, Mac Server and Windows systems as long as Ruby is available on this platform. See specific installation HowTos {http://www.redmine.org/projects/redmine/wiki/HowTos here}.

#### Database

* {file:MySQL} 5.0 or higher (recommended)
  * make sure to install the C bindings for Ruby that dramatically improve performance. You can get them by running gem install mysql2. If you have problem installing the mysql gem refer Rails Wiki pages

* PostgreSQL 8 or higher
  * make sure your database datestyle is set to ISO (Postgresql default setting). You can set it using: ``ALTER DATABASE "redmine_db" SET datestyle="ISO,MDY";``
  * some bugs in PostgreSQL 8.4.0 and 8.4.1 affect Redmine behavior (#4259, #4314), they are fixed in PostgreSQL 8.4.2

* SQLite 3

#### Redmine Version

It is recommended that the majority of users install the proper point releases of
redmine. Redmine currently releases a new version every 6 months, and these
releases are considered very usable and stable. It is not recommended to install
redmine from trunk, unless you are deeply familiar with {file:Rails Ruby on Rails}
and keep up with the changes - Trunk does break from time-to-time.

### ... on Mac OS X


## References

* {http://www.redmine.org redmine.org} - Project homepage
* {http://www.redmine.org/projects/redmine/wiki/RedmineInstall Installing Redmine}
