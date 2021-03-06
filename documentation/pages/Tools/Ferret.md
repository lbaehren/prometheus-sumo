Ferret search engine    {#ferret}
====================

\tableofcontents

Ferret is a Ruby port of the [Java Lucene](http://jakarta.apache.org/lucene) search engine. In the same way as Lucene, it is not a standalone application, but a library you can use to index documents and search for things in them later.

\section ferret_install Installation

If you have gems installed you can simply do;

\verbatim
gem install ferret
\endverbatim

Otherwise, you will need Rake installed. De-compress the archive and enter its
top directory.

\verbatim
tar zxpvf ferret-<version>.tar.gz
cd ferret-<version>
\endverbatim

Run the following;

    $ rake ext
    $ ruby setup.rb config
    $ ruby setup.rb setup
    $ ruby setup.rb install

These simple steps install ferret in the default location of Ruby libraries.
You can also install files into your favorite directory by supplying setup.rb
some options. Try;

\verbatim
$ ruby setup.rb --help
\endverbatim

\section ferret_basic_operation Basic operation

\subsection ferret_index Creating an index

To create an in memory index is very simple;

\code
index = Index::Index.new()
\endcode

To create a persistent index;

\code
index = Index::Index.new(:path => '/path/to/index')
\endcode

Both of these methods create new Indexes with the StandardAnalyzer. An
analyzer is what you use to divide the input data up into tokens which you can
search for later. If you'd like to use a different analyzer you can specify it
here, eg;

\code
index = Index::Index.new(:path => '/path/to/index',
                         :analyzer => Analysis::WhiteSpaceAnalyzer.new)
\endcode

For more options when creating an Index refer to \c Ferret::Index::Index.

\subsection ferret_documents Adding Documents

To add a document you can simply add a string or an array of strings. This will
store all the strings in the "" (ie empty string) field (unless you specify the
default field when you create the index).

\code
index << "This is a new document to be indexed"
index << ["And here", "is another", "new document", "to be indexed"]
\endcode

But these are pretty simple documents. If this is all you want to index you
could probably just use SimpleSearch. So let's give our documents some fields;

\code
index << {:title => "Programming Ruby", :content => "blah blah blah"}
index << {:title => "Programming Ruby", :content => "yada yada yada"}
\endcode

Note the way that all field-names are Symbols. Although Strings will work,
this is a best-practice in Ferret. Or if you are indexing data stored in a
database, you'll probably want to store the id;

\code
index << {:id => row.id, :title => row.title, :date => row.date}
\endcode

So far we have been storing and tokenizing all of the input data along with
term vectors. If we want to change this we need to change the way we setup the
index. You must create a FieldInfos object describing the index:

\code
field_infos = FieldInfos.new(:store => :no,
                             :index => :untokenized_omit_norms,
                             :term_vector => :no)
\endcode

The values that you set FieldInfos to have will be used by default by all
fields. If you want to change the properties for specific fields, you need to
add a `FieldInfo` to `field_infos`.

\code
  field_infos.add_field(:title, :store => :yes, :index => :yes, :boost => 10.0)
  field_infos.add_field(:content, :store => :yes,
                                  :index => :yes,
                                  :term_vector => :with_positions_offsets)
\endcode

If you need to add a field to an already open index you do so like this:

\code
index.field_infos.add_field(:new_field, :store => :yes)
\endcode

\subsection ferret_search Searching

Now that we have data in our index, how do we actually use this index to
search the data? The Index offers two search methods, \c Index\#search and
\c Index\#search_each. The first method returns a \c Ferret::Index::TopDocs object.
The second we'll show here. Lets say we wanted to find all documents with the
phrase "quick brown fox" in the content field. We'd write;

\code
index.search_each('content:"quick brown fox"') do |id, score|
  puts "Document #{id} found with a score of #{score}"
end
\endcode

But "fast" has a pretty similar meaning to "quick" and we don't mind if the
fox is a little red. Also, the phrase could be in the title so we'll search
there as well. So we could expand our search like this;

\code
index.search_each('title|content:"quick|fast brown|red fox"') do |id, score|
  puts "Document #{id} found with a score of #{score}"
end
\endcode

What if we want to find all documents entered on or after 5th of September,
2005 with the words "ruby" or "rails" in any field. We could type something like;

\code
index.search_each('date:( >= 20050905) *:(ruby OR rails)') do |id, score|
  puts "Document #{index[id][:title]} found with a score of #{score}"
end
\endcode

Ferret has quite a complex query language. To find out more about Ferret's
query language, see \c Ferret::QueryParser. You can also construct even more
complex queries like \c Ferret::Search::Spans by hand. See \c Ferret::Search::Query
for more information.

\section ferret_rails Rails plugin: acts_as_ferret

Ferret based full text search for any ActiveRecord model

\subsection ferret_rails_install Installation

For system-wide installation with Rubygems run

\verbatim
sudo gem install acts_as_ferret
\endverbatim

Inside your \ref rails project you can use the \a plugin script

\verbatim
script/plugin install svn://projects.jkraemer.net/acts_as_ferret/trunk/plugin/acts_as_ferret
\endverbatim

\subsection ferret_rails_config Central configuration file

With this option, all acts_as_ferret indexes are configured in a single file,
\c RAILS_ROOT/config/aaf.rb:

\code
ActsAsFerret::define_index( 'my_index',
                            :models => {
                              SomeModel => {
                                :fields => {
                                  :name => { :boost => 4, :store => :yes, :via => :ferret_title },
                                  :foo => { :store => :no,  :index => :untokenized },
                                  :baz => { :store => :yes, :via => :ferret_content }
                                }
                              }
                            } )

ActsAsFerret::define_index( 'some_other_index',
                            :models => {
                              Foo => { :fields => { ... } },
                              Bar => { ... },
                            } )
\endcode

As you can see for every index you want to define there's a single call, and
each model that should go into the index gets it's own ferret options hash
(see the acts_as_ferret class method docs for all available options).

\subsection ferret_rails_usage Basic usage

To use acts_as_ferret in your project, add the following line to your
project's \c config/environment.rb:

\code
require 'acts_as_ferret'
\endcode

Include the following in your model class (specifiying the fields you want to
get indexed):

  \verbatim
  class Member < ActiveRecord::Base
    acts_as_ferret :fields => [:first_name, :last_name]
  end
  \endverbatim

  Now you can use \c ModelClass.find_by_contents(query) to find instances of your model
  whose indexed fields match a given query. All query terms are required by default,
  but explicit OR queries are possible. This differs from the ferret default, but
  imho is the more often needed/expected behaviour (more query terms result in
  less results).

  Please see \c ActsAsFerret::ActMethods\#acts_as_ferret for more information.

  \subsection ferret_rails_search How to do a Basic Search

  The Acts As Ferret plugin adds additional search methods to your ActiveRecord
  Model, and unlike other tutorials out there, we’re going to start with:

  \verbatim
  find_id_by_contents
  \endverbatim

  So, if we call:

  \verbatim
  total_results, members = Member.find_id_by_contents(“Gregg”)
  \endverbatim

  The following will happen:

  \li A folder in our rails application called \c /index/development/member is
  created, and the index files will be created there.

  \li All of my Members will be queried and their first/last name put into this
  index. Now every time I add/update/delete a member, this index will
  auto-magically be updated for me! If you ever need to regenerate an index,
  then just remove this corresponding folder, restart your server, and it will
  be regenerated next time you query against the table.

  \li ActsAsFerret then calls Ferret’s Search_Each function on our index.

  \li We get returned a count of the items, and the first 10 results, in this format:
  \verbatim
  members = [
    {:model => “Member”, :id => “4”,  :score => “1.0”},
    {:model => “Member”, :id => “21”, :score => “0.93211”},
    {:model => “Member”, :id => “27”, :score => “0.32212”}
  ]
  \endverbatim
  We get an array of the first 10 results (I’m only showing 3 above) and we get
  the ids and search scores for each of em.

  However, even if there are more then 40 possible results, we’re only going to
  get 10 results returned.

  \subsection ferret_rails_pagination Pagination of search results

  It appears that it’s quite easy to integrate \c acts_as_ferret with
  \c will_paginate, the officially recommended pagination plugin for \ref rails.

  First, a patch is needed (e.g. in \c vendor/plugins/patches/lib); it could
  also go in some of existing application files, e.g. bottom of \c environment.rb:

  \verbatim
  module ActsAsFerret
    module ClassMethods
      alias :find_all_by_contents :find_by_contents
    end
  end
  \endverbatim

  Then, in controller:

  \verbatim
  @users = User.paginate_by_contents(@search.query,
    :total_entries => User.total_hits(@search.query), :page => params[:page],
    :per_page => 10)
  \endverbatim

  Change User to your model class here. You can also use sorting here.

  The trick is that \c will_paginate is friendly to model class’s methods like
  \c find_all_by_xxx; acts_as_ferret’s find_by_contents’s name is a bit wrong
  for it, so we make an alias, and later this method becomes our model’s method,
  when we put acts_as_ferret statement in the model class definition.

  \subsection ferret_rails_boost Using Boost

  Lastly, it’s worth mentioning the Boost attribute. What this allows you to do
  is boost the score of a given indexed field, for instance:

  \verbatim
  acts_as_ferret :fields => {
    :title  => {:boost => 2},
    :author => {:boost => 0}
  }
  \endverbatim

  This will modify the score slightly when you do a search, so that the results
  from a title match are scored a little higher then results from an author
  match.

  However, this does NOT mean that all title results will appear above author
  results. If an author result is a direct match, it still may be ranked above
  a title result.

\section ferret_references References

- [Ferret project page](http://rubyforge.org/projects/ferret) on rubyforge.org
- [Ferret search library documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/ferret)
- [acts_as_ferret](https://github.com/jkraemer/acts_as_ferret) - Rails full text search plugin
- [acts_as_ferret API documentation](http://rdoc.info/github/jkraemer/acts_as_ferret)
- Benjamin Krause, Mathias Meyer (2008) [Ferret: Lucene-Nachfolger für Ruby](http://www.heise.de/developer/artikel/Ferret-Lucene-Nachfolger-fuer-Ruby-227116.html)
- [acts_as_ferret Tutorial](http://www.gleanr.com/gleans/24180_acts_as_ferret_tutorial_rails_envy) (gregg, 2007)
