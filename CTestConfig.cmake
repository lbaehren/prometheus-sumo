## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.

set (CTEST_PROJECT_NAME       "prometheus-sumo" )
set (CTEST_NIGHTLY_START_TIME "01:00:00 UTC"    )
set (CTEST_TESTING_TIMEOUT    "3600"            )
set (CTEST_DROP_METHOD        "http"            )
set (CTEST_DROP_SITE          "my.cdash.org"    )
set (CTEST_DROP_LOCATION      "/submit.php?project=prometheus-sumo")
set (CTEST_DROP_SITE_CDASH    TRUE )
