#ifndef __BASE64_H
#define __BASE64_H

extern void base64_encrypt_text(const char *pbuf, int plen);
extern void base64_decrypt_text(const char * cbuf,int clen);

extern void show_base64(const char * buf, int len);
extern void show_binary(const char * buf, int len);

#endif //__BASE64_H

