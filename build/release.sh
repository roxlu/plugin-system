#!/bin/bash

#  ---------------------------------------------------------------
#
#                       ██████╗  ██████╗ ██╗  ██╗██╗     ██╗   ██╗
#                       ██╔══██╗██╔═══██╗╚██╗██╔╝██║     ██║   ██║
#                       ██████╔╝██║   ██║ ╚███╔╝ ██║     ██║   ██║
#                       ██╔══██╗██║   ██║ ██╔██╗ ██║     ██║   ██║
#                       ██║  ██║╚██████╔╝██╔╝ ██╗███████╗╚██████╔╝
#                       ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚═════╝ 
#
#                                                    www.roxlu.com
#                                            www.twitter.com/roxlu
#  
#  ---------------------------------------------------------------

d="${PWD}"
build_dir="${d}/build"
base_dir="${d}/../"
inst_dir="${base_dir}/install"

cmake_build_type="Release"
cmake_generator="Ninja"
cmake_generator="Unix Makefiles"
build_type="release"

# ----------------------------------------------------

for var in "$@"
do
    if [ "${var}" = "debug" ] ; then
        cmake_build_type="Debug"
        build_type="debug"
        debug_flag="-debug"
        debugger="gdb -ex \"handle SIGINT print nostop pass\" --args  "
    fi
done

# ----------------------------------------------------

build_dir="${build_dir}.${build_type}"

if [ ! -d "${build_dir}" ] ; then
    mkdir "${build_dir}"
fi

# ----------------------------------------------------
# P R O J E C T 
# ----------------------------------------------------

cd "${build_dir}"
cmake -DCMAKE_INSTALL_PREFIX="${inst_dir}" \
      -DCMAKE_BUILD_TYPE="${cmake_build_type}" \
      -DCMAKE_VERBOSE_MAKEFILE=TRUE \
      -G "${cmake_generator}" \
      ..

if [ $? -ne 0 ] ; then
    echo "Failed to configure."
    exit 1
fi

cd "${build_dir}"
cmake --build . \
      --target install \
      --parallel $(nproc)

if [ $? -ne 0 ] ; then
    echo "Failed to build."
    exit 2
fi

# ----------------------------------------------------
