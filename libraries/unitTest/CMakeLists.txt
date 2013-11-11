include_directories(${DIR3PARTY}/include)
link_directories(${DIR3PARTY}/lib/boost)
link_libraries (glut)
link_libraries (boost_program_options)

add_subdirectory (session)
