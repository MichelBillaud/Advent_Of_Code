CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic 
CFLAGS += -Werror -Wno-unused
# CFLAGS += -MMD
CFLAGS += -D_XOPEN_SOURCE=700

CFLAGS += -g
EXECS = day12 day12-part1


all : $(EXECS)

run: $(EXECS)
	./$<

-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
