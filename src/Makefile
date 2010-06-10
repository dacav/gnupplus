.PHONY : all clean

CXXFLAGS := -Wall -I.
DIRS := $(shell find . -type d)
FILES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
OBJS := $(addsuffix .o, $(basename $(FILES)))
APP := gpint

all: $(OBJS)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(APP)

clean:
	rm -f $(OBJS) $(APP) $(OBJS:.o=.d)

%.d: %.c
	$(CXX) $(CXXFLAGS) -MM -MF $@ $<

-include $(OBJS:.o=.d)
