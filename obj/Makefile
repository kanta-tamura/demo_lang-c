SRCS := $(wildcard ../src/*.c)
OBJS := $(patsubst ../src/%.c,%.o,$(SRCS))
OBJD := $(patsubst ../src/%.c,%.d,$(SRCS))
HEAD := $(wildcard ../include/*.h)

.PHONY: dummy
dummy: $(OBJS)

%.o: ../src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ../include

%.d: ../src/%.c $(HEAD)
	cpp -MM $< -MF $@ -I ../include

-include $(OBJD)