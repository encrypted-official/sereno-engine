#include "library.h"

#include <stdlib.h>

LibraryCTX* library_create(void)
{
    LibraryCTX* l_ctx = malloc(sizeof(*l_ctx));

    if (l_ctx == NULL)
        return NULL;

    return l_ctx;
}

void library_destroy(LibraryCTX* l_ctx)
{
    if (l_ctx == NULL)
        return;

    library_shutdown(l_ctx);
    free(l_ctx);
}

bool library_init(LibraryCTX* l_ctx)
{
    if (l_ctx == NULL)
        return false;

    return true;
}

void library_shutdown(LibraryCTX* l_ctx)
{
    if (l_ctx == NULL)
        return;
}
