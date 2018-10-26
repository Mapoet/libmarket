LIB=market

CFLAGS = -Wall -rdynamic
C_TESTS = $(wildcard src/*.c)
H_TESTS = $(wildcard src/*.h)
TESTS = $(C_TESTS) $(H_TESTS)
OBJECTS = $(subst src/$(LIB),obj,$(patsubst %.c,%.o,$(wildcard ../src/$(LIB)/*.c)))

bin/tests : $(TESTS) ../lib/lib$(LIB).a
	gcc $(CFLAGS) $(TESTS) -o bin/tests -Iinclude \
		-I../include -L../lib -l$(LIB) \
		-I../lib/libdmc/include -L../lib/libdmc -ldmc

../lib/lib$(LIB).a : $(OBJECTS)
	ar rcs ../lib/lib$(LIB).a $(OBJECTS)

../obj/%.o : ../src/$(LIB)/%.c ../include/$(LIB)/%.h
	gcc $(CFLAGS) -c $< -o $@ -I../include \
		-I../lib/libdmc/include -L../lib/libdmc -ldmc

.PHONY: valgrind

valgrind :
	gcc $(CFLAGS) -O0 -g $(TESTS) -o bin/v_tests -Iinclude \
		-I../include -L../lib -l$(LIB) \
		-I../lib/libdmc/include -L../lib/libdmc -ldmc
