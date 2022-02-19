prefix ?= /usr
I2C_BINARY=i2c
FEED_BINARY=horse-feeder

#install: $(I2C_BINARY)

install:
	gcc ./i2c.c -o ./i2c
	install --mode=755 -D "$(I2C_BINARY)" "$(DESTDIR)$(prefix)/bin/$(notdir $(I2C_BINARY))"
	install --mode=755 -D "$(FEED_BINARY)" "$(DESTDIR)$(prefix)/bin/$(notdir $(FEED_BINARY))"

uninstall:
	-rm -f "$(DESTDIR)$(prefix)/bin/$(notdir $(I2C_BINARY))"
	-rm -f "$(DESTDIR)$(prefix)/bin/$(notdir $(FEED_BINARY))"

.PHONY: clean
clean:
	rm -f ./i2c
