cmake_minimum_required(VERSION 3.16)
project(sir VERSION 1.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

# eseguibile principale (prima il nome dell'eseguibile finale e poi il file da compilare)
add_executable(sir first_part.cpp sir.cpp)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(visual second_part.cpp person.cpp population.cpp)

target_link_libraries(visual sfml-graphics)

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
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

