#ifndef SERENO_H
#define SERENO_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SERENO_VERSION_MAJOR 0
#define SERENO_VERSION_MINOR 1
#define SERENO_VERSION_PATCH 0

typedef struct LibraryCTX LibraryCTX;
typedef struct PlayerCTX PlayerCTX;

typedef struct SerenoCTX
{
    bool initialized;
    
    LibraryCTX* library;
    PlayerCTX* player;

} SerenoCTX;

SerenoCTX* sereno_create(void);
void sereno_destroy(SerenoCTX* ctx);

bool sereno_init(SerenoCTX* ctx);
void sereno_shutdown(SerenoCTX* ctx);

int sereno_version_major(void);
int sereno_version_minor(void);
int sereno_version_patch(void);

#ifdef __cplusplus
}
#endif

#endif