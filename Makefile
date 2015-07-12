
###########################################################
# 
###########################################################

.PHONY : all library build_test example clean test

all: library build_test example

library: 
	$(MAKE) -C MultiLanguage

build_test: library
	$(MAKE) -C test

example: library
	$(MAKE) -C example

install:
	$(MAKE) -C MultiLanguage install

test:
	$(MAKE) -C test  run_test

clean:
	$(MAKE) -C MultiLanguage clean
	$(MAKE) -C test clean
	$(MAKE) -C example clean
