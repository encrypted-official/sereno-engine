#include "backend.h"

#include <stdlib.h>

BackendCTX* backend_create(void)
{
    BackendCTX* b_ctx = malloc(sizeof(*b_ctx));

    if (b_ctx == NULL)
        return NULL;

    return b_ctx;
}

void backend_destroy(BackendCTX* b_ctx)
{
    if (b_ctx == NULL)
        return;

    backend_shutdown(b_ctx);
    free(b_ctx);
}

bool backend_init(BackendCTX* b_ctx)
{
    if (b_ctx == NULL)
        return false;

    return true;
}

void backend_shutdown(BackendCTX* b_ctx)
{
    if (b_ctx == NULL)
        return;
}