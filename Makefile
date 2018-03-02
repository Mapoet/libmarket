LIB = market

CFLAGS = -Wall -rdynamic
OBJECTS = $(subst src,obj,$(patsubst %.c,%.o,$(wildcard src/market/*.c)))

lib/lib$(LIB).a : $(OBJECTS)
	ar rcs lib/lib$(LIB).a $(OBJECTS)

obj/market/%.o : src/market/%.c include/market/%.h
	gcc $(CFLAGS) -c $< -o $@ \
		-Iinclude -Ilib/libdmc/include \
		-L../lib -l$(LIB) -Llib/libdmc -ldmc\
		-lgc
