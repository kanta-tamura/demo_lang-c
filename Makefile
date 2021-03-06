CC     := gcc
CFLAGS := -Wall -g
SRCS   := $(wildcard src/*.c)
OBJS   := $(patsubst src/%.c,obj/%.o,$(SRCS))
SRCH   := $(wildcard src/*.c include/*.h)

main.out: $(SRCH)
	cd obj && $(MAKE) "CC=$(CC)" "CFLAGS=$(CFLAGS)"
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

run:
	./main.out ${ARG}

clean:
	@rm -rf *.out obj/*.o obj/*.d

.PHONY: run clean