LIB=market

CFLAGS = -Wall -rdynamic
OBJECTS = $(subst src/$(LIB),obj,$(patsubst %.c,%.o,$(wildcard src/$(LIB)/*.c)))

lib/lib$(LIB).a : $(OBJECTS)
	if [ ! -e lib ];then mkdir lib;fi
	ar rcs lib/lib$(LIB).a $(OBJECTS)

obj/%.o : src/market/%.c include/market/%.h
	if [ ! -e obj ];then mkdir obj;fi
	gcc $(CFLAGS) -c $< -o $@ -Iinclude \
		-Ilib/libdmc/include -Llib/libdmc -ldmc
