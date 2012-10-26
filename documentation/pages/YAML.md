YAML    {#yaml}
====

\tableofcontents

\section yaml_overview Overview

**YAML** is a human-readable data serialization format that takes concepts from
programming languages such as C, Perl, and Python, and ideas from XML and the
data format of electronic mail (RFC 2822).

**YAML** syntax was designed to be easily mapped to data types common to most
high-level languages: list, associative array, and scalar. Its familiar indented
outline and lean appearance make it especially suited for tasks where humans are
likely to view or edit data structures, such as configuration files, dumping
during debugging, and document headers (e.g. the headers found on most e-mails
are very close to YAML). Although well-suited for hierarchical data representation,
it also has a compact syntax for relational data as well. Its line and whitespace
delimiters make it friendly to ad hoc grep/Python/Perl/Ruby operations. A major
part of its accessibility comes from eschewing the use of enclosures like quotation
marks, brackets, braces, and open/close-tags which can be hard for the human eye
to balance in nested hierarchies.

\test prometheus::config::ConfigFileBase
\test TestYamlReading.cc
\test tEmitting.cc

\section yaml_comparison Comparison to other data structure format languages

While YAML shares similarities with JSON, XML and SDL, it also has characteristics
that are unique in comparison to many other similar format languages.

\subsection yaml_comparison_json JSON

JSON syntax is a subset of YAML version 1.2, which was promulgated with the
express purpose of bringing YAML "into compliance with JSON as an official
subset." Though prior versions of YAML were not strictly compatible, the
discrepancies were rarely noticeable and most JSON documents can be parsed by
some YAML parsers such as Syck. This is because JSON's semantic structure is
equivalent to the optional "inline-style" of writing YAML. While extended
hierarchies can be written in inline-style like JSON, this is not a recommended
YAML style except when it aids clarity.

YAML has many additional features lacking in JSON, including extensible data
types, relational anchors, strings without quotation marks, and mapping types
preserving key order.

\subsection yaml_comparison_xml XML and SDL

YAML lacks the notion of tag attributes that are found in \ref xml and SDL (Simple
Declarative Language). For data structure serialization, tag attributes are,
arguably, a feature of questionable utility since the separation of data and
meta-data adds complexity when represented by the natural data structures
(associative arrays, lists) in common languages. Instead YAML has extensible
type declarations (including class types for objects).

YAML itself does not have XML's language-defined document schema descriptors
that allow, for example, a document to self validate. However, there are several
externally defined schema descriptor languages for YAML (e.g. Doctrine, Kwalify
and Rx) that fulfill that role. Moreover, the semantics provided by YAML's
language-defined type-declarations in the YAML document itself frequently relaxes
the need for a validator in simple, common situations. Additionally, YAXML,
which represents YAML data structures in XML, allows XML schema importers and
output mechanisms like XSLT to be applied to YAML.

\section yaml_language Language elements

Explicit data typing is seldom seen in the majority of YAML documents since
YAML autodetects simple types. Data types can be divided into three categories:
core, defined, and user-defined. Core are ones expected to exist in any parser
(e.g. floats, ints, strings, lists, maps, ...). Many more advanced data types,
such as binary data, are defined in the YAML specification but not supported
in all implementations. Finally YAML defines a way to extend the data type
definitions locally to accommodate user defined classes, structures or primitives
(e.g. quad precision floats).

\subsection yaml_language_collections Collections

YAML’s block collections use indentation for scope and begin each entry on its
own line. Block sequences indicate each entry with a dash and space (`-`).
Mappings use a colon and space (`: `) to mark each key: value pair. Comments
begin with an octothorpe (also called a _hash_, _sharp_, _pound_, or _number
sign_ - “#”).

* Sequence of Scalars (ball players)
\code
- Mark McGwire
- Sammy Sosa
- Ken Griffey
\endcode

* Mapping Scalars to Scalars (player statistics)
\code
hr:  65    # Home runs
avg: 0.278 # Batting average
rbi: 147   # Runs Batted In
\endcode

* Mapping Scalars to Sequences (ball clubs in each league)
\code
american:
  - Boston Red Sox
  - Detroit Tigers
  - New York Yankees
national:
  - New York Mets
  - Chicago Cubs
  - Atlanta Braves
\endcode

* Sequence of Mappings (players’ statistics)
\code
-
  name: Mark McGwire
  hr:   65
  avg:  0.278
-
  name: Sammy Sosa
  hr:   63
  avg:  0.288
\endcode

* Sequence of Sequences
\code
- [name        , hr, avg  ]
- [Mark McGwire, 65, 0.278]
- [Sammy Sosa  , 63, 0.288]
\endcode

* Mapping of Mappings
\code
Mark McGwire: {hr: 65, avg: 0.278}
Sammy Sosa: {
    hr: 63,
    avg: 0.288
  }
\endcode

\subsection yaml_language_structures Structures

YAML uses three dashes (`---`) to separate directives from document content.
This also serves to signal the start of a document if no directives are present.
Three dots (`...`) indicate the end of a document without starting a new one,
for use in communication channels.

* Two Documents in a Stream (each with a leading comment)
\code
# Ranking of 1998 home runs
---
- Mark McGwire
- Sammy Sosa
- Ken Griffey

# Team ranking
---
- Chicago Cubs
- St Louis Cardinals
\endcode

* Play by Play Feed (from a Game)
\code
---
time: 20:03:20
player: Sammy Sosa
action: strike (miss)
...
---
time: 20:03:47
player: Sammy Sosa
action: grand slam
...
\endcode

* Single Document with two Comments
\code
---
hr: # 1998 hr ranking
  - Mark McGwire
  - Sammy Sosa
rbi:
  # 1998 rbi ranking
  - Sammy Sosa
  - Ken Griffey
\endcode

\subsection yaml_language_scalars Scalars

Scalar content can be written in block notation, using a literal style (indicated
by `|`) where all line breaks are significant. Alternatively, they can be written
with the folded style (denoted by `>`) where each line break is folded to a
space unless it ends an empty or a more-indented line.

* In literals, newlines are preserved
\code
# ASCII Art
--- |
  \//||\/||
  // ||  ||__
\endcode

* In the folded scalars, newlines become spaces
\code
--- >
  Mark McGwire's
  year was crippled
  by a knee injury.
\endcode

\subsection yaml_language_tags Tags

In YAML, untagged nodes are given a type depending on the application. The
examples in this specification generally use the `seq`, `map` and `str`
types from the fail safe schema. A few examples also use the `int`, `float`,
and `null` types from the JSON schema. The repository includes additional
types such as `binary`, `omap`, `set` and others.

* Integers
\code
canonical: 12345
decimal: +12345
octal: 0o14
hexadecimal: 0xC
\endcode

* Floating Point
\code
canonical: 1.23015e+3
exponential: 12.3015e+02
fixed: 1230.15
negative infinity: -.inf
not a number: .NaN
\endcode

* Miscellaneous
\code
null:
booleans: [ true, false ]
string: '012345'
\endcode

* Timestamps
\code
canonical: 2001-12-15T02:59:43.1Z
iso8601: 2001-12-14t21:59:43.10-05:00
spaced: 2001-12-14 21:59:43.10 -5
date: 2002-12-14
\endcode

\section yaml_cpp Using YAML with C++

\subsection yaml_cpp_emitting Emitting a document

\subsubsection yaml_cpp_emitting_basic Basic Emitting

The model for emitting YAML is ``std::ostream manipulators``. A ``YAML::Emitter``
objects acts as an output stream, and its output can be retrieved through the ``c_str()`` function (as in ``std::string``). For a simple example:

\code
#include "yaml.h"

int main()
{
   YAML::Emitter out;
   out << "Hello, World!";

   std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"
   return 0;
}
\endcode

\subsubsection yaml_cpp_emitting_lists Simple Lists and Maps

A ``YAML::Emitter`` object acts as a state machine, and we use manipulators to move
it between states. Here's a simple sequence:

\code
YAML::Emitter out;
out << YAML::BeginSeq;
out << "eggs";
out << "bread";
out << "milk";
out << YAML::EndSeq;
\endcode

produces

\verbatim
- eggs
- bread
- milk
\endverbatim

A simple map:

\code
YAML::Emitter out;
out << YAML::BeginMap;
out << YAML::Key << "name";
out << YAML::Value << "Ryan Braun";
out << YAML::Key << "position";
out << YAML::Value << "LF";
out << YAML::EndMap;
\endcode

produces

\verbatim
name: Ryan Braun
position: LF
\endverbatim

These elements can, of course, be nested:

\code
YAML::Emitter out;
out << YAML::BeginMap;
out << YAML::Key << "name";
out << YAML::Value << "Barack Obama";
out << YAML::Key << "children";
out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
out << YAML::EndMap;
\endcode

  produces

  \verbatim
  name: Barack Obama
  children:
    - Sasha
    - Malia
  \endverbatim

  \subsection yaml_cpp_parsing Parsing a document

  Here's a complete example of how to parse a complex YAML file (``monsters.yaml``):

  \include monsters.yaml

  \subsubsection yaml_cpp_parsing_basic Basic parsing

  The parser accepts streams, not file names, so you need to first load the file.
  Since a YAML file can contain many documents, you can grab them one-by-one. A
  simple way to parse a YAML file might be:

  \code
  #include <fstream>
  #include "yaml-cpp/yaml.h"

  int main()
  {
      std::ifstream fin("test.yaml");
      YAML::Parser parser(fin);

      YAML::Node doc;
      while(parser.GetNextDocument(doc)) {
         // ...
      }

      return 0;
  }
  \endcode

  \subsubsection yaml_cpp_reading Reading From the Document

Suppose we have a document consisting only of a scalar. We can read that scalar like this:

  \code
    YAML::Node doc;    // let's say we've already parsed this document
    std::string scalar;
    doc >> scalar;
    std::cout << "That scalar was: " << scalar << std::endl;
  \endcode

How about sequences? Let's say our document now consists only of a sequences of scalars. We can use an iterator:

  \code
    YAML::Node doc;    // already parsed
    for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
        std::string scalar;
        *it >> scalar;
        std::cout << "Found scalar: " << scalar << std::endl;
    }
  \endcode

... or we can just loop through:

  \code
    YAML::Node doc;    // already parsed
    for(unsigned i=0;i<doc.size();i++) {
        std::string scalar;
        doc[i] >> scalar;
        std::cout << "Found scalar: " << scalar << std::endl;
    }
  \endcode

And finally maps. For now, let's say our document is a map with all keys/values being scalars. Again, we can iterate:

  \code
  YAML::Node doc;    // already parsed
  for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
      std::string key, value;
      it.first() >> key;
      it.second() >> value;
      std::cout << "Key: " << key << ", value: " << value << std::endl;
  }
  \endcode

