CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused

# CFLAGS += -MMD

CFLAGS += -g
EXECS = day18


all : $(EXECS)

run : $(EXECS)
	./$<

# -include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
