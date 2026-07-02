#include "decoder.h"

#include <stdlib.h>

DecoderCTX* decoder_create(void)
{
    DecoderCTX* d_ctx = malloc(sizeof(*d_ctx));

    if (d_ctx == NULL)
        return NULL;

    return d_ctx;
}

void decoder_destroy(DecoderCTX* d_ctx)
{
    if (d_ctx == NULL)
        return;

    decoder_shutdown(d_ctx);
    free(d_ctx);
}

bool decoder_init(DecoderCTX* d_ctx)
{
    if (d_ctx == NULL)
        return false;

    return true;
}

void decoder_shutdown(DecoderCTX* d_ctx)
{
    if (d_ctx == NULL)
        return;
}