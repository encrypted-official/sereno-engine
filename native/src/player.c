#include "player.h"

#include <stdlib.h>

PlayerCTX* player_create(void)
{
    PlayerCTX* p_ctx = malloc(sizeof(PlayerCTX));

    if (p_ctx == NULL)
    {
        return NULL;
    }
    
    p_ctx->initialized = false;
    p_ctx->songPaused = true;
    p_ctx->currentSong = 0;
    p_ctx->volume = 0.5f;

    return p_ctx;
}

void player_destroy(PlayerCTX* p_ctx)
{
    if (p_ctx == NULL)
    {
        return;
    }
    
    free(p_ctx);
}


bool player_initialize(PlayerCTX* p_ctx)
{
    if (p_ctx == NULL)
    {
        return false;
    }

    p_ctx->initialized = true;

    return true;
}

void player_shutdown(PlayerCTX* p_ctx)
{

}