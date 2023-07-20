cmake_minimum_required(VERSION 3.13)
project(lang_rt.profile)

set(LIB_PROFILE clang_rt.profile)

add_library(${LIB_PROFILE} STATIC
    InstrProfilingFileOther.c
    ${llvmproject_SOURCE_DIR}/compiler-rt/lib/profile/InstrProfiling.c
    ${llvmproject_SOURCE_DIR}/compiler-rt/lib/profile/InstrProfilingBuffer.c
    ${llvmproject_SOURCE_DIR}/compiler-rt/lib/profile/InstrProfilingInternal.c
    ${llvmproject_SOURCE_DIR}/compiler-rt/lib/profile/InstrProfilingVersionVar.c
    ${llvmproject_SOURCE_DIR}/compiler-rt/lib/profile/InstrProfilingWriter.c
)

# List of include directories
target_include_directories(${LIB_PROFILE} PRIVATE
    ${llvmproject_SOURCE_DIR}/compiler-rt/include
    ${llvmproject_SOURCE_DIR}/compiler-rt/lib/profile
    ${picolibc_SOURCE_DIR}/semihost/
)

install(
    FILES       ${CMAKE_BUILD_PREFIX}/lib${LIB_PROFILE}.a
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT   llvm-toolchain-libs
)
