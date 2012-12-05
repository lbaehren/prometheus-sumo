Search    {#pandora_search}
======

\tableofcontents

- \ref ferret

\section pandora_search_ferret Integration of Ferret search engine

Components providing or using the \ref ferret with \ref pandora :

\verbatim
  pandora
  |-- app
  |   |-- models
  |   |   `-- image.rb
  |   `-- controllers
  |       `-- search_controller.rb
  |-- config
  |   `-- app
  |       `-- query.yml                 ...  Set default_engine handling queries
  |-- lib
  |   |-- query.rb
  |   |-- query_analyzer.rb
  |   |-- engine
  |   |   |-- ferret
  |   |   |   `-- analyzer.rb
  |   |   `-- ferret.rb
  |   `-- extensions
  |       `-- to_ferret_doc.rb
  `-- vendor
      `-- plugins
          `-- acts_as_ferret
\endverbatim

Let's have a closer look at some of the components:

  \li Analyzer (\c lib/engine/ferret/analyzer.rb)
  \code
  class Engine::Ferret

    class Analyzer < Ferret::Analysis::Analyzer

      include Ferret::Analysis

      def self.normalize!(str)
        str.replace_diacritics!
        str.gsub!(/'/, '’')
      end

      def token_stream(field, str)
        self.class.normalize!(str)

        ts = StandardTokenizer.new(str)
        ts = LowerCaseFilter.new(ts)
        ts = HyphenFilter.new(ts)
      end

    end

  end
  \endcode
