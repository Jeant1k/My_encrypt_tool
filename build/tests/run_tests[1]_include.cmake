if(EXISTS "/home/jeantik/programs/my_encrypt_tool/build/tests/run_tests[1]_tests.cmake")
  include("/home/jeantik/programs/my_encrypt_tool/build/tests/run_tests[1]_tests.cmake")
else()
  add_test(run_tests_NOT_BUILT run_tests_NOT_BUILT)
endif()
