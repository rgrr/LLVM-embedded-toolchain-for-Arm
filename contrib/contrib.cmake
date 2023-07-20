OPTION(LLVM_TOOLCHAIN_CONTRIB_PROFILE "Profiling Support" 1)
OPTION(LLVM_TOOLCHAIN_CONTRIB_RTT     "RTT Support"       1)


include(contrib/profiling/clang_rt.profile.cmake)
include(contrib/rtt/rtt.cmake)


function(add_contrib_libs directory variant target_triple flags test_executor libc_target)
    get_runtimes_flags("${directory}" "${flags}")

    if(LLVM_TOOLCHAIN_CONTRIB_PROFILE)
        add_contrib_lib_profile(${directory} ${variant} ${target_triple} ${flags} ${test_executor} ${libc_target})
    endif()
    if(LLVM_TOOLCHAIN_CONTRIB_RTT)
        add_contrib_lib_rtt(${directory} ${variant} ${target_triple} ${flags} ${test_executor} ${libc_target})
    endif()
endfunction()
