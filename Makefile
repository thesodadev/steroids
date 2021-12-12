TARGET_NAME = steroids

INCLUDE_FILES = common.h math.h string.h
INCLUDE_DIR = include
INCLUDE_PATHES = $(patsubst %,$(INCLUDE_DIR)/%,$(INCLUDE_FILES))

.PHONY: install

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

install: $(INCLUDE_PATHES)
	install -d $(DESTDIR)$(PREFIX)/include/$(TARGET_NAME)
	install -m 644 $(INCLUDE_PATHES) $(DESTDIR)$(PREFIX)/include/$(TARGET_NAME)
