
include ../makefile.in

TARGET = librply.a
CSRCS := rply.c

COBJS = $(patsubst %.c,%.o,$(CSRCS))

all: $(TARGET)

#$(TARGET): $(COBJS)
#	$(CC) -o $@ $^ $(LDFLAGS)

$(TARGET): $(COBJS)
	$(AR) -r $@ $(COBJS)

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDEFLAGS)

%.d:%.c
	@set -e; rm -f $@; $(CC) -MM $< $(INCLUDEFLAGS) > $@.$$$$; \
	 sed 's,\($*\)\.o[ : ]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

-include $(COBJS:.o=.d)

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o *.d *.d.*
