CFLAGS = -std=c17
CFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused
#CFLAGS += -MMD
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -g
#CFLAGS += -O3
LDLIBS += -lcrypto

EXECS = prog

.PHONY: run clean mrproper

all : $(EXECS)

run : prog
	./prog abcdef pqrstuv iwrupvqb


#-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
