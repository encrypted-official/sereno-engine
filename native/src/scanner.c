#include "scanner.h"

#include <stdlib.h>

ScannerCTX* scanner_create(void)
{
    ScannerCTX* s_ctx = malloc(sizeof(*s_ctx));
    if (s_ctx == NULL) {return NULL;}

    return s_ctx;
}

void scanner_destroy(ScannerCTX* s_ctx)
{
    if (s_ctx == NULL) {return;}
    
    scanner_shutdown(s_ctx);
    free(s_ctx);
}
    
bool scanner_init(ScannerCTX* s_ctx)
{
    if (s_ctx == NULL) {return false;}
    
    return true;
}

void scanner_shutdown(ScannerCTX* s_ctx)
{
    if (s_ctx == NULL) {return;}
}
