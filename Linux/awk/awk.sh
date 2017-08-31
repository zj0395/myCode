BEGIN{
math=0
english=0
printf "Name   No\n"
printf "-------\n"
}
{
printf "%20s %20s %20s %20s\n", $1, $2, $3, $4
}
END{
print "------"
print "ENDas"
}
