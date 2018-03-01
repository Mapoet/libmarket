LIB = market

CFLAGS = -Wall -rdynamic
C_TESTS = $(wildcard src/*.c)
H_TESTS = $(wildcard src/*.h)
TESTS = $(C_TESTS) $(H_TESTS)
OBJECTS = $(subst src,obj,$(patsubst %.c,%.o,$(wildcard ../src/*.c)))

bin/tests : $(TESTS) ../lib/lib$(LIB).a
	gcc $(CFLAGS) $(TESTS) -o bin/tests \
		-Iinclude -I../include -Ilib/libdmc/include \
		-L../lib -l$(LIB) -Llib/libdmc -ldmc\
		-lgc

../lib/lib$(LIB).a : $(OBJECTS)
	ar rcs ../lib/lib$(LIB).a $(OBJECTS)

../obj/%.o : ../src/%.c ../include/%.h
	gcc $(CFLAGS) -c $< -o $@ \
		-Iinclude -I../include -Ilib/libdmc/include \
		-Llib/libdmc -ldmc \
		-lgc

