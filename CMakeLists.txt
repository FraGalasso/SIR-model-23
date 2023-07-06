cmake_minimum_required(VERSION 3.16)
project(sir VERSION 1.1.0)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

string(APPEND CMAKE_CXX_FLAGS_RELEASE " -Wall -Wextra")

string(APPEND CMAKE_CXX_FLAGS_RELEASE " -fsanitize=address,undefined")
string(APPEND CMAKE_EXE_LINKER_FLAGS_RELEASE " -fsanitize=address,undefined")

# executable for first part
add_executable(sir first_part.cpp sir.cpp)

# finding sfml packages
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

# executable for second part
add_executable(visual second_part.cpp person.cpp population.cpp)

# linking
target_link_libraries(visual sfml-graphics sfml-window)

# testing
if (BUILD_TESTING)

  add_executable(sir.t sir.test.cpp sir.cpp)
  add_test(NAME sir.t COMMAND sir.t)

  add_executable(evolve.t evolve.test.cpp sir.cpp)
  add_test(NAME evolve.t COMMAND evolve.t)

  add_executable(vaccination.t vaccination.test.cpp person.cpp population.cpp)
  target_link_libraries(vaccination.t sfml-graphics)
  add_test(NAME vaccination.t COMMAND vaccination.t)

  add_executable(infection.t infection.test.cpp person.cpp population.cpp)
  target_link_libraries(infection.t sfml-graphics)
  add_test(NAME infection.t COMMAND infection.t)

endif()

