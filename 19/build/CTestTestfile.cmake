# CMake generated Testfile for 
# Source directory: /mnt/c/Users/qp/programming/labs-1/19
# Build directory: /mnt/c/Users/qp/programming/labs-1/19/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_card]=] "/mnt/c/Users/qp/programming/labs-1/19/build/test_card")
set_tests_properties([=[test_card]=] PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;47;add_test;/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;51;add_atm_test;/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;0;")
add_test([=[test_account]=] "/mnt/c/Users/qp/programming/labs-1/19/build/test_account")
set_tests_properties([=[test_account]=] PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;47;add_test;/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;52;add_atm_test;/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;0;")
add_test([=[test_journal]=] "/mnt/c/Users/qp/programming/labs-1/19/build/test_journal")
set_tests_properties([=[test_journal]=] PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;47;add_test;/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;53;add_atm_test;/mnt/c/Users/qp/programming/labs-1/19/CMakeLists.txt;0;")
subdirs("_deps/doctest-build")
