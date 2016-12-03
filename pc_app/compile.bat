set PATH=C:\Qt\2010.05\mingw\bin;C:\Qt\2010.05\qt\bin;C:\dev\opencv\utils\tesseract-mingw\bin
del /q bin
del /q release\*.exe
qmake project.pro
make -f Makefile.Release 2>error.txt
strip Release\iwscope.exe
copy c:\sw\gsl\bin\* bin /y
copy ..\fixed_lib\bin\*.* bin  /y
