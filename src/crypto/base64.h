#ifndef _BASE64_H_
#define _BASE64_H_

// adapted from https://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c
static char encoding_table[] =
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
   'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
   'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
   'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
   'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
   'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
   'w', 'x', 'y', 'z', '0', '1', '2', '3',
   '4', '5', '6', '7', '8', '9', '+', '/', '='};

#define BYTES_IN_U64 8
#define LAST_POS_IN_RESULT 11

void base64_encode_nonce(uint64_t nonce, char *encoded_data){
  char unsigned data[BYTES_IN_U64];
  for(int i = 0; i < BYTES_IN_U64; i++){
    data[i] = (unsigned char)(nonce & 0xFF);
    nonce >>= 8;
  }

  for(int i = 0, j = 0; i < BYTES_IN_U64;) {

    uint32_t octet_a = i < BYTES_IN_U64 ? data[i++] : 0;
    uint32_t octet_b = i < BYTES_IN_U64 ? data[i++] : 0;
    uint32_t octet_c = i < BYTES_IN_U64 ? data[i++] : 0;

    uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

    encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
  }

  // 8 bytes input means we need one byte padding
  encoded_data[LAST_POS_IN_RESULT] = '=';
}

#endif
