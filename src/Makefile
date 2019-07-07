TARGET=pongix

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

LDFLAGS = -lm -lSDL_net -lSDL_image -lSDL

all: $(TARGET)

$(TARGET): $(OBJS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe $(TARGET).elf *.s *.o
