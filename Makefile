CC = gcc
CFLAGS = -Wall -Wextra -O2 -I$(PS4_PAYLOAD_SDK)/include
LDFLAGS = -L$(PS4_PAYLOAD_SDK)/lib -T$(PS4_PAYLOAD_SDK)/linker.x -Wl,--build-id=none

TARGET = payload.bin
SOURCE = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
