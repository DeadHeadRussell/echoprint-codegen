TEST_CFLAGS=-D TEST
SRC=../src

include ../Common.mk

MODULES += common/main.o

all: subband onsets

subband: $(MODULES) subband/subband.o
	$(CXX) $(MODULES) $(LDFLAGS) subband/subband.o -o testSubband

onsets: $(MODULES) onsets/onsets.o
	$(CXX) $(MODULES) $(LDFLAGS) onsets/onsets.o -o testOnsets

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $< -g

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -g

%.o: %.cxx %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $< -g

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o $@ $< -g

clean:
	rm -f *.o subband/*.o testSubband
	rm -f *.o onsets/*.o testOnsets

.PHONY: clean all subband onsets

