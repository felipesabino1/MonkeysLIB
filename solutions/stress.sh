#!/bin/bash

// Para uma solucao apenas:

make brute
make gen
make solution

for((c = 0; c <= 500; c++)); do
    ./gen 2 > in
    start = $(date +%s)
    ./solution < in > out
    end = $(date +%s)
    echo "Elapsed Time in test $c: $(($end - $start)) seconds."
    ./brute < in > aout
    diff -B out aout > /dev/null || break
    echo "Passou no caso $c."
done

echo "WA on the following case:"
cat in
echo "Your answer is:"
cat out
echo "Correct answer is:"
cat aout

// Para mais de uma solucao: mandar para um validador e deixar ele resolver tudo.

#!/bin/bash

make brute          # fazer o codigo forca bruta do problema
make gen            # fazer o gerador do problema
make solution       # a sua solucao do problema
make validator      # o validador da sua solucao

for((c = 0; c <= 500; c++)); do
    ./gen 2 > in
    start = $(date +%s)
    ./solution < in > out
    end = $(date +%s)
    echo "Elapsed Time in test $c: $(($end - $start)) seconds."
    ./brute < in > a_in
    ./validator < a_in > aout
    diff -B out aout > /dev/null || break
    echo "Passou no caso $c."
done

echo "WA on the following case:"
cat in
echo "Your answer is:"
cat aout
echo "The possible solutions are:"
cat out