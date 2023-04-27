OPTION(LLVM_TOOLCHAIN_CONTRIB_PROFILE "Profiling Support" Off)


include(contrib/profiling/clang_rt.profile.cmake)
include(contrib/rtt/rtt.cmake)


function(add_contrib_libs directory variant target_triple flags libc_target)
    get_runtimes_flags("${directory}" "${flags}")
    
    if(LLVM_TOOLCHAIN_CONTRIB_PROFILE)
        add_contrib_lib_profile(${directory} ${variant} ${target_triple} ${flags} ${libc_target})
    endif()
    if(LLVM_TOOLCHAIN_CONTRIB_RTT)
        add_contrib_lib_rtt(${directory} ${variant} ${target_triple} ${flags} ${libc_target})
    endif()
endfunction()
