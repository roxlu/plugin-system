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
base_dir="${d}/../"
inst_dir="${base_dir}/install"
build_dir="${d}/build"
build_type="release"
debugger=""
debug_flag=""

# ----------------------------------------------------

./release.sh "$@"
if [ $? -ne 0 ] ; then
    echo "Failed to build."
    exit 1
fi

# ----------------------------------------------------

for var in "$@"
do
    if [ "${var}" = "debug" ] ; then
        debug_flag="-debug"
        build_type="debug"
        debugger="gdb -ex \"handle SIGINT print nostop pass\" --args  "
    fi
done

build_dir="${build_dir}.${build_type}"

# ----------------------------------------------------

export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${inst_dir}/lib/"

cd "${inst_dir}/bin/"
#${debugger} ./test-compile${debug_flag}
${debugger} ./test-a${debug_flag}

# ----------------------------------------------------
