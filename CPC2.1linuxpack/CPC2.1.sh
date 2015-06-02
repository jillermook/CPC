#!/bin/bash

startstep=1
endstep=5
while getopts "t:n:f:g:s:p:a:b:q:e:" arg
do
   case $arg in
t)
 treatment=$OPTARG
 IFS=, DIRS=($treatment);;
f)
  format="-f$OPTARG";;   
n)
 output=$OPTARG;;
g)
 gsize="-g$OPTARG";;
s)
 tsize="-s$OPTARG";;
p)
 pvalue="-p$OPTARG";;
a)
 graphtag=$OPTARG;;
b)
 bwidth="--bw$OPTARG";;
q)
 startstep=$OPTARG;;
e)
 endstep=$OPTARG;;
?)
echo "unknow argument" exit
esac
done

if [ -z "$treatment" ]
then
echo "-t argument is needed" exit
fi

if [ -z "$output" ]
then
echo "-n argument is needed" exit
fi

#1 step
if [ $startstep -le 1 ]&&[ $endstep -ge 1 ]
then
echo "step1 start"
num=0
while [ $num -lt ${#DIRS[@]} ]
do
i=0
while [ $i -lt ${#DIRS[@]} ]
do
if [ $i != $num ]
then
macs14 -t ${DIRS[$num]} -c ${DIRS[$i]} -n result$[num+1]$[i+1] $format $gsize $tsize $pvalue $bwidth &
fi
let i=i+1
done
#wait
let num=num+1
done
wait

fi



#2 step
if [ $startstep -le 2 ]&&[ $endstep -ge 2 ]
then
echo "step2 start"
num=1
./peaks_to_order1.1.out result12_peaks.bed temp_order1.bed ${#DIRS[@]} 1
fi

#3 step
if [ $startstep -le 3 ]&&[ $endstep -ge 3 ]
then
echo "step3 start"
i=0
while [ $i -lt ${#DIRS[@]} ]
do
j=0
while [ $j -lt ${#DIRS[@]} ]
do
if [ "$j" -ne "$i" ]
then
if [ "$i" -eq 0 ]&&[ "$j" -eq 1 ]
then
q=0;
else
numb=`expr $i \* ${#DIRS[@]}`
let numb=numb+j
./combine_function4.0.out temp_order$num.bed result$[i+1]$[j+1]_peaks.bed temp_order$[num+1].bed ${#DIRS[@]} $numb 

let num=num+1
fi

fi
let j=j+1
done

let i=i+1
done
fi

#4 step
if [ $startstep -le 4 ]&&[ $endstep -ge 4 ]
then
echo "step4 start"
./order_to_ordergraphfile_classify.out temp_order$num.bed $output ${#DIRS[@]}
fi

#5 step
if [ $startstep -le 5 ]&&[ $endstep -ge 5 ]
then
echo "step5 start"
./out_to_htmlmlti1.1.out $output $output.html ${#DIRS[@]} "$graphtag"

fi








