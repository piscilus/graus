# Phony targets
.PHONY: all clean

EXECUTABLE = graus

INCLUDES = -I.
INCLUDES += -Ilib/cargs

SRCDIR = .
OBJDIR = obj
BINDIR = bin

SOURCES = main.c
SOURCES += lib/cargs/cargs.c
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o) )

CC = gcc
CFLAGS =\
	-c\
	-std=c99\
	-Wall\
	-Wextra\
	-Wpedantic\
	-fsanitize=undefined\
	-fsanitize-undefined-trap-on-error\
	-g

LD = gcc
LDFLAGS =\
	-fsanitize=undefined\
	-fsanitize-undefined-trap-on-error

all: $(BINDIR)/$(EXECUTABLE)

$(OBJDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(EXECUTABLE): $(OBJS)
	mkdir -p $(BINDIR)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(BINDIR)/$(EXECUTABLE)
