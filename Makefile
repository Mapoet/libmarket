LIB = market

CFLAGS = -Wall -rdynamic
OBJECTS = $(subst src,obj,$(patsubst %.c,%.o,$(wildcard src/*.c)))

lib/lib$(LIB).a : $(OBJECTS)
	ar rcs lib/lib$(LIB).a $(OBJECTS)

obj/%.o : src/%.c include/%.h
	gcc $(CFLAGS) -c $< -o $@ \
		-Iinclude -I../libdmc/include \
		-L../libdmc -ldmc \
	  -lgc

