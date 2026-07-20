# CMakeList.txt : CMake project for RaylibTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("RaylibTest")

# idk what this does
set(fmt_DIR, "C:\\Users\\bmcca\\Documents\\Github\\coding_badly\\I_Cant_C\\RaylibTest\\vcpkg_installed\\x64-windows\\share\\fmt\\")
find_package(fmt CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (RaylibTest "RaylibTest.cpp" "RaylibTest.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RaylibTest PROPERTY CXX_STANDARD 20)
endif()

# Install Targets
target_link_libraries(HelloWorld PRIVATE fmt::fmt)

# TODO: Add tests if needed.






