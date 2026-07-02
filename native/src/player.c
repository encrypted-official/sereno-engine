#include "player.h"

#include <stdlib.h>

PlayerCTX* player_create(void)
{
    PlayerCTX* p_ctx = malloc(sizeof(*p_ctx));

    if (p_ctx == NULL)
        return NULL;
    
    p_ctx->initialized = false;

    p_ctx->backend = NULL;
    p_ctx->decoder = NULL;

    p_ctx->paused = true;
    p_ctx->volume = 0.5f;

    return p_ctx;
}

void player_destroy(PlayerCTX* p_ctx)
{
    if (p_ctx == NULL)
        return;

    player_shutdown(p_ctx);
    free(p_ctx);
}

bool player_init(PlayerCTX* p_ctx)
{
    if (p_ctx == NULL)
        return false;

    if (p_ctx->initialized)
        return true;

    p_ctx->backend = backend_create();

    if (p_ctx->backend == NULL)
        goto fail;

    if (!backend_init(p_ctx->backend))
        goto fail;
    
    p_ctx->decoder = decoder_create();

    if (p_ctx->decoder == NULL)
        goto fail;

    if (!decoder_init(p_ctx->decoder))
        goto fail;

    p_ctx->initialized = true;
    return true;

    fail:
        player_shutdown(p_ctx);
        return false;
}

void player_shutdown(PlayerCTX* p_ctx)
{
    if (p_ctx == NULL)
        return;

    backend_shutdown(p_ctx->backend);
    backend_destroy(p_ctx->backend);
    p_ctx->backend = NULL;

    decoder_shutdown(p_ctx->decoder);
    decoder_destroy(p_ctx->decoder);
    p_ctx->backend = NULL;

    p_ctx->initialized = false;
}