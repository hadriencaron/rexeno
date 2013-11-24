include_directories(${DIR3PARTY}/boost/include/boost)
link_directories(${DIR3PARTY}/boost/lib)
# link_libraries (glut)
link_libraries (boost_program_options)

add_subdirectory (session)
