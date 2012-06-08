
## ==============================================================================
##
##  Download the test datasets
##
## ==============================================================================

add_test (get_test_datasets ${CMAKE_COMMAND} -D PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/TestGetDatasets.cmake)

## ==============================================================================
##
##  Run the tests
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

add_test (ferret_index_kernel ${RUBY_EXECUTABLE} ${ferret_test_indexer_rb} ${CMAKE_CURRENT_BINARY_DIR}/source ${CMAKE_CURRENT_BINARY_DIR}/ferret-index)

##__________________________________________________________
## Test: Search the generated index

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
