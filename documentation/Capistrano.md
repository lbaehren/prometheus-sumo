
Capistrano
==========

{http://www.capify.org Capistrano} is an open source tool for running scripts on multiple servers; its main use is deploying web applications. It automates the process of making a new version of an application available on one or more web servers, including supporting tasks such as changing databases.

Capistrano is written in the Ruby language and is distributed using the RubyGems distribution channel. It is an outgrowth of the {file:Rails Ruby on Rails} web application framework, but has also been used to deploy web applications written using other frameworks, including ones written in PHP.

Capistrano is implemented primarily for use on the bash command line. Users of the Ruby on Rails framework may choose from many Capistrano recipes, e.g. to deploy current changes to the web application or roll back to the previous deployment state.

Originally called SwitchTower, the name was changed to Capistrano in March 2006 because of a trademark conflict.

Capistrano is a utility and framework for executing commands in parallel on multiple remote machines, via SSH. It uses a simple Domain Specific Language borrowed in part from the tool rake. Rake is similar to make in the C world and allows you to define tasks, which may be applied to machines in certain roles. It also supports tunneling connections via some gateway machine to allow operations to be performed behind VPNs and firewalls.

Capistrano was originally designed to simplify and automate deployment of web applications to distributed environments, and originally came bundled with a set of tasks designed for deploying Rails applications. The deployment tasks are now (as of Capistrano 2.0) opt-in and require clients to explicitly put "load 'deploy'" in their recipes.

## Installation

{http://www.capify.org Capistrano} is actually comprised of the Capistrano gem itself, and

    $ gem sources -a http://gems.github.com/
    $ gem -v

Your RubyGems should be at least 1.3.x, if not please follow their upgrade
instructions and come back here... with RubyGems up to date, you can install
Capistrano and its dependencies with the following:

    $ gem install capistrano

## Assumptions

{http://www.capify.org Capistrano} makes a few assumptions about your servers. In order to use Capistrano, you will need to comply with these assumptions:

- You are using SSH to access your remote machines. Telnet and FTP are not supported.
- Your remote servers have a POSIX-compatible shell installed. The shell must be called “sh” and must reside in the default system path.
- If you are using passwords to access your servers, they must all have the same password. Because this is not generally a good idea, the preferred way of accessing your servers is with a public key. Make sure you’ve got a good passphrase on your key.

Capistrano also makes a few assumptions about your own familiarity with computers: You should be comfortable working from a command-line. You do not need to know advanced shell scripting techniques or anything like that (though it helps, if you want to start writing complex Capistrano recipes), but you should be able to navigate directories and execute commands from the command-line. Capistrano has no GUI interface; it is entirely command-line driven.

To take full advantage of Capistrano, you should be comfortable (or at least, minimally familiar) with the Ruby programming language. When you write your own Capistrano tasks, you do so in Ruby.

## Capfile

{http://www.capify.org Capistrano} reads its instructions from a ``capfile``. (For those of you familiar with the ``make`` or ``rake`` utilities, the concept is the same as a ``makefile`` or ``rakefile``.) If you create a file called ``capfile`` (or ``Capfile``, if you prefer), Capistrano will read that file and process the instructions in it.

The Capfile is where you will tell Capistrano about the servers you want to connect to and the tasks you want to perform on those servers. It is essentially just a Ruby script, but augmented with a large set of “helper” syntax, to make it easy to define server roles and tasks. (Using the lingo of those in the know, the Capfile is written using a custom DSL on top of Ruby.)

You can use any editor you want to write your Capfiles; they are just simple text files. I recommend something designed for programmers, like _vim_, _emacs_, {http://macromates.com TextMate}, {http://www.eclipse.org Eclipse}, and so forth. Choose whatever you’re comfortable with, but make sure whatever you choose can save files as plain text, and will not automatically append a extension like ``.txt`` to the filename. The Capfile should be called ``capfile`` or ``Capfile``, without any extension.

Note: As capistrano is helpful, it will search up your file tree until it finds a capfile, this is intended to insure if you are anywhere within your application, and you try and run cap, it will find the correct ``capfile``; this has been known to catch people out though; your home directory is also searched.

## References 

- {http://capify.stikipad.com/wiki Capistrano Wiki}
- {http://wiki.rubyonrails.org/rails/pages/Capistrano Capistrano in Ruby on Rails} (rubyonrails.org)
- {http://manuals.rubyonrails.com/read/book/17 Capistrano: Automating Application Deployment}
- {http://prometheus.khi.uni-koeln.de/ruby-doc/capistrano-2.0.0 Capistrano API Documentation} (via prometheus.khi.uni-koeln)
- {http://en.wikipedia.org/wiki/Capistrano Wikipedia entry}
- {http://deprec.org Deployment recipes for Capistrano} (deprec.org)
