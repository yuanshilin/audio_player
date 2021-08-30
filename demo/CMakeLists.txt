cmake_minimum_required(VERSION 3.2.0)
project(WAV_DEMO)


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)


set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AudioDevice.cpp)

set(EXAMPLE_APP_NAME "wav-examples")


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
    set(SRC ${SRC}
            ${CMAKE_CURRENT_SOURCE_DIR}/AndroidDevice.cpp)

elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    #	add_definitions("-Wno-invalid-source-encoding")
    add_definitions("-O2")
    set(UNIX_OS true)
    add_definitions("-DLINUX")
    set(SRC ${SRC}
            ${CMAKE_CURRENT_SOURCE_DIR}/LinuxDevice.cpp)

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

if (${UNIX_OS})
    add_definitions(
            "-W"
            "-fPIC"
            "-Wall"
            #            "-Werror"
            #            "-Wshadow"
            "-Wformat"
            "-Wpointer-arith"
            "-D_REENTRANT"
            "-D_USE_FAST_MACRO"
            "-Wno-long-long"
            "-Wuninitialized"
            "-D_POSIX_PTHREAD_SEMANTICS"
            "-DACL_PREPARE_COMPILE"
            "-Wno-unused-parameter"
            "-fexceptions"
    )

    if (!CMAKE_BUILD_TYPE STREQUAL "RELEASE")
        add_definitions("-g")
    endif ()

elseif (${WIN_OS})
    #aux_source_directory(${src}/stdlib/internal lib_src)
endif ()


if (CMAKE_SYSTEM_NAME MATCHES "Android")
    set(exe_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../out/android/bin/${ANDROID_ABI})
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../out/android/lib/${ANDROID_ABI})
else ()
    set(exe_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../out/bin)
    set(lib_output_path ${CMAKE_CURRENT_SOURCE_DIR}/../out/lib)
endif ()

set(EXECUTABLE_OUTPUT_PATH ${exe_output_path})

#
link_libraries(${lib_output_path}/libwav.a ${lib_output_path}/libwavpack.a)


add_executable(${EXAMPLE_APP_NAME} ${SRC})
