make:
	clang src/*.c -std=c17 -O3 -Isrc/include -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -o bin -lglib-2.0
