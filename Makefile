CC      = gcc
PS4SDK ?= /lib/ps4-payload-sdk

CFLAGS  = -Wall -Wextra -O2 \
          -I$(PS4SDK)/libPS4/include \
          -nostartfiles -nostdlib -fno-builtin \
          -masm=intel -march=btver2 -mtune=btver2 \
          -m64 -mabi=sysv -mcmodel=small \
          -fpie -fPIC

LDFLAGS = -L$(PS4SDK)/libPS4 \
          -T$(PS4SDK)/libPS4/linker.x \
          -Wl,--build-id=none \
          -lPS4

TARGET  = payload.bin
SOURCE  = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
