/*!
  \file tEmitting.cc
  \author Lars Baehren
*/

#include <yaml-cpp/yaml.h>

// ==============================================================================
//
//  Test routines
//
// ==============================================================================

//_______________________________________________________________________________
//                                                                    hello_world

//! Emit a simple message
void hello_world ()
{
  std::cout << "\n[tEmitting::hello_world]\n" << std::endl;

  YAML::Emitter out;
  out << "Hello, World!";

  std::cout << "Here's the output YAML:\n" << out.c_str() << std::endl;
}

//_______________________________________________________________________________
//                                                                      emit_list

//! Emit a simple list of elements
void emit_list ()
{
  std::cout << "\n[tEmitting::emit_list]\n" << std::endl;

  YAML::Emitter out;

  /* Assemble the sequence */
  out << YAML::BeginSeq;
  out << "eggs";
  out << "bread";
  out << "milk";
  out << YAML::EndSeq;

  /* Write out the sequence */
  std::cout << out.c_str() << std::endl;
}

//_______________________________________________________________________________
//                                                                       emit_map

void emit_map ()
{
  std::cout << "\n[tEmitting::emit_map]\n" << std::endl;

  YAML::Emitter out;

  /* Assemble the map */
  out << YAML::BeginMap;
  out << YAML::Key << "name";
  out << YAML::Value << "Barack Obama";
  out << YAML::Key << "children";
  out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
  out << YAML::EndMap;

  /* Write the map to standard output */
  std::cout << out.c_str() << std::endl;
}

// ==============================================================================
//
//  Main function
//
// ==============================================================================

//! Main routine of the test program
int main()
{
  hello_world();
  emit_list();
  emit_map();

  return 0;
}
