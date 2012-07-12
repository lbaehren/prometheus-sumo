
## Parse CSV file with Boost Tokenizer

if (Boost_FOUND)

  ## Compiler instructions
  add_executable(scan_csv_stats scan_csv_stats.cc)
  ## Linker instructions
  target_link_libraries (scan_csv_stats prometheus)

endif ()
