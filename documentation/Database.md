
Database(s)
===========

## Schema Information

### Accounts

<dl>
  <dt>Table name</dt>     <dd>accounts</dd>
  <dt>Schema version</dt> <dd>135</dd>
  <dt>Implementation</dt> <dd>{Account app/models/account.rb}</dd>
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
  <dt>Implementation</dt> <dd>{Collection app/models/collection.rb}</dd>
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
  <dt>Implementation</dt> <dd>{Comment app/models/comment.rb}</dd>
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
  <dt>Implementation</dt> <dd>{Image app/models/image.rb}</dd>
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
  <dt>Implementation</dt> <dd>{Institution app/models/institution.rb}</dd>
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
  <dt>Implementation</dt> <dd>{License app/models/license.rb}</dd>
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
  <dt>Implementation</dt> <dd>{Role app/models/role.rb}</dd>
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
  <dt>Implementation</dt> <dd>{Source app/models/source.rb}</dd>
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

## Exploring the database

You can explore the contents of your database - including the various tables
contained therein - directly: after starting up the {file:MySQL} command line
tool via

    $ mysql -u <login> -p

you can inspect the available databases:

    mysql> SHOW DATABASES;

Depending on the population of your database the result might look something
like this:

    +---------------------+
    | Database            |
    +---------------------+
    | information_schema  |
    | mysql               |
    | pandora_development |
    +---------------------+
    3 rows in set (0.11 sec)

### List of tables

Having identified the database used by **pandora**, we now can obtain a listing
of the tables contained therein:

    mysql> SHOW TABLES IN `pandora_development`

If the database has been initialized, the output will look like this:

    +-------------------------------+
    | Tables_in_pandora_development |
    +-------------------------------+
    | accounts                      |
    | accounts_groups               |
    | accounts_images               |
    | accounts_institutions         |
    | accounts_permissions          |
    | accounts_roles                |
    | announcements                 |
    | ar_mails                      |
    | bounce_emails                 |
    | brain_busters                 |
    | change_sets                   |
    | changes                       |
    | client_applications           |
    | collections                   |
    | collections_collaborators     |
    | collections_images            |
    | collections_keywords          |
    | collections_viewers           |
    | comments                      |
    | ...                           |
    +-------------------------------+
    51 rows in set (0.00 sec)

### Table columns

In order to list the columns within a given table, use the ``SHOW COLUMNS`` command:

    mysql> SHOW COLUMNS IN pandora_development.accounts;

which will list the columns:

    +--------------------------------+--------------+------+-----+---------+----------------+
    | Field                          | Type         | Null | Key | Default | Extra          |
    +--------------------------------+--------------+------+-----+---------+----------------+
    | id                             | int(11)      | NO   | PRI | NULL    | auto_increment |
    | email                          | varchar(255) | YES  | MUL | NULL    |                |
    | login                          | varchar(255) | YES  | MUL | NULL    |                |
    | firstname                      | varchar(255) | YES  |     | NULL    |                |
    | lastname                       | varchar(255) | YES  |     | NULL    |                |
    | title                          | varchar(255) | YES  |     | NULL    |                |
    | addressline                    | varchar(255) | YES  |     | NULL    |                |
    | postalcode                     | varchar(255) | YES  |     | NULL    |                |
    | city                           | varchar(255) | YES  |     | NULL    |                |
    | country                        | varchar(255) | YES  |     | NULL    |                |
    | institution_id                 | int(11)      | YES  | MUL | NULL    |                |
    | crypted_password               | varchar(40)  | YES  |     | NULL    |                |
    | salt                           | varchar(40)  | YES  |     | NULL    |                |
    | created_at                     | datetime     | YES  |     | NULL    |                |
    | updated_at                     | datetime     | YES  |     | NULL    |                |
    | ...                            | ...          | ...  |     | ...     |                |
    +--------------------------------+--------------+------+-----+---------+----------------+
    37 rows in set (0.00 sec)

If we now want to retrieve more information on the actual contents stored within
table columns, we can do so using the ``SELECT`` command:

    mysql> SELECT * FROM pandora_development.accounts LIMIT 0,10


## Importing a new (external) database

The import of a new database is channeled through the generation and subsequent
reading of an XML schema; the latter is either provided directly by the
maintainer(s) of the external database, or generated from e.g. a SQL dump of the
original database.

Models or new sources can be found in

    pandora
    `-- app/models
            |-- source
            |   |-- amtub.rb
            |   |-- arachne.rb
            |   |-- archgiessen.rb
            |   |..
            |-- source.rb
            `-- xml_source.rb

In order ingest a new database, the following building blocks/information are
required:

### XML schema for the original data

    <?xml version="1.0" encoding="UTF-8"?>
    <dataroot>
    <row>
      <bild_nr>G8001</bild_nr>
      <datierung>1783-1786</datierung>
      <gattung>Gartenarchitektur</gattung>
      <inventar_nr>GS 6258</inventar_nr>
      <kuenstler>Jussow, Heinrich Christoph (Zeichner)</kuenstler>
      <objekt>Tempel</objekt>
      <objekt_id>11846</objekt_id>
      <titel>Entwurf zu einem Gartentempel, Aufriß</titel>
    </row>
    <row>
      <bild_nr>G8002</bild_nr>
      <datierung>1783-1786</datierung>
      <gattung>Private Architektur</gattung>
      <inventar_nr>GS 6251</inventar_nr>
      <kuenstler>Jussow, Heinrich Christoph (Zeichner)</kuenstler>
      <objekt>Villa</objekt>
      <objekt_id>11839</objekt_id>
      <titel>Entwurf zu einer Villa, Grund- und Aufriß der Gartenfassade</titel>
    </row>

### Source model

Once the XML schema for the new data is available, the information can be
accessible to _pandora_

    class Source
    
      class Kassel < XMLSource::Document
    
        def self.persist
          %w[bild_nr inventar_nr]
        end
    
        module Record
    
          def path
            "#{self/'bild_nr'}.jpg"
          end
    
          def d_artist
            self/'kuenstler'
          end
    
          def artists_for_vgbk
            ["#{self/'kuenstler'}".sub(/ \(.*/, '').split(', ').reverse.join(' ')]
          end


## Index generation

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
