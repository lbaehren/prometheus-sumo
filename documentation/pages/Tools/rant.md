Rant    {#rant}
====

\tableofcontents

Rant is a flexible build tool written entirely in Ruby.

The equivalent to a _Makefile_ for _make_ is the _Rantfile_. A _Rantfile_ is
actually a valid Ruby script that is read in by the `rant` command.

Rant currently features:

* Rantfiles are written in Ruby.
* Defining custom tasks
* Automated packaging, testing and RDoc generation for Ruby applications and libraries.
* The `rant-import` command creates a monolithic rant script, so you don’t depend on an rant installation anymore.
* Creating gzipped tar and zip archives — without installing additional software.
* Optional recognition of file changes based on MD5 checksums instead of file modification times.
* Tasks with command change recognition.
* Dependency checking for C/C++ source files.
* Compiling of C# sources and resources

\section rant_usage The rant program

For a short usage message and a list of options invoke rant with the —help option:

\verbatim
% rant --help
\endverbatim

Usually you’ll run rant by giving it the name of the task(s) to be invoked as argument(s). To get an overview for the project in the current working directory, run rant with the —tasks (short form: -T) option:

~~~~
% rant -T
rant               # => test
rant package       # Create packages for distribution.
rant doc           # Generate documentation.
rant test          # Run unit tests.
rant cov           # Run all tests and generate coverage with rcov.
rant clean         # Remove autogenerated files.
rant publish-docs  # Publish html docs on RubyForge.
                   #   Note: scp will prompt for rubyforge password.
~~~~

This lists the "public" tasks for the project. The first line always tells you the task(s) that will be invoked when no argument is given to rant, in the above example, this would be the test task.

When you invoke rant on the commandline it performs the following steps (roughly):

* Process commandline options and arguments. An option starts with two dashes or one for the single letter equivalent. Arguments of the form VAR=VAL set variables available in the Rantfile(s). All other arguments are names of tasks to be invoked.
* Load Rantfile in working directory. Rantfiles with the following names are recognized:
~~~~
Rantfile
rantfile
root.rant
~~~~
* Calculate task dependencies and invoke required tasks. If no task was given on the commandline, a task called "default" will be invoked. If the "default" task doesn’t exist, the first task will be invoked.

\section rant_rantfile How to write an Rantfile

As already mentioned, an Rantfile is a Ruby script. Additionally, Rant provides
methods and classes which aid you in automating your work.

Centric to the processing done by Rant is the task. The Rantfile defines tasks
and their dependencies, Rant invokes the required tasks.

Also important is the Rant application. When the rant command starts, it
instantiates one Rant application which will read one or more Rantfiles. The
Rantfile communicates with the following list of methods with the Rant
application:

| Method  | Description |
|---------|-------------|
| task    | Defines a task with prerequisites and an action. |
| file    | A special form of task which creates one file.   |
| desc    | Describes the next defined task. A task with description is considered a "public" task. |
| gen     | Takes a generator object as first argument which usually creates one or more tasks. An example would be the RubyPackage generator which produces tasks for packaging. |
| import  | Imports additional code which usually provides additional generators. Example: to use the RubyPackage generator you have to import "rubypackage" first. |
| sys     | Run external commands or do usual file system operations (copy files, unlink files, install, …). |
| source  | Takes a filename as argument and causes Rant to read it in as Rantfile. |
| subdirs | Takes a list of subdirectories in which Rant should look for Rantfiles. |
| var     | Provides access to variables accessible in Rantfiles and from the commandline. |
| make    | Immediately build a target. |

\subsection rant_rantfile_task Defining a task

Just call the task function and give it a task name as argument. The task name may be a string or symbol:

    task :taskname

That’s it, your first task. Not very useful, because it doesn’t do anything. To associate an action with the task, add a block:

    task :mytask do
        puts "Hello, mytask running."
    end

Put these 3 lines of code into a file called Rantfile and run rant:

    % rant mytask
    Hello, mytask running.

Note: you could have omited the mytask argument to rant because it is the only task in the Rantfile.

You can add a block parameter which will be a reference to the created task:

    task :mytask do |t|
        puts t.name
    end

Running rant now:

    % rant
    mytask

Add prerequisites to create relations between tasks:

    task :first => [:t1, :t2] do |t|
        puts t.name
    end
    task :t1 do |t|
        puts t.name
    end
    task :t2 do |t|
        puts t.name
    end

In the definition of the "first" task we told Rant that it depends on task "t1" and task "t2". "t1" and "t2" are called prerequisites for "first". Try it out:

    % rant first
    t1
    t2
    first
    % rant t1
    t1
    % rant t2
    t2

\subsection rant_rantfile_file Defining a file task

You will notice that rant will run the actions for a normal task always its name is given on the commandline or it is required by another task. Often you want to create a file, e.g. a program by invoking a compiler. In this case, the action needs only to be run if the source files (prerequisites) have changed. Use a file task instead of a normal task.

In this example we use the sys.touch method to test our file task. (This method works the same as the Unix touch command: Update the modification time of a file or create an empty file):

    file "testfile" do |t|
        sys.touch t.name
    end

Now run rant:

    % rant
    touch testfile

This would have been the same with a normal task. But now run rant a second time:

    % rant

This time rant doesn’t run the action, because "testfile" is up to date. Of course you can add prerequisites the same way as for a normal task. Additionally you can add filenames as prerequisites. Assuming the files "a.o" and "b.o" are in the same directory as the Rantfile:

    file "myprog" => %w(a.o b.o) do |t|
        sys %w(cc -o), t.name, t.prerequisites
    end

Running rant:

    % rant
    cc -o myprog a.o b.o

Running a second time:

    % rant

Does nothing, myprog is up to date. Don‘t be irritated by the %w() syntax. It creates a list of strings. The following expressions are equivalent:

    ["a", "b", "c"]
    %w(a b c)

\subsection rant_rantfile_desc Adding task descriptions

The desc function lets you describe your tasks. A small example Rantfile:

    # Generate C source file ls.c with the xgen command.
    file "ls.c" => %w(ls1.x ls2.x) do |t|
        sys %w(xgen -o), t.name, t.prerequisites
    end

    desc "Build ls program."
    file "ls" => "ls.c" do
        sys "cc -o ls ls.c"
    end

    desc "Remove autogenerated files."
    task :clean do
        sys.rm_f %w(ls.c ls)
    end

(Note that xgen is a hypothetical command ;) The —tasks (or the short form, -T) option of rant shows this descriptions:

    % rant -T
    rant ls     # Build ls program.
    rant clean  # Remove autogenerated files.

Only the tasks which have a description are listed. 

\subsection rant_rantfile_gen Generators

The `gen` function takes a generator which usually creates one or more tasks for you. The following list of generators is immediately available:

* `Directory:`	Create directories.
* `Task:`	Define custom task.
* `Rule:`	Define a rule (a rule produces tasks on the fly).
* `Action:`	Run a block of code immediately.

\subsubsection rant_rantfile_gen_directory The Directory generator

An example usage of the Directory generator would be the backup example shown in the README file:

    file "misc/backup/data" => %w(misc/backup data) do |t|
        sys.cp "data", t.name
    end

    gen Directory, "misc/backup"

Now rant will create the directories "misc" and "backup" on demand. Assuming "misc/backup" doesn’t exist:

    % rant
    mkdir misc
    mkdir misc/backup
    cp data misc/backup/data

\subsubsection rant_rantfile_gen_task The Task generator

The Task generator allows you to determine by hand when your task action needs to be run:

    desc "Install with setup.rb"
    gen Task, :install do |t|
        t.needed { !File.exist? "InstalledFiles" }
        t.act do
            sys.ruby "setup.rb"
        end
    end

The act block of the "install" task will only be run if "InstalledFiles" doesn’t exist. Of course you can add prerequisites like with any other task. 

\subsubsection rant_rantfile_gen_rule Rules

A Rule allows you to tell Rant how it should build files matching a common pattern, e.g. how to build files ending in `.o`. A standard rule usage is to create C object files:

    gen Rule, '.o' => '.c' do |t|
        sys "cc -c -o #{t.name} #{t.source}"
    end

Assuming that we have the C source file `util.c` in the current directory:

    % rant util.o
    cc -c -o util.o util.c

Because Rant didn’t find a task for `util.o`, it looked for a matching rule and created a task for `util.o`.

The first line above could also be written as:

    gen Rule, :o => :c do |t|

The source method of the task object gives us the first dependency. So the following line has the same effect:

        sys "cc -c -o #{t.name} #{t.prerequisites.first}"

You can also refine the rule pattern by using a regular expression. To refine dependency selection give a block as source argument:

    src = lambda { |target| [target.sub_ext("c"), target.sub_ext("h")] }
    gen Rule, /^my_[^.]+\.o$/ => src do |t|
        sys "cc -c -o #{t.name} #{t.source}"
    end

This rule generates a task for files beginning with `my_` and ending in `.o` (like `my_program.o`). The task has a file ending in `.c` and one ending in `.h` as dependencies (like `my_program.c` and `my_program.h`) . Since `t.source` gives us the first dependency, the `.c` file will appear as argument to cc, but not the `.h` file.

The `sub_ext` method of the String class replaces anything after the last dot with the given string. 

\subsection rant_rantfile_import Importing additional generators

The import function lets you import additional generators. Currently the following come with Rant:

| Function     | Description            |
|--------------|------------------------|
| Clean        | Remove selected files. |
| AutoClean    | Remove all files generated by any file task (including those generated by rules). |
| DirectedRule | A Rule which takes sources from one or more directories and puts generated files into a specified directory. |
| SubFile      | Create file task and necessary directory tasks. |
| Command      | Tasks with command change recognition. |
| RubyTest     | Run `Test::Unit` tests for your Ruby code. |
| RubyDoc      | Run RDoc. |
| RubyPackage  | Generate tar, zip and gem packages of your Ruby application/library. |
| Archive::Tgz | Create gzipped tar archives. |
| Archive::Zip | Create zip archives. |
| Package::Tgz | Create gzipped tar packages. |
| Package::Zip | Create zip packages. |
| C::Dependencies | Determine dependencies between C/C++ source/header files caused by include statements. |
| Win32::RubyCmdWrapper | Create `.cmd` wrapper scripts for installation of Ruby scripts on Windows.  |

\section rant_references References

* [rant.rubyforge.org](http://rant.rubyforge.org)