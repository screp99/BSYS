rm tlb.csv

for (( i = 1; i <= $1; i *= 2))
do
    ./tlb $i $2
    wait
done