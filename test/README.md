cd ..

make

Copy generated tal code to https://metasyn.srht.site/learn-uxn/ to see output

gcc -I. -P -E examples/printf.c -o examples/printf.tmp

./chibicc -O1 examples/printf.tmp > examples/printf.tal