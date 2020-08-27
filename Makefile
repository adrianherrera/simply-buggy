SRC=$(shell find . -name '*.c' -and -not -name 'common.c')
TARGETS=$(SRC:%.c=%)

.PHONY: all
all: $(TARGETS)

%: %.c common.c
	$(CC) $(CFLAGS) -o $@ $?

.PHONY: clean
clean:
	rm -f $(TARGETS)
