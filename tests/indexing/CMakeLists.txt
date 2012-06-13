
## ==============================================================================
##
##  Download the test datasets
##
## ==============================================================================

add_test (get_test_datasets ${CMAKE_COMMAND} -D PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/TestGetDatasets.cmake)

## ==============================================================================
##
##  Tests using Ferret search engine
##
## ==============================================================================

find_file (ferret_test_indexer_rb ferret_indexer.rb
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
  )

find_file (ferret_test_search_rb ferret_search.rb
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
  )

##__________________________________________________________
## Test: Index the sources of the Linux kernel

add_test (ferret_index_kernel ${RUBY_EXECUTABLE} ${ferret_test_indexer_rb} ${CMAKE_CURRENT_BINARY_DIR}/data_kernel ${CMAKE_CURRENT_BINARY_DIR}/ferret-index)

##__________________________________________________________
## Tests: Search the generated index

foreach (ferretSearchTerm
    net
    skb
    x86
    linux
    Linus
    )

  add_test (ferret_search_kernel_${ferretSearchTerm} ${RUBY_EXECUTABLE} ${ferret_test_search_rb} ${ferretSearchTerm} ${CMAKE_CURRENT_BINARY_DIR}/ferret-index)

  set_tests_properties(ferret_search_kernel_${ferretSearchTerm}
    PROPERTIES
    DEPENDS ferret_index_kernel
    )

endforeach (ferretSearchTerm)

## ==============================================================================
##
##  Tests using Sphinx search engine
##
## ==============================================================================

##__________________________________________________________
## Configure Python script to use correct paths

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/sphinx_flat.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/sphinx_flat.py
  )

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/sphinx_queries.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/sphinx_queries.py
  )

# Generates build.xml for sphinx indexing
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/sphinx_build_xml.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/sphinx_build_xml.py
  )

# Configuration file for Sphinx
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/sphinx.conf.in
  ${CMAKE_CURRENT_BINARY_DIR}/sphinx.conf
  )

##__________________________________________________________
## Test preparation

add_test (sphinx_flat      python ${CMAKE_CURRENT_BINARY_DIR}/sphinx_flat.py      )
add_test (sphinx_queries   python ${CMAKE_CURRENT_BINARY_DIR}/sphinx_queries.py   )
add_test (sphinx_build_xml python ${CMAKE_CURRENT_BINARY_DIR}/sphinx_build_xml.py )

set_tests_properties (sphinx_flat
  PROPERTIES
  DEPENDS get_test_datasets
  )

set_tests_properties (sphinx_queries
  PROPERTIES
  DEPENDS sphinx_flat
  )

set_tests_properties (sphinx_build_xml
  PROPERTIES
  DEPENDS sphinx_queries
  )

##__________________________________________________________
## Run the tests

