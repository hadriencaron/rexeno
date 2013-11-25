# boost
include_directories(${DIR3PARTY}/boost/include)
link_directories(${DIR3PARTY}/boost/lib)


if (STATIC)
  add_library(configuration parser.cc)
else()
  add_library(configuration SHARED parser.cc)
endif()
install_targets(/lib configuration)
install(FILES parser.hh
        DESTINATION /usr/include)
