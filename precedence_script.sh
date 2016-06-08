echo "Each test is worth 3 points"
echo "1) Basic paren test"
(echo "True")
echo "2) Basic paren test with &&"
(echo "True" && echo "True")
echo "3) Basic paren teset with ||"
(echo "True" || echo "False")
echo "4) Nested Paren test with &&"
(echo "True" && (echo "True"))
echo "5) Nested Paren test with ||"
(echo "True" || (echo "False"))
echo "6) Print Three Trues (tripple depth)"
(echo "True" && (echo "maybe" && echo "false"))
echo "7) Symbolic Test (prints one True)"
([ -e test.txt ]) && (echo "True")
echo "8) Print Two Trues (internal unit test)"
(echo "True" || echo "False") && echo "True"
echo "9) Print Four Trues"
echo "True" && echo "True" && echo "True" && echo "True"
echo "10) Print Two Trues"
(echo "yes" && echo "this") && (echo "is" && echo "the") && (echo "best" && (echo "code" && echo "ever"))
echo "tru") && (echo "truf")
echo "I hope this works"
