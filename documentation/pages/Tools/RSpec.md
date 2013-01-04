RSpec    {#rspec}
=====

\tableofcontents

The RSpec tool is a Ruby package that lets you build a specification alongside your software. This specification is actually a test that describes the behavior of your system. Here's the flow for development with RSpec:

* You write a test. This test describes the behavior of a small element of your system.
* You run the test. The test fails because you have not yet built the code for that part of your system. This important step tests your test case, verifying that your test case fails when it should.
* You write enough code to make the test pass.
* You run the tests and verify that they pass.

In essence, an RSpec developer turns test cases from red (failing) to green (passing) all day. It's a motivating process.

\section rspec_install Installation

RSpec is available as a gem, which makes installation as simple as

    gem install rspec

\subsection rspec_install_rails2 ... with Rails 2.x

    gem install rspec-rails -v 1.3.3

Bootstrap the application:

    ./script/generate rspec
        create  spec
        create  spec/spec_helper.rb
        create  spec/spec.opts
        create  previous_failures.txt
        create  script/spec_server
        create  script/spec

\subsection rspec_install_rails3 ... with Rails 3.x

Configure the Gemfile:

    group :development, :test do
      gem "rspec-rails", "~> 2.0"
    end

Install the bundle:

    bundle install

Bootstrap the application:

    ./script/rails generate rspec:install
          create  .rspec
          create  spec
          create  spec/spec_helper.rb
          create  autotest
          create  autotest/discover.rb

\section rspec_usage Usage

\subsection rspec_usage_rails2 ... with Rails 2.x

    ./script/generate rspec_model User
    rake -T spec # lists all rspec rake tasks
    rake spec # run all specs
    rake spec SPEC=spec/models/mymodel_spec.rb SPEC_OPTS="-e \"should do something\"" #run a single spec

\subsection rspec_usage_rails3 ... with Rails 3.x

    ./rails/generate model User
    rake -T spec # lists all rspec rake tasks
    rake spec # run all specs
    rake spec/models/mymodel_spec.rb # run a single spec file
    rake spec/models/mymodel_spec.rb:27 # run a single example or group on line 27

\section rspec_matchers Matchers

  * `obj.should be_true`, `obj.should be_false`, `obj.should be_nil`, obj.should be_empty – the first three of these could be done by == true, etc. be_empty will be true if `obj.empty?` is true.
  * `obj.should exist` – does this object even exist yet?
  * `obj.should have_at_most(n).items`, `object.should have_at_least(n).items` – like have, but will pass if there are more or fewer than n items, respectively.
  * `obj.should include(a[,b,...])` – are one or more items in an array?
  * `obj.should match(string_or_regex)` – does the object match the string or regex?
  * `obj.should raise_exception(error)` – does this method raise an error when called?
  * `obj.should respond_to(method_name)` – does this object have this method? Can take more than one method name, in either strings or symbols.

\section rspec_output Output formats

\verbatim
  -f, --format FORMATTER           Choose a formatter.
                                     [p]rogress (default - dots)
                                     [d]ocumentation (group and example names)
                                     [h]tml
                                     [t]extmate
                                     custom formatter class name
  -o, --out FILE                   Write output to a file instead of STDOUT. This option applies
                                     to the previously specified --format, or the default format
                                     if no format is specified.
  -b, --backtrace                  Enable full backtrace.
  -c, --[no-]color, --[no-]colour  Enable color in the output.
  -p, --profile                    Enable profiling of examples and list 10 slowest examples.
\endverbatim

You can change the output of your specs by placing flags in a `spec/spec.opts`
file in your rails app.

\verbatim
--colour
--format progress
--format specdoc:spec/spec_full_report.txt
--format failing_examples:spec/spec_failing_examples.txt
--format html:spec/spec_report.html
--loadby mtime
--reverse
\endverbatim

\section rspec_ref References

* [Behavior-driven testing with RSpec](http://www.ibm.com/developerworks/web/library/wa-rspec)
* [RSpec Best Practices](http://www.methodsandtools.com/tools/tools.php?rspec)
* [An Introduction To RSpec](http://blog.teamtreehouse.com/an-introduction-to-rspec)
* [An introduction to RSpec - Part I](http://blog.davidchelimsky.net/2007/05/14/an-introduction-to-rspec-part-i)
* [RSpec cheat-sheet](http://cheat.errtheblog.com/s/rspec)