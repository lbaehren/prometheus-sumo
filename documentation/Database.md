
Database(s)
===========

## Schema Information

### Accounts

<dl>
  <dt>Table name</dt>     <dd>accounts</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/account.rb</dd>
</dl>

    id                             :integer(11)   not null, primary key
    email                          :string(255)
    login                          :string(255)
    firstname                      :string(255)
    lastname                       :string(255)
    title                          :string(255)
    addressline                    :string(255)
    postalcode                     :string(255)
    city                           :string(255)
    country                        :string(255)
    institution_id                 :integer(11)
    crypted_password               :string(40)
    salt                           :string(40)
    created_at                     :datetime
    updated_at                     :datetime
    expires_at                     :datetime
    notified_at                    :datetime
    newsletter                     :boolean(1)    default(TRUE)
    member_since                   :datetime
    remember_token                 :string(255)
    remember_token_expires_at      :datetime
    notes                          :text
    local_identifier               :string(255)
    registered_at                  :datetime
    code                           :string(255)
    announcement_hide_time         :datetime
    email_verified_at              :datetime
    accepted_terms_of_use_at       :datetime
    status                         :string(255)
    mode                           :string(255)
    creator_id                     :integer(11)
    about                          :text
    about_de                       :text
    accepted_terms_of_use_revision :integer(11)
    login_failed_at                :datetime
    failed_logins                  :integer(11)   default(0)
    disabled_at                    :datetime


### Collection

<dl>
  <dt>Table name</dt>     <dd>collections</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/collection.rb</dd>
</dl>

    id                :integer(11)   not null, primary key
    title             :string(255)
    description       :text
    created_at        :datetime
    updated_at        :datetime
    owner_id          :integer(11)
    notes             :text
    parent_id         :integer(11)
    forked_at         :datetime
    public_access     :string(255)
    thumbnail_id      :string(255)
    links             :text
    changed_at        :datetime
    references        :text
    meta_image        :boolean(1)
    meta_image_reader :string(255)


### Comment

<dl>
  <dt>Table name</dt>     <dd>comments</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/comment.rb</dd>
</dl>

    id              :integer(11)   not null, primary key
    collection_id   :integer(11)
    parent_id       :integer(11)
    author_id       :integer(11)
    text            :text
    created_at      :datetime
    updated_at      :datetime
    image_id        :string(255)
    presentation_id :integer(11)

A comment given to by an individual user (``author_id``) on a resource, such as a collection or a slide.


### Image

<dl>
  <dt>Table name</dt>     <dd>images</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/image.rb</dd>
</dl>

    pid        :string(255)   not null, primary key
    source_id  :integer(11)
    votes      :integer(11)   default(0)
    score      :integer(11)   default(0)
    checked_at :datetime


### Institution

<dl>
  <dt>Table name</dt>     <dd>institutions</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/institution.rb</dd>
</dl>

    id             :integer(11)   not null, primary key
    name           :string(255)
    title          :string(255)
    description    :text
    addressline    :string(255)
    postalcode     :string(255)
    city           :string(255)
    country        :string(255)
    email          :string(255)
    homepage       :string(255)
    contact_id     :integer(11)
    ipranges       :text
    ipuser_id      :integer(11)
    created_at     :datetime
    updated_at     :datetime
    campus_id      :integer(11)
    member_since   :datetime
    notes          :text
    public_info    :text
    issuer         :string(255)
    parsed_ranges  :text
    short          :string(255)
    hostnames      :text


### Invoice

<dl>
  <dt>Table name</dt>     <dd>invoices</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/invoice.rb</dd>
</dl>

    id              :integer(11)   not null, primary key
    due             :datetime
    end             :datetime
    amount          :float
    issued_at       :datetime
    paid_at         :datetime
    reminded_at     :datetime
    issuer          :string(255)
    license_id      :integer(11)
    license_type_id :integer(11)
    invoice_no      :string(255)


### License

<dl>
  <dt>Table name</dt>     <dd>licenses</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/license.rb</dd>
</dl>

    id                 :integer(11)   not null, primary key
    license_type_id    :integer(11)
    institution_id     :integer(11)
    account_id         :integer(11)
    created_at         :datetime
    updated_at         :datetime
    expires_at         :datetime
    terminates_at      :datetime
    amount             :float
    valid_from         :datetime
    paid_from          :datetime


### License Type

<dl>
  <dt>Table name</dt>     <dd>license_types</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/license_type.rb</dd>
</dl>

    id     :integer(11)   not null, primary key
    title  :string(255)
    amount :integer(11)


### Role

