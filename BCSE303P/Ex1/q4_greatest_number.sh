echo "First number: "
read n1
echo "Second number: "
read n2
echo "Third number: "
read n3

ans=$n1
if [ $n2 -gt $ans ]
then
ans=$n2
fi
if [ $n3 -gt $ans ]
then
ans=$n3
fi

echo "Greatest number: " $ans
