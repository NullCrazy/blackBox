# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
                          src/main/cpp/AES/aes256.cpp
                          src/main/cpp/AES/aes.cpp
                          src/main/cpp/AES/aes256.cpp
                          src/main/cpp/AES/AESTool.cpp
                          src/main/cpp/AES/zbase64.cpp

                          src/main/cpp/jsonStore/LCJsonStorage.cpp

                          src/main/cpp/json/autolink.h
                          src/main/cpp/json/config.h
                          src/main/cpp/json/features.h
                          src/main/cpp/json/forwards.h
                          src/main/cpp/json/json.h
                          src/main/cpp/json/json_valueiterator.inl
                          src/main/cpp/json/json_batchallocator.h
                          src/main/cpp/json/json_internalarray.inl
                          src/main/cpp/json/json_internalmap.inl
                          src/main/cpp/json/json_reader.cpp
                          src/main/cpp/json/json_value.cpp
                          src/main/cpp/json/json_writer.cpp
                          src/main/cpp/json/reader.h
                          src/main/cpp/json/value.h
                          src/main/cpp/json/writer.h

                          src/main/cpp/cache/LCDataCache.cpp

                          src/main/cpp/imageSteganography/EdecodeBmp.cpp

                          src/main/cpp/LuckinXxaaxxMain/BYUJhIpYsodLgizj.cpp
                          src/main/cpp/native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )