
#include <yaml-cpp/yaml.h>

// ==============================================================================
//
//  Test routines
//
// ==============================================================================

//_______________________________________________________________________________
//                                                                    hello_world

void hello_world ()
{
  YAML::Emitter out;
  out << "Hello, World!";
  
  std::cout << "Here's the output YAML:\n" << out.c_str(); // prints "Hello, World!"
}

//_______________________________________________________________________________
//                                                                      emit_list

void emit_list ()
{
  YAML::Emitter out;
  out << YAML::BeginSeq;
  out << "eggs";
  out << "bread";
  out << "milk";
  out << YAML::EndSeq;
}

//_______________________________________________________________________________
//                                                                       emit_map

void emit_map ()
{
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "name";
  out << YAML::Value << "Barack Obama";
  out << YAML::Key << "children";
  out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
  out << YAML::EndMap;
}

// ==============================================================================
//
//  Main function
//
// ==============================================================================

int main()
{
  hello_world();
  emit_list();
  emit_map();
  
  return 0;
}
