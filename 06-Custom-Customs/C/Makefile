CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused
CFLAGS += -MMD
CFLAGS += -D_XOPEN_SOURCE=700

CFLAGS += -g
EXECS = aoc2020-06-part1 aoc2020-06

RUNNABLE = aoc2020-06


all : $(EXECS)

run : $(RUNNABLE)
	./$(RUNNABLE)

-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
