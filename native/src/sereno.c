#include "sereno.h"

#include <stdlib.h>

#include "library.h"
#include "player.h"
#include "scanner.h"

SerenoCTX* sereno_create(void)
{
    SerenoCTX* ctx = malloc(sizeof(*ctx));

    if (ctx == NULL)
        return NULL;

    ctx->initialized = false;

    ctx->library = NULL;
    ctx->player = NULL;
    ctx->scanner = NULL;

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

    ctx->scanner = scanner_create();

    if (ctx->scanner == NULL)
        goto fail;

    if (!scanner_init(ctx->scanner))
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

    scanner_shutdown(ctx->scanner);
    scanner_destroy(ctx->scanner);
    ctx->scanner = NULL;

    ctx->initialized = false;
}

bool sereno_scan_library(SerenoCTX* ctx)
{
    if (ctx == NULL)
        return false;

    return scanner_scan_all(ctx->scanner);
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