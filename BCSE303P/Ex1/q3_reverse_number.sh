echo "Number to reverse: "
read number
copy=$number
reversed=0
until [ $copy -eq 0 ]
do
reversed=$((reversed*10))
reversed=$((reversed+copy%10))
copy=$((copy/10))
done
echo $reversed
