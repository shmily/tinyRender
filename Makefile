
include makefile.in

vpath %.cpp src
vpath %.d   target

TARGET = tinyRender

SUBDIRS = rply-1.1.4

CSRCS = src/vector.cpp \
        src/color.cpp  \
		src/mesh.cpp   \
		src/window.cpp \
		src/canvas.cpp \
		src/main.cpp

OBJ_PATH = target
DEPENDS  = $(patsubst %.cpp,$(OBJ_PATH)/%.d,$(notdir $(CSRCS)))
COBJS    = $(patsubst %.cpp,$(OBJ_PATH)/%.o,$(notdir $(CSRCS)))

CFLAGS += -std=c++11
LFLAGS  = -L./library/rply -lrply
LFLAGS += -lSDLmain -lSDL

all: $(TARGET)

$(TARGET): $(COBJS)
	@echo +++ Linking [$(notdir $@)]
	@$(CXX) $(COBJS) -o $@ $(CFLAGS) $(LFLAGS)

$(COBJS):$(OBJ_PATH)/%.o : %.cpp
	@echo +++ Compiling [$(notdir $<)]
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INCLUDEFLAGS)

$(DEPENDS):$(OBJ_PATH)/%.d : %.cpp
	@set -e; rm -f $@; \
	 $(CXX) -MM $< -MT $(patsubst %.cpp,$(OBJ_PATH)/%.o,$(notdir $<)) $(INCLUDEFLAGS) $(CFLAGS) > $@.$$$$; \
	 sed 's,\($*\)\.o[ : ]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

-include $(DEPENDS)

.PHONY: libs clean

libs:
	@ mkdir -p library
	@ for subdir in $(SUBDIRS); do \
		(cd $$subdir && make install); \
	done

clean:
	rm -rf $(OBJ_PATH)/*
	rm -rf $(TARGET)
#	cd src && rm -rf $(TARGET) $(COBJS) *.o *.d *.d.*
#	@ for subdir in $(SUBDIRS); do \
#		(cd $$subdir && make clean); \
#	done
