
set (KERNEL_VERSION_MAJOR  "2")
set (KERNEL_VERSION_MINOR  "6")
set (KERNEL_VERSION_PATCH  "39")
set (KERNEL_VERSION_SERIES "${KERNEL_VERSION_MAJOR}.${KERNEL_VERSION_MINOR}")
set (KERNEL_VERSION        "${KERNEL_VERSION_SERIES}.${KERNEL_VERSION_PATCH}")
set (KERNEL_SOURCE_ARCHIVE "linux-${KERNEL_VERSION}.tar.gz")
set (KERNEL_URL            "ftp://ftp.kernel.org/pub/linux/kernel/v${KERNEL_VERSION_SERIES}/${KERNEL_SOURCE_ARCHIVE}")

##__________________________________________________________
## Check for the test scripts and test data

find_file (ferret_test_indexer_rb indexer.rb
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
  )

find_file (KERNEL_SOURCE
  NAMES ${KERNEL_SOURCE_ARCHIVE}
  PATHS ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
  PATH_SUFFIXES data test
  )

if (NOT KERNEL_SOURCE)
  set (KERNEL_SOURCE ${KERNEL_URL})
endif (NOT KERNEL_SOURCE)

##__________________________________________________________
## Get the data and process them

ExternalProject_Add (ferret_data_kernel
  PREFIX ${PROJECT_BINARY_DIR}
  DOWNLOAD_DIR download
  SOURCE_DIR source
  URL ${KERNEL_SOURCE}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${RUBY_EXECUTABLE} ${ferret_test_indexer_rb} ${CMAKE_CURRENT_BINARY_DIR}/source
  INSTALL_COMMAND ""
  )
