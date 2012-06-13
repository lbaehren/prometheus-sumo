
## ==============================================================================
##
##  DESCRIPTION:
##
##   CMake script to handle the download of test datasets.
##
##  USAGE:
##
##   cmake -c -DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}
##
## ==============================================================================

## ==============================================================================
##
##  Macro definitions
##
## ==============================================================================

macro(get_test_dataset varName varSourceArchive varUrl)

  ##________________________________________________________
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

  ##________________________________________________________
  ## Decompose the filename

  set (varTargetDir ${CMAKE_CURRENT_BINARY_DIR}/data_${varName})
  get_filename_component (varFilenameName ${varSource} NAME_WE )
  get_filename_component (varFilenameExt  ${varSource} EXT     )
  
  ##________________________________________________________
  ## Check on target directory into which the data are expanded

  if (NOT EXISTS ${varTargetDir})
    message (STATUS "Creating directory ${varTargetDir}")
    file(MAKE_DIRECTORY ${varTargetDir})
  endif (NOT EXISTS ${varTargetDir})
  
  ##________________________________________________________
  ## Expand the source archive

  message (STATUS "Expanding source archive ${varSourceArchive} ...")
  execute_process(
    COMMAND tar -xzf ${varSource}
    WORKING_DIRECTORY ${varTargetDir}
    )
  
  ##________________________________________________________
  ## Reset variables

  unset (varSource)
  
endmacro(get_test_dataset)

## ==============================================================================
##
##  Download instructions
##
## ==============================================================================

##__________________________________________________________
## Linux kernel sources

set (KERNEL_VERSION_SERIES "2.6")
set (KERNEL_VERSION_PATCH  "39")
set (KERNEL_VERSION        "${KERNEL_VERSION_SERIES}.${KERNEL_VERSION_PATCH}")
set (KERNEL_SOURCE_ARCHIVE "linux-${KERNEL_VERSION}.tar.gz")
set (KERNEL_URL            "ftp://ftp.kernel.org/pub/linux/kernel/v${KERNEL_VERSION_SERIES}/${KERNEL_SOURCE_ARCHIVE}")

get_test_dataset (kernel ${KERNEL_SOURCE_ARCHIVE} ${KERNEL_URL})

##__________________________________________________________
## OHSUMED test collection of 348,566 references from MEDLINE

set (OHSUMED_SOURCE_ARCHIVE "t9.filtering.tar.gz")
set (OHSUMED_URL            "http://trec.nist.gov/data/filtering/${OHSUMED_SOURCE_ARCHIVE}")

get_test_dataset (ohsumed ${OHSUMED_SOURCE_ARCHIVE} ${OHSUMED_URL})

##__________________________________________________________
## Project Gutenberg EBook of Ulysses, by James Joyce

set (ULYSSES_SOURCE_ARCHIVE "pg4300.txt")
set (ULYSSES_URL            "http://www.gutenberg.org/cache/epub/4300/${ULYSSES_SOURCE_ARCHIVE}")

get_test_dataset (ulysses ${ULYSSES_SOURCE_ARCHIVE} ${ULYSSES_URL})
