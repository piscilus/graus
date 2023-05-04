.PHONY: all clean debug release

EXECUTABLE = graus

INCLUDES = -I.
INCLUDES += -Ilib/cargs

SOURCES = main.c
SOURCES += lib/cargs/cargs.c

OBJS = $(SOURCES:.c=.o)

DBG_DIR = debug
DBG_EXE = $(DBG_DIR)/$(EXECUTABLE)
DBG_OBJS = $(addprefix $(DBG_DIR)/, $(OBJS))

REL_DIR = release
REL_EXE = $(REL_DIR)/$(EXECUTABLE)
REL_OBJS = $(addprefix $(REL_DIR)/, $(OBJS))

CC = gcc

CFLAGS =\
	-c\
	-std=c99\
	-Wall\
	-Wextra\
	-Wpedantic\
	-fsanitize=undefined\
	-fsanitize-undefined-trap-on-error\

CFLAGS_DBG =\
	-g3\
	-O0

CFLAGS_REL =\
	-O1\
	-DNDEBUG

LD = gcc

LDFLAGS =\
	-fsanitize=undefined\
	-fsanitize-undefined-trap-on-error

all: prepare release

debug: $(DBG_EXE)

$(DBG_EXE): $(DBG_OBJS)
	$(LD) $(LDFLAGS) -o $(DBG_EXE) $^

$(DBG_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) $(CFLAGS_DBG) -o $@ $<

release: $(REL_EXE)

$(REL_EXE): $(REL_OBJS)
	$(LD) $(LDFLAGS) -o $(REL_EXE) $^

$(REL_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) $(CFLAGS_REL) -o $@ $<

prepare:
	@mkdir -p $(DBG_DIR) $(REL_DIR)

clean:
	rm -rf $(REL_DIR)/* $(DBG_DIR)/*
