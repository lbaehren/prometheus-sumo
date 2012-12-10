Ruby Version Manager (RVM)    {#rvm}
==========================

\tableofcontents

[RVM](https://rvm.io) is a command-line tool which allows you to easily install, manage, and work with multiple ruby environments from interpreters to sets of gems.

\section rvm_install Installation

Install RVM with ruby:

\verbatim
\curl -L https://get.rvm.io | bash -s stable --ruby
\endverbatim

Additionally with rails:

\verbatim
\curl -L https://get.rvm.io | bash -s stable --rails
\endverbatim

Or with rubinius, rails and puma:

\verbatim
\curl -L https://get.rvm.io | bash -s stable --ruby=rbx --gems=rails,puma
\endverbatim

Finally, to install without the "rubygems-bundler" or "rvm" gems:

\verbatim
\curl -L https://get.rvm.io | bash -s stable --without-gems="rvm rubygems-bundler"
\endverbatim

Point to be noted is, there is a backslash before curl. This prevents misbehaving if you have aliased it with configuration in your ~/.curlrc file. 

\section rvm_references References

* [Project website](https://rvm.io)
