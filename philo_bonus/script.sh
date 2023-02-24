#!/bin/bash

if [ $# -ne 5 ]; then
	echo -e "Usage: $0 PHILO DIE EAT SLEEP [NUM_EAT]\n"
	exit 1
fi

PHILO=$1
DIE=$2
EAT=$3
SLEEP=$4
NUM=$5

IS_DIED="died"

echo "Run philosophers ..."
./philo_bonus $PHILO $DIE $EAT $SLEEP $NUM >test.txt 

# PHILO_LAST=$(tail -n1 test.txt | cut -f3 -d' ')


# if ["$PHILO_LAST" != "died"]; then
# 	echo "There is no philo who died"
# 	exit 0
# fi 

# PHILO_DIED=$(tail -n1 test.txt | cut -f2 -d' ')

for i in $(seq 1 $PHILO); do
	echo -e "\e[0;31m----------$i----------\e[0m"
	grep -w $i test.txt
done


