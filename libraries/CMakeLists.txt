cmake_minimum_required (VERSION 2.6)
project (Rexeno)

OPTION(XENO "Build Library with super cool option" ON)
OPTION(STATIC "Build Library with super cool option" ON)

set(CMAKE_DEBUG_TYPE=DEBUG)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
include_directories ("${PROJECT_SOURCE_DIR}/configuration")

## Set 3rdParty root
if(NOT DIR3PARTY)
  set(DIR3PARTY "${PROJECT_SOURCE_DIR}/../../3rdParty/linux-ububuntu-12-04-noxeno/target")
endif()



include_directories ("${PROJECT_SOURCE_DIR}/session")
include_directories ("${PROJECT_SOURCE_DIR}/includes")
include_directories ("${PROJECT_SOURCE_DIR}/recorder")
add_subdirectory (configuration)
add_subdirectory (session)
add_subdirectory (driver)
add_subdirectory (recorder)
add_subdirectory (unitTest)
add_subdirectory (interface)
add_subdirectory (CreateSession)
add_executable(Rexeno main.cc)
target_link_libraries (Rexeno configuration)
target_link_libraries (Rexeno session)
target_link_libraries (Rexeno driver)
target_link_libraries (Rexeno recorder)

link_directories(${DIR3PARTY}/lib)
# include_directories(${DIR3PARTY}/include/xenomai)
include_directories(${DIR3PARTY}/include)
if(XENO)
  add_definitions(-DXENO)
  include_directories ("/usr/xenomai/include")
  link_directories ("/usr/xenomai/lib")
  link_libraries ("pthread")
  link_libraries ("native")
  link_libraries ("rt")
  link_libraries ("analogy")
  link_libraries ("rtdm")
  link_libraries ("xenomai")
  if(NOT DIR3PARTY)
    set(DIR3PARTY "${PROJECT_SOURCE_DIR}/../../3rdParty/linux-ububuntu-12-04-xeno/target")
  endif()
endif()

# here we add configuration files
add_custom_command(TARGET Rexeno POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/unitTest/"
        $<TARGET_FILE_DIR:Rexeno>)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "~/.rexeno")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "~/.rexeno/trial_types")
add_custom_command(TARGET Rexeno POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/configFiles/"
        "~/.rexeno")
