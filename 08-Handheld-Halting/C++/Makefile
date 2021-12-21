CXXFLAGS = -std=c++20
CXXFLAGS += -Wall -Wextra -pedantic -Werror -Wno-unused
# CXXFLAGS += -MMD

CXXFLAGS += -g

RUN = day08
EXECS = $(RUN)

all : $(EXECS)

run: $(RUN)
	./$<

-include $(wildcard *.d)

clean:
	$(RM) *~ *.o *.d

mrproper: clean
	$(RM) $(EXECS)
