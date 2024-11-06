cd ..

make

Copy generated tal code to https://metasyn.srht.site/learn-uxn/ to see output

gcc -I. -P -E examples/printf.c -o examples/printf.tmp

./chibicc -O1 examples/printf.tmp > examples/printf.tal

gcc -I. -P -E examples/mandelbrot.c -o examples/mandelbrot.tmp

./chibicc -O1 examples/mandelbrot.tmp > examples/mandelbrot.tal

gcc -I. -P -E examples/day6.c -o examples/day6.tmp

./chibicc -O1 examples/day6.tmp > examples/day6.tal
