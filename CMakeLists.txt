cmake_minimum_required(VERSION 3.15.0)
project(linalg LANGUAGES CXX VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

# Declare all CMake settings
set(${PROJECT_NAME_UPPER}_BUILD_SHARED_LIBRARY ON CACHE BOOL "build shared libraries instead of static ones")
set(${PROJECT_NAME_UPPER}_BUILD_TESTS OFF CACHE BOOL "build testrunner for ${PROJECT_NAME}")

# Language server
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dynamic linking
set(CMAKE_INSTALL_RPATH "$ORIGIN")

# Collect dependencies
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/cie/lib")
find_package(cieutils REQUIRED)
find_package(Eigen3 REQUIRED)

# Build main library
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/packages/*/src/*.cpp")
if (${${PROJECT_NAME_UPPER}_BUILD_SHARED_LIBRARY})
    add_library(${PROJECT_NAME} SHARED ${sources})
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)
else()
    add_library(${PROJECT_NAME} STATIC ${sources})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC cie::cieutils)
target_include_directories(${PROJECT_NAME}
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_include_directories(${PROJECT_NAME} PUBLIC "${EIGEN3_INCLUDE_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC "${EIGEN3_INCLUDE_DIR}/unsupported")

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets LIBRARY DESTINATION "cie/lib")
install(DIRECTORY packages DESTINATION "cie/include" FILES_MATCHING PATTERN "*.hpp")

# Build test executable
if (${PROJECT_NAME_UPPER}_BUILD_TESTS)
    file(GLOB_RECURSE test_sources "${CMAKE_CURRENT_SOURCE_DIR}/packages/*/test/*.cpp")
    list(INSERT test_sources 0 test/${PROJECT_NAME}_testrunner.cpp)

    add_executable(${PROJECT_NAME}_testrunner ${test_sources})
    target_link_libraries(${PROJECT_NAME}_testrunner PRIVATE ${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME}_testrunner PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

# Export
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(TARGETS ${PROJECT_NAME} NAMESPACE cie:: FILE ${PROJECT_NAME}Targets.cmake)
export(PACKAGE ${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}Targets FILE ${PROJECT_NAME}Targets.cmake DESTINATION "cie/lib")
install(EXPORT ${PROJECT_NAME}Targets FILE ${PROJECT_NAME}Targets.cmake DESTINATION "cie/lib/cmake/${PROJECT_NAME}")

# Package
set(CPACK_PACKAGE_VENDOR "")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/readme")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES
    /.git
    /build
    *.gitignore)
include(CPack)

include(CMakePackageConfigHelpers)
configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "cie/lib/cmake/${PROJECT_NAME}")