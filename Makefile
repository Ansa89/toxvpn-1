OBJS := $(patsubst %.c,%.o, $(wildcard *.c))
OBJS += $(patsubst %.cpp,%.o, $(wildcard *.cpp))
DEPS := libnl-3.0 libnl-route-3.0 jansson libtoxcore

#COMMON_FLAGS := -Wall -g -Werror=incompatible-pointer-types -Werror=return-type
#CXXFLAGS += -std=c++14 $(COMMON_FLAGS)
#CFLAGS += -std=c99 -I/usr/include/libnl3 $(COMMON_FLAGS)
#LDFLAGS += -pthread -static-libgcc -static-libstdc++ -Wl,-Bstatic -ltoxcore -lsodium -lnl-3 -lnl-route-3 -lcap -ljansson -Bdynamic
CFLAGS += -std=c99 $(shell pkg-config --cflags $(DEPS))
CXXFLAGS += -std=c++11 $(shell pkg-config --cflags $(DEPS))
LDFLAGS += -lcap $(shell pkg-config --libs $(DEPS))
LDFLAGS_STATIC += -static -pthread -Wl,-Bstatic $(LDFLAGS)


# Targets
all: toxvpn

toxvpn: $(OBJS)
	@echo "  LD    $@"
	@$(CXX) $(LDFLAGS) $(OBJS) -o $@

toxvpn_static: $(OBJS)
	@echo "  LD    toxvpn"
	@$(CXX) $(OBJS) $(LDFLAGS_STATIC) -o toxvpn

%.o: %.c
	@echo "  CC    $@"
	@$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.cpp
	@echo "  CXX   $@"
	@$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) $(OUTFILE)

.PHONY: all clean toxvpn_static
