gcc -Wall -Wextra main.c -o main -lm

mkdir -p results

./main

python plot.py