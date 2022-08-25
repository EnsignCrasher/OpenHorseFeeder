prefix ?= /usr
FEED_BINARY=horse-feeder

install:
	install --mode=755 -D "$(FEED_BINARY)" "$(DESTDIR)$(prefix)/bin/$(notdir $(FEED_BINARY))"

uninstall:
	-rm -f "$(DESTDIR)$(prefix)/bin/$(notdir $(FEED_BINARY))"

.PHONY: clean
clean:
	rm -f ./i2c
