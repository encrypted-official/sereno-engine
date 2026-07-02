#include "sereno.h"
#include "player.h"

#include <stdlib.h>

SerenoCTX* sereno_create(void)
{
    SerenoCTX* ctx = malloc(sizeof(SerenoCTX));

    if (ctx == NULL)
    {
        return NULL;
    }

    ctx->initialized = false;
    ctx->player = NULL;

    return ctx;
}

void sereno_destroy(SerenoCTX* ctx)
{
    if (ctx == NULL)
    {
        return;
    }

    player_destroy(ctx->player);
    ctx->player = NULL;

    free(ctx);
}

bool sereno_initialize(SerenoCTX* ctx)
{
    if (ctx == NULL)
    {
        return false;
    }

    if (ctx->initialized)
    {
        return true;
    }

    ctx->player = player_create();
    
    if (ctx->player == NULL)
    {
        return false;
    }

    if (!player_initialize(ctx->player))
    {
        player_destroy(ctx->player);
        ctx->player = NULL;
        return false;
    }

    ctx->initialized = true;

    return true;
}

void sereno_shutdown(SerenoCTX* ctx)
{

}

int sereno_version_major(void)
{
    return SERENO_VERSION_MAJOR;
}

int sereno_version_minor(void)
{
    return SERENO_VERSION_MINOR;
}

int sereno_version_patch(void)
{
    return SERENO_VERSION_PATCH;
}