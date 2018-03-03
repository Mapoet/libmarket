CFLAGS = -Wall -rdynamic
C_TESTS = $(wildcard src/*.c)
H_TESTS = $(wildcard src/*.h)
TESTS = $(C_TESTS) $(H_TESTS)
OBJECTS = $(subst src/market,obj,$(patsubst %.c,%.o,$(wildcard ../src/market/*.c)))

bin/tests : $(TESTS) ../lib/libmarket.a
	gcc $(CFLAGS) $(TESTS) -o bin/tests \
		-Iinclude -I../include -I../lib/libdmc/include \
		-L../lib -lmarket -L../lib/libdmc -ldmc \
		-lgc

../lib/libmarket.a : $(OBJECTS)
	ar rcs ../lib/libmarket.a $(OBJECTS)

../obj/%.o : ../src/market/%.c ../include/market/%.h
	gcc $(CFLAGS) -c $< -o $@ \
		-I../include -I../lib/libdmc/include \
		-L../lib/libdmc -ldmc\
		-lgc