Note that dereferencing a map iterator is undefined; instead, use the first and second methods to get the key and value nodes, respectively.

Alternatively, we can pick off the values one-by-one, if we know the keys:

  \code
  YAML::Node doc;    // already parsed
  std::string name;
  doc["name"] >> name;
  int age;
  doc["age"] >> age;
  std::cout << "Found entry with name '" << name << "' and age '" << age << "'\n";
  \endcode

One thing to be keep in mind: reading a map by key (as immediately above) requires looping through all entries until we find the right key, which is an O(n) operation. So if you're reading the entire map this way, it'll be O(n^2). For small n, this isn't a big deal, but I wouldn't recommend reading maps with a very large number of entries (>100, say) this way.

\subsubsection yaml_cpp_parsing_example A complete example

The following code will parse the example file ``monsters.yaml`` listed above:

\include parse-monsters.cc

\subsubsection yaml_cpp_parsing_map Iterate through a map

Here is some additional help for iterating through the data structure: for a
data structure such as

\code
characterType :
 type1 :
  attribute1 : something
  attribute2 : something
 type2 :
  attribute1 : something
  attribute2 : something
\endcode

the following code construct may be valid:

\code
YAML::Node characterType = node["characterType"];
for(YAML::const_iterator it=characterType.begin();it != characterType.end();++it) {
   std::string key = it->first.as<std::string>();       // <- key
   cTypeList.push_back(it->second.as<CharacterType>()); // <- value
}
\endcode

\section yaml_ruby Using YAML with Ruby



\section yaml_references References & Software packages

* [YAML 1.2 specification](http://yaml.org/spec/1.2/spec.html)
* [YAML 1.1 specification](http://yaml.org/spec/1.1/current.html)
* [Wikipedia entry](http://en.wikipedia.org/wiki/YAML)
* [Basic methods for parsing a YAML document](http://code.google.com/p/yaml-cpp/wiki/HowToParseADocument)

Libraries for emitting and parsing YAML are available throughout a wide range
of programming languages:

* [LibYAML](http://pyyaml.org/wiki/LibYAML) - a YAML 1.1 parser and emitter written in C
* [yaml-cpp](http://code.google.com/p/yaml-cpp) - a YAML parser and emitter in C++ matching the YAML 1.2 spec.
* [Mirror of the official yaml-cpp Google code repository](https://github.com/nebirhos/yaml-cpp)
* [YAML component from the BOOST vault serialization library](https://github.com/boost-vault/serialization)
* [Iterate through a map with undefined values](http://stackoverflow.com/questions/12374691/yaml-cpp-easiest-way-to-iterate-through-a-map-with-undefined-values)
