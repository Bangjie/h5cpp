set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS ${dir}/hdf5.hpp)
install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp)

set(h5cpp_headers ${HEADERS})
set(h5cpp_sources )
add_subdirectory(core)
add_subdirectory(attribute)
add_subdirectory(dataspace)
add_subdirectory(datatype)
add_subdirectory(error)
add_subdirectory(file)
add_subdirectory(filter)
add_subdirectory(node)
add_subdirectory(property)
add_subdirectory(utilities)

add_doxygen_source_deps(${h5cpp_headers})

add_library(h5cpp SHARED
  ${h5cpp_sources}
  ${h5cpp_headers}
  )

add_doxygen_source_deps(${h5cpp_headers})

target_compile_definitions(h5cpp PRIVATE DLL_BUILD)
set(H5CPP_LINKS Boost::filesystem Boost::system ${MPI_CXX_LIBRARIES})

#
# remove the absolute path from the library name
#
set(H5CPP_INTERFACE_LIBS)
set(H5CPP_PRIVATE_LIBS ${HDF5_LIBRARIES})
foreach(HDF5_LIBRARY ${HDF5_LIBRARIES})
    get_filename_component(LIB_NAME ${HDF5_LIBRARY} NAME)
    list(APPEND  H5CPP_INTERFACE_LIBS ${LIB_NAME})  
endforeach()


target_include_directories(h5cpp
  PRIVATE ${PROJECT_SOURCE_DIR}/src
  PRIVATE ${HDF5_INCLUDE_DIRS}
  PUBLIC ${MPI_CXX_INCLUDE_PATH}
  INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

#
# THIS IS BAD
# NEED TO GET RID OF THIS
if (WITH_MPI)
  target_compile_definitions(h5cpp PUBLIC WITH_MPI)
endif ()

set_target_properties(h5cpp
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SO_VERSION 0
  CXX_STANDARD_REQUIRED ON
  OUTPUT_NAME h5cpp
  )

enable_coverage(h5cpp)

target_link_libraries(h5cpp
  PUBLIC ${H5CPP_LINKS}
  PRIVATE ${COVERAGE_LIBRARIES} ${H5CPP_PRIVATE_LIBS}
  INTERFACE ${H5CPP_INTERFACE_LIBS})

include(GNUInstallDirs) #Required for CMAKE_INSTALL_XXX

install(TARGETS h5cpp
  EXPORT h5cpp_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT runtime
  )

install(EXPORT h5cpp_targets
  DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
  COMPONENT development)



