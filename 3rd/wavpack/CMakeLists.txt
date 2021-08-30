# libwavpack
cmake_minimum_required(VERSION 3.13.0)
project(wavpack)

if(MSVC)
    # Disable warning C4996 regarding fopen(), strcpy(), etc.
    _add_define("_CRT_SECURE_NO_WARNINGS")

    # Disable warning C4996 regarding unchecked iterators for std::transform,
    # std::copy, std::equal, et al.
    _add_define("_SCL_SECURE_NO_WARNINGS")

    # Make sure WinDef.h does not define min and max macros which
    # will conflict with std::min() and std::max().
    _add_define("NOMINMAX")
endif()

add_definitions(${_NQR_CXX_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${_NQR_CXX_FLAGS} ${CMAKE_CXX_FLAGS}")

file(GLOB third_wavpack_src "${CMAKE_CURRENT_SOURCE_DIR}/src/*")


if (CMAKE_SYSTEM_NAME MATCHES "Android")
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../../out/android/lib/${ANDROID_ABI})
else ()
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../../out/lib)
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${lib_output_path})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${lib_output_path})

add_library(wavpack STATIC ${third_wavpack_src})

#set_cxx_version(libwavpack)
#_set_compile_options(libwavpack)

if (WIN32)
    _disable_warning(181)
    _disable_warning(111)
    _disable_warning(4267)
    _disable_warning(4996)
    _disable_warning(4244)
    _disable_warning(4701)
    _disable_warning(4702)
    _disable_warning(4133)
    _disable_warning(4100)
    _disable_warning(4127)
    _disable_warning(4206)
    _disable_warning(4312)
    _disable_warning(4505)
    _disable_warning(4365)
    _disable_warning(4005)
    _disable_warning(4013)
    _disable_warning(4334)
    _disable_warning(4703)
endif()

target_include_directories(wavpack PRIVATE ${LIBNYQUIST_ROOT}/wavpack/include)

if (MSVC_IDE)
    set_target_properties(wavpack PROPERTIES IMPORT_PREFIX "../..")
endif()

set_target_properties(wavpack
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

#set_target_properties(libwavpack PROPERTIES OUTPUT_NAME_DEBUG libwavpack_d)

#install(TARGETS libwavpack
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib
#        RUNTIME DESTINATION bin)
#
#install (TARGETS libwavpack DESTINATION lib)




