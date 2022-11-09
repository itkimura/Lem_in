wc=`ls -l test_suite/maps | wc -l | awk '{print $1}'`
path="test_suite/tests_eval_generator/"
files=`ls -l $path | sed '1d' | awk '{print $9}'`
nb=0;
for element in ${files[@]}
do
    echo "----[Test $path$element]----"
    # time leaks -q --atExit -- ./lem-in < "$path$element"
    ./lem-in < "$path$element"
    echo ""
done
