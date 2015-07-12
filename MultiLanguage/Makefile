
cppfiles:=$(shell find -name '*.cpp' | xargs)
objects:=$(subst .cpp,.o,$(cppfiles))

static_lib:=libMultiLanguage.a
head_files:=MultiLanguage.h

CP:=cp -r
PREFIX?=/usr/local
CXXFLAGS+=-I/usr/local/boost/include

all: $(static_lib)

$(static_lib) : $(objects)
	$(AR) rcs $@ $^

install: $(static_lib) $(head_files)
	$(CP) $(static_lib) $(PREFIX)/lib
	$(CP) $(head_files) $(PREFIX)/include

clean:
	-rm -f $(objects)
