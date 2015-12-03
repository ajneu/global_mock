cmake_minimum_required(VERSION 3.2)
project(gmock_demo)




###########
# Debug or Release
###########
if (NOT CMAKE_BUILD_TYPE)
  ## set default to Debug
  set(CMAKE_BUILD_TYPE Debug)  # override with -DCMAKE_BUILD_TYPE=Release
  message("==> CMAKE_BUILD_TYPE empty. Changing it to Debug.")
else()
  message("==> CMAKE_BUILD_TYPE == ${CMAKE_BUILD_TYPE}.")
endif()

## https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html
## During Debug, use debug version of libstdc++ (asserts on access to invalid iterators, etc!)
if (CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
endif()


###########
# Warnings
###########
if (CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-unused-variable")        # suppress
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations") # suppress
endif ()




##############
# C++ Standard
##############
#set(CMAKE_CXX_STANDARD   11)
set(CMAKE_CXX_EXTENSIONS OFF)




##############
# GMock
##############
# Download gtest_gmock at configure time
include(cmake/add_dl_project.cmake)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # see https://www.johnlamp.net/cmake-tutorial-4-libraries-and-subdirectories.html
  # see http://stackoverflow.com/a/11921648
  #
  # force this option to ON so that Google Test will use /MD instead of /MT
  # /MD is now the default for Visual Studio, so it should be our default, too
  option(gtest_force_shared_crt
    "Use shared (DLL) run-time lib even when Google Test is built as static lib."
    ON)
endif()

add_dl_project(
  PROJ     gtest_gmock
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master # Git branch name, commit id or tag
  
  # URL          https://googletest.googlecode.com/files/gtest-1.7.0.zip
  # URL_HASH     SHA1=f85f6d2481e2c6c4a18539e391aa4ea8ab0394af
  
  EXCLUDE_FROM_ALL
  INCLUDE_DIRS   googlemock/include googletest/include
  )





##############
# Build
##############
set(src    main.cpp test_printer.cpp)
set(target mytest)

add_executable(      ${target}  ${src})
target_link_libraries(${target}  gmock ${libs})



##############
# Test (run:   make test)
##############
enable_testing()
string(REPLACE "${CMAKE_SOURCE_DIR}/" "" PATH_TO_TEST "${CMAKE_CURRENT_LIST_DIR}/${target}")
add_test(NAME                          ${PATH_TO_TEST}
         COMMAND                       ${target})
