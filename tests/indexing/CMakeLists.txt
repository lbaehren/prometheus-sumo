
## ==============================================================================
##
##  Macro definitions
##
## ==============================================================================

find_program (TAR_EXECUTABLE tar)

macro(prepare_test_dataset varName varSourceArchive varUrl)

  ## Check if the source file is available already
  message (STATUS "Checking for local copy of ${varSourceArchive} ...")
  find_file (varSource
    NAMES ${varSourceArchive}
    PATHS ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    PATH_SUFFIXES data data/tests
    )
  
  if (NOT varSource)
    message (STATUS "No local copy of ${varSourceArchive} - starting download ...")
    file (
      DOWNLOAD ${varUrl} ${CMAKE_CURRENT_BINARY_DIR}/${varSourceArchive}
      )
    ## Set pointer to the file
    set (varSource ${CMAKE_CURRENT_BINARY_DIR}/${varSourceArchive})
  endif (NOT varSource)

  ## Decompose the filename
  get_filename_component (varFilenameExt  ${varSource} EXT     )
  get_filename_component (varFilenameName ${varSource} NAME_WE )
  
  ## Expand the source archive
  message (STATUS "Expanding source archive ${varSourceArchive} ...")
  execute_process(
    COMMAND ${TAR_EXECUTABLE} -xzf ${varSource}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
  
endmacro(prepare_test_dataset)

## ==============================================================================
##
##  Download the test datasets
##
## ==============================================================================


##__________________________________________________________
## Linux kernel sources

set (KERNEL_VERSION_MAJOR  "2")
set (KERNEL_VERSION_MINOR  "6")
set (KERNEL_VERSION_PATCH  "39")
set (KERNEL_VERSION_SERIES "${KERNEL_VERSION_MAJOR}.${KERNEL_VERSION_MINOR}")
set (KERNEL_VERSION        "${KERNEL_VERSION_SERIES}.${KERNEL_VERSION_PATCH}")
set (KERNEL_SOURCE_ARCHIVE "linux-${KERNEL_VERSION}.tar.gz")
set (KERNEL_URL            "ftp://ftp.kernel.org/pub/linux/kernel/v${KERNEL_VERSION_SERIES}/${KERNEL_SOURCE_ARCHIVE}")

prepare_test_dataset (kernel ${KERNEL_SOURCE_ARCHIVE} ${KERNEL_URL})

##__________________________________________________________
## OHSUMED test collection of 348,566 references from MEDLINE

set (OHSUMED_SOURCE_ARCHIVE "t9.filtering.tar.gz")
set (OHSUMED_URL            "http://trec.nist.gov/data/filtering/${OHSUMED_SOURCE_ARCHIVE}")

prepare_test_dataset (ohsumed ${OHSUMED_SOURCE_ARCHIVE} ${OHSUMED_URL})

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
