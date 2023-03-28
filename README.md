# LiM_Gem5_Simulator
## Getting star
+ Clone code from GitHub and initialize
```bash=
git clone https://github.com/njru8cjo/LiM_Gem5_Simulator.git
cd LiM_Gem5_Simulator
git submodule init
git submodule update --remote
```
+ Build RISC-V GNU toolchain
```bash=
cd riscv-gnu-toolchain
git submodule init
git submodule update --remote
mkdir build
./configure --prefix=/path/to/build
make linux
```
+ Build Gem5
```bash=
cd gem5
scons build/RISCV/gem5.opt
```
+ Compile example code and run with Gem5
```bash=
/path/to/build/bin/riscv64-unknown-linux-gnu-gcc experiment/aes128_addroundkey/aes128_addroundkey_lim_ext_asm.c -static -o exp
gem5/build/RISCV/gem5.opt gem5/configs/example/se.py -c ./test
```
