#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "backend.h"
#include "decoder.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PlayerCTX
{
    bool initialized;

    BackendCTX* backend;
    DecoderCTX* decoder;

    bool paused;
    float volume;

} PlayerCTX;

PlayerCTX* player_create(void);
void player_destroy(PlayerCTX* p_ctx);

bool player_init(PlayerCTX* p_ctx);
void player_shutdown(PlayerCTX* p_ctx);

#ifdef __cplusplus
}
#endif

#endif