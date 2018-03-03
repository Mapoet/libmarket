LIB = market

CFLAGS = -Wall -rdynamic
C_TESTS = $(wildcard src/*.c)
H_TESTS = $(wildcard src/*.h)
TESTS = $(C_TESTS) $(H_TESTS)
OBJECTS = $(subst src/market,obj,$(patsubst %.c,%.o,$(wildcard ../src/market/*.c)))

bin/tests : $(TESTS) ../lib/lib$(LIB).a
	gcc $(CFLAGS) $(TESTS) -o bin/tests \
		-Iinclude -I../include -I../lib/libdmc/include \
		-L../lib -l$(LIB) -L../lib/libdmc -ldmc \
		-lgc

../lib/lib$(LIB).a : $(OBJECTS)
	ar rcs ../lib/lib$(LIB).a $(OBJECTS)

../obj/%.o : ../src/market/%.c ../include/market/%.h
	gcc $(CFLAGS) -c $< -o $@ \
		-I../include -I../lib/libdmc/include \
		-L../lib/libdmc -ldmc\
		-lgc
