CFLAGS += -std=c17 -Wall -Wextra -pedantic
CFLAGS += -Werror -Wno-unused

#CFLAGS += -D_POSIX_C_SOURCE=200809L
#CFLAGS += -D_XOPEN_SOURCE=700
#CFLAGS += -Ofast
#CFLAGS += -pg -g

# CFLAGS += -MMD

# LDFLAGS += -pg -g

execs = day10

all: $(execs)


# -include *.d

clean:
	$(RM) *.o *~ \#* *.d

mrproper: clean
	$(RM) $(execs)
