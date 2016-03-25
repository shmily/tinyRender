
include makefile.in

.PHONY: libs clean

TARGET = libmix.a

all: $(TARGET)

SUBDIRS = rply-1.1.4

CSRCS = src/vector.c \
        src/color.c \
		src/mesh.c

COBJS = $(patsubst %.c,%.o,$(CSRCS))

CFLAGS += -std=c++11

$(TARGET): $(COBJS) libs
	$(AR) -r $@ $(COBJS)

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS) $(INCLUDEFLAGS)

%.d:%.cpp
	@set -e; rm -f $@; $(CXX) -MM $< -MT $(patsubst %.cpp,%.o,$<) $(INCLUDEFLAGS) $(CFLAGS) > $@.$$$$; \
	 sed 's,\($*\)\.o[ : ]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

-include $(COBJS:.o=.d)

libs:
	@ mkdir -p library
	@ for subdir in $(SUBDIRS); do \
		(cd $$subdir && make install); \
	done

clean:
	cd src && rm -rf $(TARGET) $(COBJS) *.o *.d *.d.*
	@ for subdir in $(SUBDIRS); do \
		(cd $$subdir && make clean); \
	done
