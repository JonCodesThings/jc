setlocal EnableDelayedExpansion

CALL :run_test test\10.jc 10
CALL :run_test test\11.jc 11
CALL :run_test test\12.jc 12
CALL :run_test test\13.jc 13
CALL :run_test test\14.jc 14
CALL :run_test test\15.jc 15
CALL :run_test test\16.jc 16
CALL :run_test test\17.jc 17
CALL :run_test test\18.jc 18
CALL :run_test test\19.jc 19

CALL :run_test test\add.jc 8
CALL :run_test test\subtract.jc 8
CALL :run_test test\multiply.jc 8
CALL :run_test test\divide.jc 8

CALL :run_test test\pointer_test.jc 24

CALL :run_test test\proto_helloworld.jc 0

CALL :run_test test\if_test.jc 0
CALL :run_test test\if_else_test.jc 1
CALL :run_test test\if_else_if_else_test.jc 10
CALL :run_test test\if_else_if_else_else_test.jc 2

CALL :run_test test\for_test.jc 36
CALL :run_test test\for_array_test.jc 9
CALL :run_test test\while_test.jc 6
CALL :run_test test\while_array_test.jc 9

CALL :run_test test\defer_test.jc 0

CALL :run_test test\explicit_cast_test.jc 24
CALL :run_test test\implicit_cast_test.jc 24

CALL :run_test test\float_if_test.jc 0

CALL :run_test test\u32_test.jc 1

CALL :run_test test\alias_test.jc 10

CALL :run_test test\variadic_def_test.jc 0

CALL :run_test test\struct_test.jc 5

CALL :run_test test\module_import_test.jc 0
pause
cmd /k

:run_test
@echo OFF
echo Running test %~1
RelWithDebInfo\jc.exe %~1
llc -filetype=obj -march=x86-64 %~1.ir
set retval=%ERRORLEVEL%
if not retval==0 (link.exe %~1.ir.obj /OUT:%~1.exe libcmt.lib) 
%~1.exe
set return_code=%ERRORLEVEL%
if not return_code == %~2 (echo "Test successful!")
if return_code == %~2 (echo "Test failed!")
