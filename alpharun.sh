function run_test()
{
echo "Running test $1"
./jc $1
llc -filetype=obj $1.ir
retval=$?
if [ $retval -eq  0 ]
then
clang $1.ir.o -o $1.out
./$1.out
return_code=$?

if [ $return_code -eq $2 ]
then
echo "Test successful!"
fi

if [ $return_code -ne $2 ]
then
echo "Test failed!"
fi
fi
}

ninja

run_test test/10.jc 10
run_test test/11.jc 11
run_test test/12.jc 12
run_test test/13.jc 13
run_test test/14.jc 14
run_test test/15.jc 15
run_test test/16.jc 16
run_test test/17.jc 17
run_test test/18.jc 18
run_test test/19.jc 19

run_test test/add.jc 8
run_test test/subtract.jc 8
run_test test/multiply.jc 8
run_test test/divide.jc 8

run_test test/pointer_test.jc 24

run_test test/proto_helloworld.jc 0

run_test test/if_test.jc 0
run_test test/if_else_test.jc 1
run_test test/if_else_if_else_test.jc 10
run_test test/if_else_if_else_else_test.jc 2

run_test test/for_test.jc 36
run_test test/for_array_test.jc 9
run_test test/while_test.jc 6
run_test test/while_array_test.jc 9

run_test test/defer_test.jc 0

run_test test/explicit_cast_test.jc 24
run_test test/implicit_cast_test.jc 24

