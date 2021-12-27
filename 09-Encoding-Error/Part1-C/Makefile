CFLAGS += -std=c17 -Wall -Wextra -pedantic

#CFLAGS += -D_POSIX_C_SOURCE=200809L
#CFLAGS += -D_XOPEN_SOURCE=700
#CFLAGS += -Ofast
#CFLAGS += -pg -g

# CFLAGS += -MMD

# LDFLAGS += -pg -g

execs = xmas xmas-part1-only

all: $(execs)


# -include *.d

clean:
	$(RM) *.o *~ \#* *.d

mrproper: clean
	$(RM) $(execs)
