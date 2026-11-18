CC      = gcc
PS4SDK ?= /lib/ps4-payload-sdk

CFLAGS  = -std=gnu11 -Wall -Wextra -O2 \
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
HEADERS = $(wildcard *.h)

.PHONY: all clean rebuild

all: $(TARGET)

# Force rebuild whenever main.c or any local header changes
$(TARGET): $(SOURCE) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o *.d

rebuild: clean all
