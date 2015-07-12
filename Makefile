
###########################################################
# 
###########################################################

.PHONY : all library test example clean

all: library test example

library: 
	$(MAKE) -C MultiLanguage

test: library
	$(MAKE) -C test

example: library
	$(MAKE) -C example

install:
	$(MAKE) -C MultiLanguage install

clean:
	$(MAKE) -C MultiLanguage clean
	$(MAKE) -C test clean
	$(MAKE) -C example clean
