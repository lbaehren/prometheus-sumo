
# YAML

## Emitting a document

### ... using Ruby

### ... using C++

#### Basic Emitting

The model for emitting YAML is ``std::ostream manipulators``. A ``YAML::Emitter`` objects acts as an output stream, and its output can be retrieved through the ``c_str()`` function (as in ``std::string``). For a simple example:

    #include "yaml.h"
    
    int main()
    {
       YAML::Emitter out;
       out << "Hello, World!";
       
       std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"
       return 0;
    }

#### Simple Lists and Maps

A ``YAML::Emitter`` object acts as a state machine, and we use manipulators to move it between states. Here's a simple sequence:

    YAML::Emitter out;
    out << YAML::BeginSeq;
    out << "eggs";
    out << "bread";
    out << "milk";
    out << YAML::EndSeq;

produces

    - eggs
    - bread
    - milk

A simple map:

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "name";
    out << YAML::Value << "Ryan Braun";
    out << YAML::Key << "position";
    out << YAML::Value << "LF";
    out << YAML::EndMap;

produces

    name: Ryan Braun
    position: LF

These elements can, of course, be nested:

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "name";
    out << YAML::Value << "Barack Obama";
    out << YAML::Key << "children";
    out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
    out << YAML::EndMap;

produces

    name: Barack Obama
    children:
      - Sasha
      - Malia

## Parsing a document

Here's a complete example of how to parse a complex YAML file (``monsters.yaml``):

    - name: Ogre
      position: [0, 5, 0]
      powers:
        - name: Club
          damage: 10
        - name: Fist
          damage: 8
    - name: Dragon
      position: [1, 0, 10]
      powers:
        - name: Fire Breath
          damage: 25
        - name: Claws
          damage: 15
    - name: Wizard
      position: [5, -3, 0]
      powers:
        - name: Acid Rain
          damage: 50
        - name: Staff
          damage: 3

### ... using Ruby


### ... using C++

#### Basic parsing

The parser accepts streams, not file names, so you need to first load the file.
Since a YAML file can contain many documents, you can grab them one-by-one. A
simple way to parse a YAML file might be:

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

#### Reading From the Document

Suppose we have a document consisting only of a scalar. We can read that scalar like this:

    YAML::Node doc;    // let's say we've already parsed this document
    std::string scalar;
    doc >> scalar;
    std::cout << "That scalar was: " << scalar << std::endl;

How about sequences? Let's say our document now consists only of a sequences of scalars. We can use an iterator:

    YAML::Node doc;    // already parsed
    for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
        std::string scalar;
        *it >> scalar;
        std::cout << "Found scalar: " << scalar << std::endl;
    }

... or we can just loop through:

    YAML::Node doc;    // already parsed
    for(unsigned i=0;i<doc.size();i++) {
        std::string scalar;
        doc[i] >> scalar;
        std::cout << "Found scalar: " << scalar << std::endl;
    }

And finally maps. For now, let's say our document is a map with all keys/values being scalars. Again, we can iterate:

    YAML::Node doc;    // already parsed
    for(YAML::Iterator it=doc.begin();it!=doc.end();++it) {
        std::string key, value;
        it.first() >> key;
        it.second() >> value;
        std::cout << "Key: " << key << ", value: " << value << std::endl;
    }

Note that dereferencing a map iterator is undefined; instead, use the first and second methods to get the key and value nodes, respectively.

Alternatively, we can pick off the values one-by-one, if we know the keys:

    YAML::Node doc;    // already parsed
    std::string name;
    doc["name"] >> name;
    int age;
    doc["age"] >> age;
    std::cout << "Found entry with name '" << name << "' and age '" << age << "'\n";

One thing to be keep in mind: reading a map by key (as immediately above) requires looping through all entries until we find the right key, which is an O(n) operation. So if you're reading the entire map this way, it'll be O(n^2). For small n, this isn't a big deal, but I wouldn't recommend reading maps with a very large number of entries (>100, say) this way. 

#### A complete example

The following code will parse the example file ``monsters.yaml`` listed above:

    #include "yaml-cpp/yaml.h"
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    
    // our data types
    struct Vec3 {
       float x, y, z;
    };
    
    struct Power {
       std::string name;
       int damage;
    };
    
    struct Monster {
       std::string name;
       Vec3 position;
       std::vector <Power> powers;
    };
    
    // now the extraction operators for these types
    void operator >> (const YAML::Node& node, Vec3& v) {
       node[0] >> v.x;
       node[1] >> v.y;
       node[2] >> v.z;
    }

    void operator >> (const YAML::Node& node, Power& power) {
       node["name"] >> power.name;
       node["damage"] >> power.damage;
    }

    void operator >> (const YAML::Node& node, Monster& monster) {
       node["name"] >> monster.name;
       node["position"] >> monster.position;
       const YAML::Node& powers = node["powers"];
       for(unsigned i=0;i<powers.size();i++) {
          Power power;
          powers[i] >> power;
          monster.powers.push_back(power);
       }
    }
    
    int main()
    {
       std::ifstream fin("monsters.yaml");
       YAML::Parser parser(fin);
       YAML::Node doc;
       parser.GetNextDocument(doc);
       for(unsigned i=0;i<doc.size();i++) {
          Monster monster;
          doc[i] >> monster;
          std::cout << monster.name << "\n";
       }
    
       return 0;
    }

## References 

* [Basic methods for parsing a YAML document](http://code.google.com/p/yaml-cpp/wiki/HowToParseADocument)
