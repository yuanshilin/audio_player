# libwavpack
cmake_minimum_required(VERSION 3.13.0)
project(wavpack)



add_definitions("-fPIC")

#string(TOUPPER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME)
if (CMAKE_SYSTEM_NAME MATCHES "Android")
    # xxx: -flto can't be used on NDK with gnustl_shared
    if (ANDROID_STL MATCHES "gnustl_shared")
        add_definitions("-Oz -g -DHAVE_NO_ATEXIT")
    else ()
        add_definitions("-O3 -flto")
    endif ()

    add_definitions("-DANDROID")
    add_definitions("-Wno-unused-command-line-argument")
    #	add_definitions("-Wno-invalid-source-encoding")
    add_definitions("-fdata-sections -ffunction-sections")
    # string(APPEND CMAKE_CXX_FLAGS "-Qunused-arguments")
    set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    #	add_definitions("-Wno-invalid-source-encoding")
    add_definitions("-O2")
    set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_definitions("-Wno-invalid-source-encoding")
    add_definitions("-fdata-sections -ffunction-sections")
    add_definitions("-flto")
    add_definitions("-Os")
    set(UNIX_OS true)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE ws2_32.lib")
    set(WIN_OS true)
else ()
    message(FATAL_ERROR "unknown CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
endif ()

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

# 设置静态库的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${lib_output_path})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${lib_output_path})

# 设置动态库的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${lib_output_path})

#add_library(wavpack_so SHARED ${third_wavpack_src})
add_library(wavpack_static STATIC ${third_wavpack_src})


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

target_include_directories(wavpack_static PRIVATE ${LIBNYQUIST_ROOT}/wavpack/include)

if (MSVC_IDE)
    set_target_properties(wavpack_static PROPERTIES IMPORT_PREFIX "../..")
endif()

set_target_properties(wavpack_static
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




