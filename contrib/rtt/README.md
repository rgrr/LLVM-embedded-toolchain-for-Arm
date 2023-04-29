# RTT

**Note that RTT support is experimental.**

This add-on enables RTT support for embedded Arm targets.  RTT uses the files provided by Segger on target side.
On host side either tooling like pyOCD or OpenOCD or the debug probe like YaPicoprobe fetch the RTT data from the target.


## Building librtt*

Building the RTT libraries is controlled with the **LLVM_TOOLCHAIN_CONTRIB_RTT** switch on cmake
invocation.  To include the profiling library use:


```bash
# "cd" into build directory (one level below LLVM-embedded-toolchain-for-Arm)
cmake .. -GNinja -DFETCHCONTENT_QUIET=OFF -DLLVM_TOOLCHAIN_CONTRIB_RTT=ON
ninja llvm-toolchain
ninja package-llvm-toolchain
```

or with less effort:

```bash
# "cd" into build directory (one level below LLVM-embedded-toolchain-for-Arm)
cmake .. -GNinja -DLLVM_TOOLCHAIN_CONTRIB_RTT=ON -DFETCHCONTENT_FULLY_DISCONNECTED=ON -DLLVM_TOOLCHAIN_LIBRARY_VARIANTS="aarch64;armv6m_soft_nofp"
ninja llvm-toolchain
ninja package-llvm-toolchain
```

If enabled, the libraries will be built for all enabled target architectures.  After installation, the library
will be placed in the same location as `libclang_rt.builtins.a`, i.e. `$(SYSROOT)/lib`.


## What's included?

Two libraries are built:

* `librtt.a` - includes only the Segger files
* `librtt_stdio.a` - includes additionally some setup so that `printf()` and `getchar()` (i.e. stdio) are redirected
  to/from RTT
* header files `SEGGER/Config/SEGGER_RTT_Conf.h` and `SEGGER/RTT/SEGGER_RTT.h`.


## Static Configuration

Static configuration is contained in `SEGGER/Config/SEGGER_RTT_Conf.h`:

* three up/down channels
* console up (target -> host) buffer: 1024 bytes
* console down (target <- host): 16 bytes
* buffer size for `SEGGER_RTT_printf()`: 64 bytes
* default mode for console channel is `SEGGER_RTT_MODE_NO_BLOCK_SKIP`


## TODO

* how to setup the buffer dynamically?  How is it done with heap assignment?
* buffer perhaps with weak assignment?
