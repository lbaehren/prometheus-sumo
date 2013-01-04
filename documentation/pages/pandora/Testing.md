
Testing    {#pandora_testing}
=======

\tableofcontents

\section pandora_testing_intro Introduction

Testing support was woven into the \ref rails "Rails" fabric from the
beginning. It wasn’t an “oh! let’s bolt on support for running tests because
they're new and cool” epiphany. Just about every Rails application interacts
heavily with a database - and, as a result, your tests will need a database to
interact with as well. To write efficient tests, you’ll need to understand how
to set up this database and populate it with sample data.

\subsection pandora_testing_env Environments

Every Rails application you build has 3 sides: a side for production, a side for
development, and a side for testing.

One place you’ll find this distinction is in the `config/database.yml` file. This
\ref yaml configuration file has 3 different sections defining 3 unique database setups:

* production
* development
* test

This allows you to set up and interact with test data without any danger of your tests altering data from your production environment.

For example, suppose you need to test your new `delete_this_user_and_every_everything_associated_with_it` function. Wouldn’t you want to run this in an environment where it makes no difference if you destroy data or not?

When you do end up destroying your testing database (and it will happen, trust
me), you can rebuild it from scratch according to the specs defined in the
development database. You can do this by running

~~~~
rake db:test:prepare
~~~~

\subsection pandora_testing_frameworks Framworks

* MiniTest
* TestUnit
* \ref rspec

Comparison of the output/source code of two functionally equivalent unit tests, one written using RSpec and the other using Test::Unit

* Code under test
\code{.rb}
class DeadError < StandardError; end

class Dog
  def bark
    raise DeadError.new "Can't bark when dead" if @dead
    "woof"
  end

  def die
    @dead = true
  end
end
\endcode
* Test::Unit
\code{.rb}
 require 'test/unit'
  require 'dog'

  class DogTest < Test::Unit::TestCase
    def setup
      @dog = Dog.new
    end

    def test_barks
      assert_equal "woof", @dog.bark    
    end

    def test_doesnt_bark_when_dead
      @dog.die
      assert_raises DeadError do
        @dog.bark
      end
    end
  end
\endcode
* RSpec
\code{.rb}
require 'rspec'
require 'dog'

describe Dog do
  before(:all) do
    @dog = Dog.new
  end

  context "when alive" do
    it "barks" do
      @dog.bark.should == "woof"
    end
  end

  context "when dead" do
    before do
      @dog.die
    end

    it "raises an error when asked to bark" do
      lambda { @dog.bark }.should raise_error(DeadError)
    end
  end
end
\endcode
* Test::Unit output
~~~~
Ξ code/examples → ruby dog_test.rb --verbose
Loaded suite dog_test
Started
test_barks(DogTest): .
test_doesnt_bark_when_dead(DogTest): .

Finished in 0.004937 seconds.
~~~~
* RSpec output (documentation formatter)
~~~~
Ξ code/examples → rspec -fd dog_spec.rb 

Dog
  when alive
    barks
  when dead
    raises an error when asked to bark

Finished in 0.00224 seconds
2 examples, 0 failures

2 tests, 2 assertions, 0 failures, 0 errors
~~~~

\section pandora_testing_specification Test specifications

Tests are defined in the ``spec`` sub-directory:

    ./pandora
      └── spec
          ├── controllers
          ├── fixtures
          ├── helpers
          ├── lib
          ├── models
          ├── shared
          └── views

\section pandora_testing_run Running the tests

In order to get a list of all available tests, use the command

    rake -T spec

The resulting list should contain entries like this:

\verbatim
  rake spec                         Run all specs in spec directory (excluding plugin specs)
  rake spec:clobber_rcov            Remove rcov products for rcov
  rake spec:controllers             Run the code examples in spec/controllers
  rake spec:db:fixtures:load        Load fixtures (from spec/fixtures) into the current environment's database.
  rake spec:doc                     Print Specdoc for all specs (excluding plugin specs)
  rake spec:helpers                 Run the code examples in spec/helpers
  rake spec:lib                     Run the code examples in spec/lib
  rake spec:models                  Run the code examples in spec/models
  rake spec:plugin_doc              Print Specdoc for all plugin examples
  rake spec:plugins                 Run the code examples in vendor/plugins (except RSpec's own)
  rake spec:plugins:rspec_on_rails  Runs the examples for rspec_on_rails
  rake spec:rcov                    Run all specs in spec directory with RCov (excluding plugin specs)
  rake spec:server:restart          reload spec_server.
  rake spec:server:start            start spec_server.
  rake spec:server:stop             stop spec_server.
  rake spec:views                   Run the code examples in spec/views
\endverbatim

Since essentially the specs are groups into Rake tasks, running them is as
simple as e.g.

    rake spec:models

If however you want a bit more control over the test carried out, you e.g. can
utilize the ``SPEC`` option to pass along an individual file with test instructions:

    rake spec SPEC=spec/models/image_spec.rb

Using ``SPEC_OPTS`` it is possible to pass along options e.g. to influence the
formatting of the output.

    rake spec SPEC=spec/controllers/institution_controller_spec.rb SPEC_OPTS="--format nested --color"

  which will result in something like this (color missing here though):

  \verbatim
    InstitutionController
      in general
        should redirect to login if user is not logged in
        should redirect to email confirmation if user's email is not already confirmed
        should redirect to license if the current user's license is expired
      handling GET /institution/index
        should redirect to /institution/list if user is allowed
        should redirect to /institution/show if user is not allowed to see the list
      handling GET /institution/show
        should not show the given institution if current user is not allowed (FAILED - 1)
        when allowed
          should successfully render the template
          should show the current user's institution
          should show the given institution
  \endverbatim

\section pandora_testing_references References

* [A Guide to Testing Rails Applications](http://guides.rubyonrails.org/testing.html)
* [How to Run a Single Rails Unit Test](http://flavio.castelli.name/2010/05/28/rails_execute_single_test)
* [Testing in Rails](http://www.nullislove.com/2007/11/10/testing-in-rails-introduction) -- Series of posts about how to get started writing tests for Ruby on Rails
* [RSpec vs Test::Unit in Rails](http://programmers.stackexchange.com/questions/27328/rspec-vs-testunit-in-rails)