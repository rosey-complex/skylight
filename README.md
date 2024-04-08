# **Skylight - A companion tool for Skymake development**
## About
This tool simply extracts the data of .sky files for use in Skymake's code. Nothing more, nothing less.

## Compiling:

### On Linux:
-   Clone the repository using `git clone https://github.com/rosey-complex/skylight`
-   Install development files for Qt6Core and Qt6Widgets.
-   In the root directory of the reposotory, run `cmake .` .
-   After cmake finishes, run `make`.
-   If the compilation finishes, you should now have a compiled `skylight` binary.

### On Windows (MSYS2):
-   Install MSYS2.
-   Start MSYS2 MINGW64 from the start menu.
-   In the MSYS2 command line, install the required tools and libaries.
    + Run `pacman -S mingw-w64-x86_64-binutils pactoys git`.
    + Afterwards, run `pacboy -S toolchain:p cmake:p qt6-base:p extra-cmake-modules:p ninja:p`.
    + If prompted to select an option, just press "enter".
-   Clone the repository using `git clone https://github.com/rosey-complex/skylight`
-   Enter the repository's directory.
-   Run `cmake .` and then, after cmake completes succesfully, run `cmake --build .`.
-   If there are no compilation errors, you should have a compiled `skylight.exe` executable.