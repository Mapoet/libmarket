CFLAGS = -Wall -rdynamic
OBJECTS = $(subst src/market,obj,$(patsubst %.c,%.o,$(wildcard src/market/*.c)))

lib/libmarket.a : $(OBJECTS)
	ar rcs lib/libmarket.a $(OBJECTS)

obj/%.o : src/market/%.c include/market/%.h
	gcc $(CFLAGS) -c $< -o $@ \
		-Iinclude -Ilib/libdmc/include \
		-L../lib -lmarket -Llib/libdmc -ldmc \
		-lgc
