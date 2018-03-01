LIB = market

CFLAGS = -Wall -rdynamic
OBJECTS = $(subst src,obj,$(patsubst %.c,%.o,$(wildcard src/market/*.c))) \
	$(subst src,obj,$(patsubst %.c,%.o,$(wildcard src/dm/*.c)))

lib/lib$(LIB).a : $(OBJECTS)
	ar rcs lib/lib$(LIB).a $(OBJECTS)

obj/market/%.o : src/market/%.c include/market/%.h
	gcc $(CFLAGS) -c $< -o $@ \
		-Iinclude \
		-lgc

obj/dm/%.o : src/dm/%.c include/dm/%.h
	gcc $(CFLAGS) -c $< -o $@ \
		-Iinclude \
		-lgc

clean:
	rm -fR obj/market
	rm -fR obj/dm
	mkdir obj/market
	mkdir obj/dm
