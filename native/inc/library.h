#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LibraryCTX
{

} LibraryCTX;

LibraryCTX* library_create(void);
void library_destroy(LibraryCTX* l_ctx);

bool library_init(LibraryCTX* l_ctx);
void library_shutdown(LibraryCTX* l_ctx);

#ifdef __cplusplus
}
#endif

#endif