APP=meminfo

SRC = $(wildcard *.cpp)
BINDIR = bin

OBJS = $(addprefix $(BINDIR)/,$(addsuffix .o,$(SRC)))
DEPS = $(addprefix $(BINDIR)/,$(addsuffix .d,$(SRC)))

#CROSS_COMPILE=arm-linux-gnueabihf-
CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++
LD=$(CROSS_COMPILE)g++
STRIP=$(CROSS_COMPILE)strip

CFLAGS= -Wall -Wconversion -fexceptions -Wextra 
CXXFLAGS = $(CFLAGS) -std=c++17 

LDFLAGS = $(CXXFLAGS) -lm -lrt -lpthread 

$(shell mkdir -p $(BINDIR))

.PHONY: all debug build clean 


all: CFLAGS += -O3
all: $(BINDIR) build
	$(STRIP) $(BINDIR)/$(APP) 

build: $(DEPS) $(BINDIR)/$(APP)

$(BINDIR):
	mkdir -p $(BINDIR)

debug: CFLAGS += -O0 -g -DDEBUG
debug: LDFLAGS += -Wl,-Map,$(BINDIR)/$(APP).map
debug: $(BINDIR) build

$(BINDIR)/$(APP): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(BINDIR)/%.cpp.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $(BINDIR)/$*.cpp.o $< 

$(BINDIR)/%.cpp.d : %.cpp
	$(CXX) $(CXXFLAGS) -MM -MT $(BINDIR)/$*.cpp.o -MT $(BINDIR)/$*.cpp.d -MF $@ $<

clean:
	rm $(OBJS) $(DEPS) $(APP) $(APP).map

-include $(DEPS)