<dl>
  <dt>Table name</dt>     <dd>roles</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/role.rb</dd>
</dl>

    id    :integer(11)   not null, primary key
    title :string(255)


### Settings

<dl>
  <dt>Table name</dt>     <dd>settings</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/settings.rb</dd>
</dl>

    id             :integer(11)   not null, primary key
    user_id        :integer(11)
    type           :string(255)
    zoom           :boolean(1)
    per_page       :integer(11)
    list_per_page  :integer(11)
    order          :string(255)
    list_order     :string(255)
    direction      :string(255)
    list_direction :string(255)
    view           :string(255)
    locale         :string(255)
    start_page     :string(255)
    facets         :boolean(1)


### Source

<dl>
  <dt>Table name</dt>     <dd>sources</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/source.rb</dd>
</dl>

    id                :integer(11)   not null, primary key
    title             :string(255)
    name              :string(255)
    kind              :string(255)
    type              :string(255)
    institution_id    :integer(11)
    contact_id        :integer(11)
    admin_id          :integer(11)
    created_at        :datetime
    updated_at        :datetime
    description       :text
    url               :text
    email             :string(255)
    technical_info    :text
    encoding          :string(255)   default("utf-8")
    record_count      :integer(11)   default(0)
    prometheus        :boolean(1)
    loaded_at         :datetime
    dbuser_id         :integer(11)
    rating            :float
    description_de    :text
    technical_info_de :text
    skip              :boolean(1)

There are several conditions characterizing a source: e.g. in order to determine
whether a source is considered an ``open_source``

    def self.conditions_for_active
      { :conditions => ['record_count > ?', 0] }.merge_conditions(
        production? && ['kind <> ?', KIND_OF_DUMMY]
      )
    end

    def self.conditions_for_open_access
     { :conditions => "#{quoted_table_name}.dbuser_id IS NOT NULL" }
    end

    def self.conditions_for_open_sources
      conditions_for_open_access.merge_conditions(conditions_for_active)
    end


### Stats 

<dl>
  <dt>Table name</dt>     <dd>stats</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>app/models/stats.rb</dd>
</dl>

     id                :integer(11)   not null, primary key
     pid               :string(255)
     host              :string(255)
     controller        :string(255)
     action            :string(255)
     ip                :string(255)
     datetime          :datetime
     request_method    :string(255)
     sid               :string(255)
     params            :text
     params_hash       :string(255)
     user_agent        :string(255)
     accept_language   :string(255)
     runtime           :float
     rendering_runtime :float
     db_runtime        :float
     status            :string(255)
     request_uri       :text
     created_at        :datetime
     updated_at        :datetime
     referer           :text
     year              :integer(11)
     month             :integer(11)
     day               :integer(11)
     token_type        :string(255)
     token             :string(255)
     user_id           :integer(11)
     client_id         :integer(11)
     institution_id    :integer(11)
     flags             :(0)


### Sum Stats

[Table name] sum_stats
[Schema version] 135
[Implementation] app/models/sum_stats.rb

    id                     :integer(11)   not null, primary key
    year                   :integer(11)
    month                  :integer(11)
    day                    :integer(11)
    sessions_campus        :integer(11)   default(0)
    sessions_personalized  :integer(11)   default(0)
    searches_campus        :integer(11)   default(0)
    searches_personalized  :integer(11)   default(0)
    downloads_campus       :integer(11)   default(0)
    downloads_personalized :integer(11)   default(0)
    hits_campus            :integer(11)   default(0)
    hits_personalized      :integer(11)   default(0)
    runtime_sum            :float         default(0.0)
    runtime_sqr            :float         default(0.0)
    runtime_min            :float         default(0.0)
    runtime_max            :float         default(0.0)
    runtime_count          :integer(11)   default(0)
    created_at             :datetime
    updated_at             :datetime
    institution_id         :integer(11)

## Search index

### Ferret search engine

Ferret is a Ruby port of the {http://jakarta.apache.org/lucene Java Lucene} search engine. In the same way as Lucene, it is not a standalone application, but a library you can use to index documents and search for things in them later.

#### Creating an index

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

#### Adding Documents

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

#### Searching

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

### Index generation

Prerequisite for a working search is an index.

    <installation root>/app/pandora/shared
    `-- index
         `-- production
             |-- 0_11_8
             |   |-- image
             |   |   |-- 1332541248
             |   |   |-- 1333630394
             |   |   |-- 1334590731
             |   |   `-- 1334932732
             |   `-- resource
             |       |-- 1327917072
             |       |-- 1330708669
             |       `-- 1331304781
             `-- 0_11_8_1 -> 0_11_8
