obj = test.o base64.o
cc = gcc
CFLAGS := -std=c99

base64 : $(obj)
	cc $(CFLAGS) -o base64 $(obj)

$(obj) : base64.h

.PHONY : clean
clean :
	rm base64 $(obj)
