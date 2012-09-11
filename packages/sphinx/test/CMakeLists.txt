
## ==============================================================================
##
##  The test below essentially wraps the various steps described in
##
##    https://github.com/zooie/opensearch
##
##  In essence the test utilizes the OHSUMED test collection of 348,566
##  references from MEDLINE, the on-line medical information database, consisting
##  of titles and/or abstracts from 270 medical journals over a five-year
##  period (1987-1991).
##
## ==============================================================================

##__________________________________________________________
## Configure Python script to use correct paths

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/create_flat.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/create_flat.py
  )

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/create_queries.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/create_queries.py
  )

# Generates build.xml for sphinx indexing
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/create_build_xml.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/create_build_xml.py
  )

# Configuration file for Sphinx
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/sphinx.conf.in
  ${CMAKE_CURRENT_BINARY_DIR}/sphinx.conf
  )

##__________________________________________________________
## Download and pre-process data to run the tests with

ExternalProject_Add (sphinx_data_ohsumed
  PREFIX ${PROJECT_BINARY_DIR}
  DOWNLOAD_DIR download
  SOURCE_DIR source
  URL http://trec.nist.gov/data/filtering/t9.filtering.tar.gz
  CONFIGURE_COMMAND python ${CMAKE_CURRENT_BINARY_DIR}/create_flat.py
  BUILD_COMMAND python ${CMAKE_CURRENT_BINARY_DIR}/create_queries.py
  INSTALL_COMMAND python ${CMAKE_CURRENT_BINARY_DIR}/create_build_xml.py
  ## Testing instructions
  TEST_AFTER_INSTALL 1
  TEST_COMMAND ${CMAKE_INSTALL_PREFIX}/bin/indexer --config ${CMAKE_CURRENT_BINARY_DIR}/sphinx.conf medindex
  )

add_dependencies (sphinx_data_ohsumed sphinx)

##__________________________________________________________
## Testing

add_test (sphinx_indexer ${CMAKE_INSTALL_PREFIX}/bin/indexer --config ${CMAKE_CURRENT_BINARY_DIR}/sphinx.conf medindex)
