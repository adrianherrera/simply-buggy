SRC=$(shell find . -name '*.c')
TARGETS=$(SRC:%.c=%)

.PHONY: all
all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGETS)
