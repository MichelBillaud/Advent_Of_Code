CFLAGS += -std=c17 -Wall -Wextra -pedantic

#CFLAGS += -D_POSIX_C_SOURCE=200809L
#CFLAGS += -D_XOPEN_SOURCE=700
#CFLAGS += -Ofast
#CFLAGS += -pg -g

# CFLAGS += -MMD

# LDFLAGS += -pg -g

execs = prog

run: $(execs)
	./$<
	
all: $(execs)

prog: prog.o

# -include *.d

clean:
	$(RM) *.o *~ \#* *.d

mrproper: clean
	$(RM) $(execs)
