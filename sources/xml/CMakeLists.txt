
if (XERCESC_FOUND)

  include_directories (${XERCESC_INCLUDES})

  add_executable (tPlatformUtils tPlatformUtils.cc)
  target_link_libraries (tPlatformUtils ${XERCESC_LIBRARIES})

else (XERCESC_FOUND)

  message (STATUS "Skipping XML parsing code - missing Xercesc library!")
  
endif (XERCESC_FOUND)