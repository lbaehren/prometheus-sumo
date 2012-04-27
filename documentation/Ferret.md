
# Ferret search engine

Ferret is a Ruby port of the {http://jakarta.apache.org/lucene Java Lucene} search engine. In the same way as Lucene, it is not a standalone application, but a library you can use to index documents and search for things in them later.


## Concepts

* Index: Sequence of documents
* Document: Sequence of fields
* Field: Named sequence of terms
* Term: A text string, keyed by field name


## Creating an index

To create an in memory index is very simple;

    index = Index::Index.new()

To create a persistent index;

    index = Index::Index.new(:path => '/path/to/index')

Both of these methods create new Indexes with the StandardAnalyzer. An
analyzer is what you use to divide the input data up into tokens which you can
search for later. If you'd like to use a different analyzer you can specify it
here, eg;

    index = Index::Index.new(:path => '/path/to/index',
                             :analyzer => Analysis::WhiteSpaceAnalyzer.new)

For more options when creating an Index refer to Ferret::Index::Index.


## Adding Documents

To add a document you can simply add a string or an array of strings. This will
store all the strings in the "" (ie empty string) field (unless you specify the
default field when you create the index).

    index << "This is a new document to be indexed"
    index << ["And here", "is another", "new document", "to be indexed"]

But these are pretty simple documents. If this is all you want to index you
could probably just use SimpleSearch. So let's give our documents some fields;

    index << {:title => "Programming Ruby", :content => "blah blah blah"}
    index << {:title => "Programming Ruby", :content => "yada yada yada"}

Note the way that all field-names are Symbols. Although Strings will work,
this is a best-practice in Ferret. Or if you are indexing data stored in a
database, you'll probably want to store the id;

    index << {:id => row.id, :title => row.title, :date => row.date}

So far we have been storing and tokenizing all of the input data along with
term vectors. If we want to change this we need to change the way we setup the
index. You must create a FieldInfos object describing the index:

    field_infos = FieldInfos.new(:store => :no,
                                 :index => :untokenized_omit_norms,
                                 :term_vector => :no)

The values that you set FieldInfos to have will be used by default by all
fields. If you want to change the properties for specific fields, you need to
add a FieldInfo to field_infos. 

    field_infos.add_field(:title, :store => :yes, :index => :yes, :boost => 10.0)
    field_infos.add_field(:content, :store => :yes,
                                    :index => :yes,
                                    :term_vector => :with_positions_offsets)

If you need to add a field to an already open index you do so like this:

    index.field_infos.add_field(:new_field, :store => :yes)


## Searching

Now that we have data in our index, how do we actually use this index to
search the data? The Index offers two search methods, Index#search and
Index#search_each. The first method returns a Ferret::Index::TopDocs object.
The second we'll show here. Lets say we wanted to find all documents with the
phrase "quick brown fox" in the content field. We'd write;

    index.search_each('content:"quick brown fox"') do |id, score|
      puts "Document #{id} found with a score of #{score}"
    end

But "fast" has a pretty similar meaning to "quick" and we don't mind if the
fox is a little red. Also, the phrase could be in the title so we'll search
there as well. So we could expand our search like this;

    index.search_each('title|content:"quick|fast brown|red fox"') do |id, score|
      puts "Document #{id} found with a score of #{score}"
    end

What if we want to find all documents entered on or after 5th of September,
2005 with the words "ruby" or "rails" in any field. We could type something like;

    index.search_each('date:( >= 20050905) *:(ruby OR rails)') do |id, score|
      puts "Document #{index[id][:title]} found with a score of #{score}"
    end

Ferret has quite a complex query language. To find out more about Ferret's
query language, see Ferret::QueryParser. You can also construct even more
complex queries like Ferret::Search::Spans by hand. See Ferret::Search::Query
for more information.


## References

* Benjamin Krause, Mathias Meyer (2008) {http://www.heise.de/developer/artikel/Ferret-Lucene-Nachfolger-fuer-Ruby-227116.html Ferret: Lucene-Nachfolger für Ruby}

