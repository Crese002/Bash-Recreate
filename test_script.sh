echo "Setup with test.txt file and test_dir directory"
echo "Each test is worth 2 points"
echo "1) True base Test"
test test.txt
echo "2) False base Test"
test false.txt
echo "3) True -e Test"
test -e test.txt
echo "4) False -e Test"
test -e false.txt
echo "5) True -f Test"
test -f test.txt
echo "6) False -f Test"
test -f false.txt
echo "7) False -f Test with real directory"
test -f test_dir
echo "8) True -d Test"
test -d test_dir
echo "9) False -d Test with symbolic"
[ -d false_dir ]
echo "10) False -d Test with real file"
test -d test.txt
echo "11) True test with && True print"
test -e test.txt && echo "True"
echo "12) Flase test with || True print"
test -e false.txt || echo "True"
echo "13) True test with || (no print) and symbolic"
[ -e test.txt ] || echo "False"
echo "14) False test with && (no print)"
test -e false.txt && echo "False"
echo "15) True test (basic parentheses)"
(test -e test.txt)
echo "16) Test for symbolic"
[ -d test.txt ]
echo "17) Test with && True print"
(test -e test.txt && echo "True")
echo "18) Test with && (no print) and symbolic"
([ -d test.txt ] && echo "False")
echo "19) False test which should print nothing"
(test -d test.txt && (echo "True A" && echo "True B"))
echo "20) True test printing True A and True B"
(test -e test.txt && (echo "True A" && echo "True B"))