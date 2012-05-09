
file (GLOB varTestsRuby Test*.rb)

foreach (varTest ${varTestsRuby})
  ## remove file extension
  get_filename_component (varFilename ${varTest} NAME_WE)
  ## register the test
  add_test (${varFilename} ${RUBY_EXECUTABLE} ${varTest})
endforeach (varTest)
