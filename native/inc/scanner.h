#ifndef SCANNER_H
#define SCANNER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SCANNER_SCAN_DEFAULT,
    SCANNER_SCAN_WITH_INC,
    SCANNER_SCAN_WITH_INC_EXC
} ScanType;

typedef struct ScannerCTX {
    bool initialized;
    char *incPathList[128];
    char *excPathList[128];
    char *pathList[2500];   // todo: make this malloc based.
} ScannerCTX;

/* control */
ScannerCTX* scanner_create(void);
void scanner_destroy(ScannerCTX* s_ctx);
bool scanner_init(ScannerCTX* s_ctx);
void scanner_shutdown(ScannerCTX* s_ctx);

/* commands */
bool scanner_scan_filepaths(ScannerCTX* s_ctx, ScanType type);

#ifdef __cplusplus
}
#endif
#endif