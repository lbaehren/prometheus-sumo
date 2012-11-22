Bundler    {#bundler}
=======

\tableofcontents

\section bundler_about About

Bundler is a tool that maintains a consistent environment for a developer’s code
across all machines. When a developer’s code is run on different machines, the
libraries the developer originally built their code on may change. This breaks
the developer’s application. Bundler ensures that the libraries will remain the
same, taping everything together so that the developer’s application runs smoothly
on every machine where it is deployed.

When you run `gem bundle`, a few things happen. First, the bundler attempts to
resolve your list of dependencies against the gems you have already bundled. If
they don’t resolve, the metadata for each specified source is fetched and the
gems are downloaded. Next (either way), the bundler checks to see whether the
downloaded gems are expanded. For any gem that is not yet expanded, the bundler
expands it. Finally, the bundler creates the `environment.rb` file with the new
settings. This means that running gem bundler over and over again will be
extremely fast, because after the first time, all gems are downloaded and
expanded. If you change settings, like `disable_rubygems`, running `gem bundle`
again will simply regenerate the `environment.rb`.

\section bundler_install Installation

Bundler is pure Ruby with few dependencies. It's installed using a typical gem install command.

~~~~
gem install bundler
~~~~

\section bundler_references References

* [Bundler project website](http://gembundler.com)
* [Creating and Distributing Gems with Bundler](http://ruby.about.com/od/advancedruby/ss/Creating-And-Distributing-Gems-With-Bundler.htm)
* [Using the New Gem Bundler Today](http://yehudakatz.com/2009/11/03/using-the-new-gem-bundler-today)
