
##____________________________________________________________________
##                                                      scan_csv_stats

add_executable(scan_csv_stats scan_csv_stats.cc)
target_link_libraries (scan_csv_stats libprometheus)

##____________________________________________________________________
##                                                    install_packages

add_executable (install_packages install_packages.cc)
target_link_libraries (install_packages libprometheus)

add_test (install_packages install_packages)
add_test (install_packages_config install_packages --config)

if (APPLE)
  add_test (install_packages_osx    install_packages --osx)
else (APPLE)
  add_test (install_packages_debian install_packages --debian)
  add_test (install_packages_redhat install_packages --redhat)
endif (APPLE)
