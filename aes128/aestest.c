#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "aes128.h"

void dump_buffer(uint8_t *out, int len)
{
	uint8_t buffer[512] = {0};
	uint8_t *ptr = out;
	uint8_t *end = out+len;
	uint16_t count = 0;
	uint16_t i = 0;

	for(; ptr < end && i < 512; ptr++) {
		uint8_t low = *ptr %16;
		uint8_t high = *ptr >> 4;
		
		if(high < 10) {
			buffer[i++] = high+'0';
		} else {
			buffer[i++] = 'A' + high - 10;
		}
		if(low < 10) {
			buffer[i++] = low+'0';
		} else {
			buffer[i++] = 'A' + low -10;
		}
	}

	fprintf(stdout, "%s\n\n", buffer);
}

void get_data(uint8_t *in, uint32_t in_len, uint8_t*out, uint32_t *out_len)
{
	uint8_t *ptr = in;
	uint8_t *p = out;

	for(; ptr < in + in_len; ptr +=2)
	{
		uint8_t a = *ptr;
		uint8_t b = *(ptr+1);

		if(a >='0' && a <= '9')
		{
			a = a - '0';
		}
		else if(a >= 'A' && a <= 'F')
		{
			a = a - 'A' + 10;
		}

		if(b >='0' && b <= '9')
		{
			b = b - '0';
		}
		else if(b >= 'A' && b <= 'F')
		{
			b = b - 'A' + 10;
		}

		*p = a * 16 + b;
		p += 1;
	}
	*out_len = in_len / 2;
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		fprintf(stdout, "usage: %s [ed] [text] [key]\n", argv[0]);
		return 1;
	}

	if(strncmp(argv[1], "e", 1) == 0)
	{
		uint8_t buf[1024] = {0};
		uint32_t out_len = sizeof(buf);
		fprintf(stdout, "text:%s\ntext len:%d\n", argv[2], (int)strlen(argv[2]));
		fprintf(stdout, "key:%s\n\n", argv[3]);
		AES128_EncryptECB(MODE_PKCS7_PADDING, argv[2], strlen(argv[2]), buf, &out_len, argv[3]);
		fprintf(stdout, "encrypted text[%d]:\n", out_len);
		dump_buffer(buf, out_len);
	}
	else if(strncmp(argv[1], "d", 1) == 0)
	{
		uint8_t buf_in[1024] = {0};
		uint8_t buf_out[1024] = {0};
		uint32_t out_len = sizeof(buf_in);
		uint32_t in_len = strlen(argv[2]);

		uint32_t t1 = 0;
		uint32_t t2 = 0;

		fprintf(stdout, "text:%s\nencrypted text len:%d\n", argv[2], (int)strlen(argv[2]));
		fprintf(stdout, "key:%s\n\n", argv[3]);
		fprintf(stdout, "in_len =%d\n", in_len);
		get_data(argv[2], in_len, buf_in, &in_len);
		dump_buffer(buf_in, in_len);
		fprintf(stdout, "in_len =%d\n", in_len);
		AES128_DecryptECB(MODE_PKCS7_PADDING, buf_in, in_len, buf_out, &out_len, argv[3]);
		fprintf(stdout, "decrypted text:\n");
		dump_buffer(buf_out, out_len);

		t1 = ((buf_out[0]*256 + buf_out[1])*256 + buf_out[2])*256 + buf_out[3];
		t2 = ((buf_out[4]*256 + buf_out[5])*256 + buf_out[6])*256 + buf_out[7];

		fprintf(stdout, "t_start=%u, t_end=%u\n", t2, t1);
	}
	else
	{
		fprintf(stderr, "the first param mustbe 'e' or 'd'\n");
	}
}
