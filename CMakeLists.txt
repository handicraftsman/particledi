cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(ParticleDI VERSION 0.3.1 LANGUAGES CXX)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX /usr/ CACHE PATH "Default install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

set(CMAKE_CXX_STANDARD 11)


add_library(particledi SHARED particledi.cpp)

add_executable(pdi-test test.cpp)
target_link_libraries(pdi-test particledi)


configure_file(${CMAKE_SOURCE_DIR}/particledi.pc.in ${CMAKE_BINARY_DIR}/particledi.pc)
install(FILES ${CMAKE_BINARY_DIR}/particledi.pc DESTINATION lib/pkgconfig)


install(
  TARGETS particledi
  LIBRARY DESTINATION lib
)

install(FILES particledi.hpp DESTINATION include)
