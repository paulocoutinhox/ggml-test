# project
cmake_minimum_required(VERSION 3.20.0)
project(sample LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# policies
cmake_policy(SET CMP0054 NEW) # only interpret if() arguments as variables or keywords when unquoted
cmake_policy(SET CMP0076 NEW) # target_sources() command converts relative paths to absolute
set(CMAKE_POLICY_DEFAULT_CMP0091 NEW) # msvc runtime library flags are selected by an abstraction
set(CMAKE_POLICY_DEFAULT_CMP0135 NEW) # set the timestamps of all extracted contents to the time of the extraction

# output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin") # .exe and .dll
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "bin") # .exe and .dll
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "bin") # .exe and .dll

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib") # .so and .dylib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "lib") # .so and .dylib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "lib") # .so and .dylib

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib") # .lib and .a
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "lib") # .lib and .a
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "lib") # .lib and .a

# setup all vendors
add_subdirectory(whisper)

# target
set(MY_ALL_FILES main.cpp ${MY_INC_FILES} ${MY_SRC_FILES})
add_library(${PROJECT_NAME} SHARED "${MY_ALL_FILES}")

target_include_directories(${PROJECT_NAME} PUBLIC whisper)

set_target_properties(${PROJECT_NAME} PROPERTIES
    FRAMEWORK TRUE
    FRAMEWORK_VERSION A
    MACOSX_FRAMEWORK_IDENTIFIER "com.my.library"
    VERSION 1.0.0 # "current version" in semantic format in Mach-O binary file
    SOVERSION 1 # "compatibility version" in semantic format in Mach-O binary file
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
    XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH YES
    XCODE_ATTRIBUTE_SKIP_INSTALL NO
    XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.my.library"
    XCODE_ATTRIBUTE_DEFINES_MODULE YES
    XCODE_ATTRIBUTE_BUILD_LIBRARY_FOR_DISTRIBUTION YES
    MACOSX_FRAMEWORK_BUNDLE_VERSION "1.0.0" # machine readable
    MACOSX_FRAMEWORK_SHORT_VERSION_STRING "1" # user visible
)

find_library(FOUNDATION_LIBRARY Foundation REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${FOUNDATION_LIBRARY})

find_library(ACCELERATE_FRAMEWORK Accelerate REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${ACCELERATE_FRAMEWORK})

find_library(METAL_FRAMEWORK Metal REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${METAL_FRAMEWORK})

find_library(METALKIT_FRAMEWORK MetalKit REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${METALKIT_FRAMEWORK})

target_link_libraries(${PROJECT_NAME} PRIVATE whisper)
