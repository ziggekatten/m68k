## Toolchains

Instead of messing up your local linux install or VM's, usage of containers is an pragmatic way for running toolchains.
Several options exists, and this repo have currently three different ones to pick from. Two versions of LLVM for future use of zig and/or rust instead of C.
Third option is to use the toolchan created by: https://rosco-m68k.com/ 


- Dockerfile.15: LLVM 1.15.x build with m68k support. To be used with zig
- Dockerfile.16: LLVM 1.16.x build with m68k support. To be used with rust
- Dockerfile.rosco: A containerized implementation of Rosco SBC toolchain https://rosco-m68k.com/docs/toolchain-installation