#include <stdio.h>

#include "sereno.h"

int main(void)
{
    SerenoCTX* ctx = sereno_create();

    if (ctx == NULL)
    {
        printf("Failed to create Sereno context.\n");
        return 1;
    }

    if (!sereno_init(ctx))
    {
        printf("Initialization failed.\n");

        sereno_destroy(ctx);
        return 1;
    }

    printf("Sereno %d.%d.%d\n",
        sereno_version_major(),
        sereno_version_minor(),
        sereno_version_patch());

    printf("Initialization successful.\n");

    sereno_scan_library(ctx);

    sereno_shutdown(ctx);
    sereno_destroy(ctx);

    return 0;
}