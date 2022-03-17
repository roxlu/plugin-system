@echo off

:: ----------------------------------------------------

set curr_dir=%cd%
set base_dir=%curr_dir%/..
set install_dir=%base_dir%/install
set build_dir=build.release
set extern_dir=%base_dir%/extern

:: ----------------------------------------------------

set cmake_generator=Visual Studio 17 2022
set cmake_build_type=Release
set cmake_config=Release
set debug_flag=
set verbose_flag=

:: ----------------------------------------------------

:: Iterate over command line arguments
:argsloop

  if "%1" == "" (
    goto :argsloopdone
  )

  if "%1" == "verbose" (
    set verbose_flag=/verbosity:diagnostic /fl
  )

  if "%1" == "debug" (
   set debug_flag=-debug
   set cmake_build_type=Debug
   set cmake_config=Debug
   set build_dir=build.debug
  )

shift
goto :argsloop
:argsloopdone

:: ----------------------------------------------------

if not exist "%curr_dir%/%build_dir%" mkdir "%curr_dir%/%build_dir%"
if not exist "%install_dir%" mkdir "%install_dir%"

:: ----------------------------------------------------

cd "%curr_dir%/%build_dir%"

@echo on
cmake -G "%cmake_generator%" ^
      -A X64 ^
      -DCMAKE_INSTALL_PREFIX="%install_dir%" ^
      -DCMAKE_VERBOSE_MAKEFILE=On ^
      -DCMAKE_BUILD_TYPE="%cmake_build_type%" ^
      ..

echo Done
if errorlevel 1 goto err

:: ----------------------------------------------------

cmake --build . ^
      --target install ^
      --config "%cmake_config%" ^
      --parallel 12 ^
      -- %verbose_flag% 

if errorlevel 1 goto err

:: ----------------------------------------------------

cd "%install_dir%"
cd bin
test-b

:: ----------------------------------------------------
