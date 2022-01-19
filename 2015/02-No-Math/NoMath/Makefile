CFLAGS += -std=c17 -Wall -Wextra -pedantic
CFLAGS += 
#CFLAGS += -D_POSIX_C_SOURCE=200809L
#CFLAGS += -D_XOPEN_SOURCE=700
#CFLAGS += -Werror
#CFLAGS += -pg -g

# CFLAGS += -MMD

# LDFLAGS += -pg -g

execs = prog

all: $(execs)

prog: prog.o

# -include *.d

clean:
	$(RM) *.o *~ \#* *.d

mrproper: clean
	$(RM) $(execs)
