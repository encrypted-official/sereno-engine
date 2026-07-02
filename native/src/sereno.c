#include "sereno.h"

#include <stdlib.h>

#include "library.h"
#include "player.h"

SerenoCTX* sereno_create(void)
{
    SerenoCTX* ctx = malloc(sizeof(*ctx));

    if (ctx == NULL)
        return NULL;

    ctx->initialized = false;

    ctx->library = NULL;
    ctx->player = NULL;

    return ctx;
}

void sereno_destroy(SerenoCTX* ctx)
{
    if (ctx == NULL)
        return;

    sereno_shutdown(ctx);
    free(ctx);
}

bool sereno_init(SerenoCTX* ctx)
{
    if (ctx == NULL)
        return false;

    if (ctx->initialized)
        return true;

    ctx->library = library_create();

    if (ctx->library == NULL)
        goto fail;

    if (!library_init(ctx->library))
        goto fail;

    ctx->player = player_create();
    
    if (ctx->player == NULL)
        goto fail;

    if (!player_init(ctx->player))
        goto fail;

    ctx->initialized = true;
    return true;

    fail:
        sereno_shutdown(ctx);
        return false;
}

void sereno_shutdown(SerenoCTX* ctx)
{
    if (ctx == NULL)
        return;

    library_shutdown(ctx->library);
    library_destroy(ctx->library);
    ctx->library = NULL;

    player_shutdown(ctx->player);
    player_destroy(ctx->player);
    ctx->player = NULL;

    ctx->initialized = false;
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