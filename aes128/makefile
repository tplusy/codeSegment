obj = aestest.o aes128.o
cc = gcc
CFLAGS := -std=c99

aes128 : $(obj)
	cc $(CFLAGS) -o aes128 $(obj)

$(obj) : aes128.h

.PHONY : clean
clean :
	rm aes128 $(obj)
