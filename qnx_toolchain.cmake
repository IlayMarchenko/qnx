# set target system
set(CMAKE_SYSTEM_NAME QNX)

#set(CMAKE_SYSTEM_VERSION 7.0.0)
set(CMAKE_SYSTEM_PROCESSOR x86)

set(arch gcc_ntox86)

# set(BUILD_SHARED_LIBS OFF)
# set(WITH_DLT_SHM_ENABLE ON)
# set(CMAKE_INSTALL_PREFIX "/home/Illia/local")
# set(WITH_DLT_USE_IPv6 OFF)

set(CMAKE_C_COMPILER qcc)
set(CMAKE_C_COMPILER_TARGET ${arch})
set(CMAKE_C_FLAGS "-static -no-pie")

set(CMAKE_CXX_COMPILER QCC)
set(CMAKE_CXX_COMPILER_TARGET ${arch})
set(CMAKE_CXX_FLAGS "-Vgcc_ntox86 -static -no-pie")


# set qnx build flags
# add_definitions("-D_QNX_SOURCE")
# add_definitions("-stdlib=libstdc++")
# add_definitions("-std=c++14")

# set QNX_TARGET
# if (DEFINED ENV{QNX_TARGET})
#     set (QNX_TARGET $ENV{QNX_TARGET})
# else ()
#     message (FATAL_ERROR "NO QNX TARGET ENV DEFINED")
# endif ()

# include c++ library
# include_directories("${QNX_TARGET}/usr/include/c++/5.4.0/")

# search for programs in the build host directories (not necessary)
# SET(CMAKE_FIND_ROOT_PATH ${QNX_TARGET}/${CMAKE_SYSTEM_PROCESSOR})
# SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#
# # set the cmake install prefix to <qnx target path>/usr/local/
# if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT 
# 	OR NOT DEFINED CMAKE_INSTALL_PREFIX)
#   SET(CMAKE_INSTALL_PREFIX ${CMAKE_FIND_ROOT_PATH}/usr/local CACHE PATH "cmake install prefix" FORCE)
# endif()

# =============================================================================

# set(ntoarch x86)
# set(QNX_PROCESSOR x86)

# set (QNX_HOST “~/Desktop/qnx700/host/linux/x86_64”)
# set (QNX_TARGET “~/Desktop/qnx700/target/qnx7”)
#
# set(TOOLCHAIN QNX)
#
# set(CMAKE_ASM_COMPILER qcc -V${arch})
# set(CMAKE_ASM_DEFINE_FLAG "-Wa,--defsym,")
#
# set(CMAKE_RANLIB $ENV{QNX_HOST}/usr/bin/nto${ntoarch}-ranlib
#     CACHE PATH "QNX ranlib Program" FORCE)
# set(CMAKE_AR $ENV{QNX_HOST}/usr/bin/nto${ntoarch}-ar
#     CACHE PATH "QNX qr Program" FORCE)
