#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BackendCTX
{

} BackendCTX;

BackendCTX* backend_create(void);
void backend_destroy(BackendCTX* b_ctx);

bool backend_init(BackendCTX* b_ctx);
void backend_shutdown(BackendCTX* b_ctx);

#ifdef __cplusplus
}
#endif

#endif