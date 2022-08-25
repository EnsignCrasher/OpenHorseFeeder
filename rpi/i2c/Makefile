prefix ?= /usr
I2C_BINARY=i2c

install:
	gcc ./i2c.c -o ./i2c
	install --mode=755 -D "$(I2C_BINARY)" "$(DESTDIR)$(prefix)/bin/$(notdir $(I2C_BINARY))"

uninstall:
	-rm -f "$(DESTDIR)$(prefix)/bin/$(notdir $(I2C_BINARY))"

.PHONY: clean
clean:
	rm -f ./i2c
