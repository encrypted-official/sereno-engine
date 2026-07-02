#ifndef DECODER_H
#define DECODER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DecoderCTX
{

} DecoderCTX;

DecoderCTX* decoder_create(void);
void decoder_destroy(DecoderCTX* d_ctx);

bool decoder_init(DecoderCTX* d_ctx);
void decoder_shutdown(DecoderCTX* d_ctx);

#ifdef __cplusplus
}
#endif

#endif