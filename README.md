# winSocketpair
C++ socketpair implementation for windows

# Installation
1. Download the project ( c:\winSocketpair )
2. Create a build directory ( c:\winSocketpair\build )
3. Go to build directory and do cmake ( cmake .. )
4. Build project ( cmake --build . ). You may get errors that header file is missing. This is because the header is not installed yet
5. In Admin console do install ( cmake --install ). This will install header in c:\Program Files(X86)\winSocketpair\include. If you don't have admin rights, then you can use --prefix to install in other directories. check cmake documentation.
6. Build again ( cmake build . ). This time build step should not have any errors.
    
# Tutorial/EXample(TEX)
In the tex directory there are 2 examples of how to use winSocketpair. If install is completed correctly the two example programs would have compiled and installed under .../build/tex/<example>/Debug
