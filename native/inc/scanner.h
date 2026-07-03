#ifndef SCANNER_H
#define SCANNER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScannerCTX
{
    bool initialized;

} ScannerCTX;

ScannerCTX* scanner_create(void);
void scanner_destroy(ScannerCTX* s_ctx);

bool scanner_init(ScannerCTX* s_ctx);
void scanner_shutdown(ScannerCTX* s_ctx);

bool scanner_scan_all(ScannerCTX* s_ctx);

#ifdef __cplusplus
}
#endif

#endif