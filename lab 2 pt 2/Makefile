CC = gcc
CFLAGS = -Wall -gcc
all: signal timer

signals: signal.c 
  $(CC) $(CFLAGS) signal.c -o signalab

timer: timer.c 
  $(CC) $(CFLAGS) timer.c -o timer

clean:
  rm -f Signalab timer
