# -----------------------------------------------------------------

cmake_minimum_required(VERSION 3.18)
project(plugins C CXX)

# -----------------------------------------------------------------

set(curr_dir "${CMAKE_CURRENT_LIST_DIR}")
set(base_dir "${curr_dir}/../")
set(src_dir "${base_dir}/src")
set(inc_dir "${base_dir}/include")
set(ext_dir "${base_dir}/extern")
set(deps_dir "${curr_dir}/deps")
set(mod_dir "${base_dir}/src/modules")

# -----------------------------------------------------------------

string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
if (${build_type} MATCHES "debug")
  set(debug_flag "-debug")
endif()

# -----------------------------------------------------------------

list(APPEND plugins_inc_dirs
  ${inc_dir}
  )

# -----------------------------------------------------------------

macro(plugins_create_test)

  set(options "")
  set(one_value_args NAME LIBS)
  set(multi_value_args SOURCES LABELS)

  cmake_parse_arguments(
    APP
    "${options}"
    "${one_value_args}"
    "${multi_value_args}"
    ${ARGN}
    )

  if (NOT APP_NAME)
    message(FATAL_ERROR "Missing the `NAME` argument.")
  endif()

  # Collect the sources for this test
  set(app_source "${src_dir}/test/test-${APP_NAME}.c")

  # Create name, executable and test.
  set(app_name "test-${APP_NAME}${debug_flag}")
  add_executable(${app_name} ${app_source})
  target_link_libraries(${app_name} ${plugins_libs})
  
  install(TARGETS ${app_name} DESTINATION bin)

  if (plugins_deps)
    add_dependencies(${app_name} ${plugins_deps})
  endif()

endmacro()

# -----------------------------------------------------------------

include_directories(${plugins_inc_dirs})

# -----------------------------------------------------------------

plugins_create_test(NAME "compile")

# -----------------------------------------------------------------

if (UNIX)

  # TEST CASE "A"
  if (TRUE)

    # Static core, run-time linkage module
    add_library(core STATIC ${src_dir}/log.c ${src_dir}/loader.c)
    add_library(encoder MODULE ${src_dir}/module/encoder.c)
    install(TARGETS encoder DESTINATION lib)

    # Create the target.
    add_executable(test-a ${src_dir}/test/test-a.c)
    target_link_options(test-a PRIVATE -rdynamic) # Because we link statically with `core` we need to make the symbols available using the `-rdynamic` option with GCC.
    target_link_libraries(test-a core)
    install(TARGETS test-a DESTINATION bin)

  endif()
  
endif() # UNIX

# -----------------------------------------------------------------
