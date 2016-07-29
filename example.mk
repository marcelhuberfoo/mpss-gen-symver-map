.PHONY: all clean

all: libbar.so

clean:
	rm -f libbar.map libbar.so

libbar.map: example.cfg example.c
	./gen-symver-map $< $@ -- $(filter-out $<, $^) -- $(CC) $(CFLAGS)

libbar.so: example.c libbar.map
	$(CC) $(CFLAGS) -fpic -shared $< -o $@ \
		-Wl,-soname,libbar.so.3 \
		-Wl,--version-script=libbar.map
