
Ruby on Rails    {#rails}
=============

\tableofcontents

\section rails_overview Overview

**Ruby on Rails**, often shortened to Rails or RoR, is a web application development framework written in the Ruby language. It is designed to make programming web applications easier by making assumptions about what every developer needs to get started. It allows you to write less code while accomplishing more than many other languages and frameworks. Experienced Rails developers also report that it makes web application development more fun.

Rails is opinionated software. It makes the assumption that there is a “best” way to do things, and it’s designed to encourage that way – and in some cases to discourage alternatives. If you learn “The Rails Way” you’ll probably discover a tremendous increase in productivity. If you persist in bringing old habits from other languages to your Rails development, and trying to use patterns you learned elsewhere, you may have a less happy experience.

The Rails philosophy includes several guiding principles:

* DRY – “Don’t Repeat Yourself” – suggests that writing the same code over and over again is a bad thing.
* Convention Over Configuration – means that Rails makes assumptions about what you want to do and how you’re going to do it, rather than requiring you to specify every little thing through endless configuration files.
* REST (Representational state transfer) is the best pattern for web applications – organizing your application around resources and standard HTTP verbs is the fastest way to go.

\section rails_mvc Model-View-Controller (MVC) pattern

Understanding the [MVC pattern](http://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller) is key to understanding Rails. MVC divides your application into three layers, each with a specific responsibility.

The View layer is composed of “templates” that are responsible for providing appropriate representations of your application’s resources. Templates can come in a variety of formats, but most view templates are HTML with embedded Ruby code (.erb files).

The Model layer represents your domain model (such as Account, Product, Person, Post) and encapsulates the business logic that is specific to your application. In Rails, database-backed model classes are derived from ActiveRecord::Base. Active Record allows you to present the data from database rows as objects and embellish these data objects with business logic methods. Although most Rails models are backed by a database, models can also be ordinary Ruby classes, or Ruby classes that implement a set of interfaces as provided by the ActiveModel module. You can read more about Active Record in its [README](http://api.rubyonrails.org/files/activerecord/README_rdoc.html).

The Controller layer is responsible for handling incoming HTTP requests and providing a suitable response. Usually this means returning HTML, but Rails controllers can also generate XML, JSON, PDFs, mobile-specific views, and more. Controllers manipulate models and render view templates in order to generate the appropriate HTTP response.

In Rails, the Controller and View layers are handled together by Action Pack. These two layers are bundled in a single package due to their heavy interdependence. This is unlike the relationship between Active Record and Action Pack which are independent. Each of these packages can be used independently outside of Rails. You can read more about Action Pack in its [README](http://api.rubyonrails.org/files/actionpack/README_rdoc.html).

\section rails_website Creating a new website

Rails provides a simple mechanism to start developing a new website from scratch

\code
rails new <path>
\endcode

where ``path`` is the (absoluet) path to the root directory of the new Rails
application.

The most common rails commands are:

| Command   | Description |
|-----------|-------------|
| \b generate | Generate new code (short-cut alias: "g") |
| \b console | Start the Rails console (short-cut alias: "c") |
| \b server | Start the Rails server (short-cut alias: "s") |
| \b dbconsole | Start a console for the database specified in \c config/database.yml (short-cut alias: "db") |
| \b new | Create a new Rails application. "rails new my_app" creates a new application called MyApp in "./my_app" |

In addition to those, there are:

| Command   | Description |
|-----------|-------------|
| \b application | Generate the Rails application code |
| \b destroy     | Undo code generated with "generate" (short-cut alias: "d") |
| \b benchmarker | See how fast a piece of code runs |
| \b profiler    | Get profile information from a piece of code |
| \b plugin      | Install a plugin |
| \b runner      | Run a piece of code in the application environment (short-cut alias: "r") |

\subsection rails_website_structure Directory structure

The basic (directory-) structure set up by Rails will look something like this:

\verbatim
  .
  |-- app
  |   |-- assets
  |   |   |-- images
  |   |   |-- javascripts
  |   |   `-- stylesheets
  |   |-- controllers
  |   |-- helpers
  |   |-- mailers
  |   |-- models
  |   `-- views
  |       `-- layouts
  |-- config
  |   |-- environments
  |   |-- initializers
  |   `-- locales
  |-- db
  |-- doc
  |-- lib
  |   |-- assets
  |   `-- tasks
  |-- log
  |-- public
  |-- script
  |-- test
  |   |-- fixtures
  |   |-- functional
  |   |-- integration
  |   |-- performance
  |   `-- unit
  |-- tmp
  |   `-- cache
  |       `-- assets
  `-- vendor
      |-- assets
      |   |-- javascripts
      |   `-- stylesheets
      `-- plugins
\endverbatim

\subsection rails_website_rake Rake tasks

Along with the directory structure, also an initial setup for Rake will be
configured; a newly created application will support the following tasks:

    rake about              # List versions of all Rails frameworks and the environment
    rake assets:clean       # Remove compiled assets
    rake assets:precompile  # Compile all the assets named in config.assets.precompile
    rake db:create          # Create the database from config/database.yml for the current
                            # Rails.env (use db:create:all to create all dbs in the config)
    rake db:drop            # Drops the database for the current Rails.env (use db:drop:all
                            # to drop all databases)
    rake db:fixtures:load   # Load fixtures into the current environment's database.
    rake db:migrate         # Migrate the database (options: VERSION=x, VERBOSE=false).
    rake db:migrate:status  # Display status of migrations
    rake db:rollback        # Rolls the schema back to the previous version (specify steps
                            # w/ STEP=n).
    rake db:schema:dump     # Create a db/schema.rb file that can be portably used against
                            # any DB supported by AR
    rake db:schema:load     # Load a schema.rb file into the database
    rake db:seed            # Load the seed data from db/seeds.rb
    rake db:setup           # Create the database, load the schema, and initialize with the
                            # seed data (use db:reset to also drop the db first)
    rake db:structure:dump  # Dump the database structure to db/structure.sql. Specify
                            # another file with DB_STRUCTURE=db/my_structure.sql
    rake db:version         # Retrieves the current schema version number
    rake doc:app            # Generate docs for the app -- also available doc:rails,
                            # doc:guides, doc:plugins (options: TEMPLATE=/rdoc-template.rb,
                            # TITLE="Custom Title")
    rake log:clear          # Truncates all *.log files in log/ to zero bytes
    rake middleware         # Prints out your Rack middleware stack
    rake notes              # Enumerate all annotations (use notes:optimize, :fixme, :todo
                            # for focus)
    rake notes:custom       # Enumerate a custom annotation, specify with ANNOTATION=CUSTOM
    rake rails:template     # Applies the template supplied by LOCATION=(/path/to/template)
                            # or URL
    rake rails:update       # Update configs and some other initially generated files (or
                            # use just update:configs, update:scripts, or update:application_controller)
    rake routes             # Print out all defined routes in match order, with names.
    rake secret             # Generate a cryptographically secure secret key (this is typically used to
                            # generate a secret for cookie sessions).
    rake stats              # Report code statistics (KLOCs, etc) from the application
    rake test               # Runs test:units, test:functionals, test:integration together (also
                            # available: test:benchmark, test:profile, test:plugins)
    rake test:recent        # Run tests for recenttest:prepare / Test recent changes
    rake test:single        # Run tests for singletest:prepare
    rake test:uncommitted   # Run tests for uncommittedtest:prepare / Test changes since last
                            # checkin (only Subversion and Git)
    rake time:zones:all     # Displays all time zones, also available: time:zones:us,
                            # time:zones:local -- filter with OFFSET parameter, e.g., OFFSET=-6
    rake tmp:clear          # Clear session, cache, and socket files from tmp/ (narrow w/
                            # tmp:sessions:clear, tmp:cache:clear, tmp:sockets:clear)
    rake tmp:create         # Creates tmp directories for sessions, cache, sockets, and pids

  \subsection rails_website_model Creating a new model

Using the ``create`` command it is possible to create the necessary files for a
new _model_, _view_ or _controller_:

\code
$ rails generate model Book
\endcode

The output from that task reports the files created on disk:

\verbatim
  invoke  active_record
  create    db/migrate/20120426064746_create_book.rb
  create    app/models/book.rb
  invoke    test_unit
  create      test/unit/book_test.rb
  create      test/fixtures/book.yml
\endverbatim

The class responsible for implementing the new model at this point is populated
with the bare minimum of code:

\code{.rb}
class Book < ActiveRecord::Base
  # attr_accessible :title, :body
end
\endcode

\subsection rails_website_testing Testing the application

Rails, via Rake, has the build-in capability to generate statistics concerning
the test coverage: run
\verbatim
rake stats
\endverbatim
in order to get a table with the lines of code:
\verbatim
+----------------------+-------+-------+---------+---------+-----+-------+
| Name                 | Lines |   LOC | Classes | Methods | M/C | LOC/M |
+----------------------+-------+-------+---------+---------+-----+-------+
| Controllers          |  6156 |  3683 |      23 |     279 |  12 |    11 |
| Helpers              |  2064 |   852 |       0 |     132 |   0 |     4 |
| Models               | 16476 |  9111 |     195 |    1884 |   9 |     2 |
| Libraries            | 12482 |  5711 |      57 |     664 |  11 |     6 |
| Model specs          |  3204 |  2294 |       0 |       4 |   0 |   571 |
| View specs           |     0 |     0 |       0 |       0 |   0 |     0 |
| Controller specs     |  2216 |  1541 |       1 |      44 |  44 |    33 |
| Helper specs         |     0 |     0 |       0 |       0 |   0 |     0 |
| Library specs        |     0 |     0 |       0 |       0 |   0 |     0 |
+----------------------+-------+-------+---------+---------+-----+-------+
| Total                | 42598 | 23192 |     276 |    3007 |  10 |     5 |
+----------------------+-------+-------+---------+---------+-----+-------+
  Code LOC: 19357     Test LOC: 3835     Code to Test Ratio: 1:0.2
\endverbatim

\section rails_references References

* [Ruby on Rails](http://rubyonrails.org) open-source web framework
* Release notes: [2.2](http://guides.rubyonrails.org/2_2_release_notes.html) | [2.3](http://guides.rubyonrails.org/2_3_release_notes.html) | [3.0](http://guides.rubyonrails.org/3_0_release_notes.html) | [3.1](http://guides.rubyonrails.org/3_1_release_notes.html) | [3.2](http://guides.rubyonrails.org/3_2_release_notes.html)
* [Ruby on Rails Tutorial](http://ruby.railstutorial.org/ruby-on-rails-tutorial-book)
* [Getting Started with Rails](http://guides.rubyonrails.org/getting_started.html)
* [Ruby on Rails 3.0 und 3.1](http://www.ruby-auf-schienen.de/buch/index.html)
* [A Guide to Testing Rails Applications](http://guides.rubyonrails.org/testing.html])
* [Rails Application Visualizer](http://rav.rubyforge.org)
* [Inspecting a live Ruby process](http://weblog.jamisbuck.org/2006/9/22/inspecting-a-live-ruby-process)
* [Inspecting a live Ruby process, easier if you cheat](http://eigenclass.org/hiki/ruby+live+process+introspection)
