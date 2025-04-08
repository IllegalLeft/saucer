TARGET	= saucer
SOURCES = src/
LIBS	=
CC	= gcc
CFLAGS	= -g -Wall


.PHONY: default all clean
.PRECIOUS: $(TARGET) $(OBJECTS)


default: $(TARGET)
all: default


CFILES = $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
OBJECTS = $(patsubst %.c, %.o, $(wildcard $(SOURCES)*.c))

HEADERS = $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.h)))


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f $(SOURCES)*.o
	-rm -f $(TARGET)
