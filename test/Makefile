
target:=unit_test

cppfiles:=$(shell find -name '*.cpp' | xargs)
objects:=$(subst .cpp,.o,$(cppfiles))


CXXFLAGS+=-I/usr/local/boost/include

LDFLAGS+=-L/usr/local/boost/lib \
		 -L../MultiLanguage/

LIBS+=-lMultiLanguage -lboost_system -lboost_filesystem

all: $(target)

$(target) : $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

run_test:
	-./$(target)

clean:
	-rm -f $(objects)
