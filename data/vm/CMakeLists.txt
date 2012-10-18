
find_program (CURL_EXECUTABLE curl
  HINTS ${CMAKE_INSTALL_PREFIX} ${CURL_ROOT_DIR}
)

if (CURL_EXECUTABLE)

  ## Custom target
  add_custom_target (FetchVirtualMachines)

  ## Base URL for the download location of the VirtualMachine images
  set (VM_DOWNLOAD_BASE "http://134.95.11.135/virtualbox")

  foreach (VM_IMAGE
    vm-debian6.ova
    vm-debian7.ova
    vm-ubuntu1004.ova
    vm-ubuntu1204.ova
    vm-windowsxp-ie6.ova
    vm-windowsxp-ie7.ova
    vm-windowsxp-ie8.ova
    )

    add_custom_command (
      TARGET FetchVirtualMachines
      POST_BUILD
      COMMAND ${CURL_EXECUTABLE} -o ${VM_IMAGE} ${VM_DOWNLOAD_BASE}/${VM_IMAGE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Downloading VirtualMachine image ${VM_IMAGE} ..."
    )

    set_property (DIRECTORY
      APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/${VM_IMAGE}
      )

  endforeach (VM_IMAGE)

endif (CURL_EXECUTABLE)
