obj = test.o utils.o
cc = gcc
CFLAGS := -std=c99

utils : $(obj)
	cc $(CFLAGS) -o utils $(obj)

$(obj) : utils.h

.PHONY : clean
clean :
	rm utils $(obj)
