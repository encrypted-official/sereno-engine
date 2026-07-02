#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PlayerCTX
{
    bool initialized;
    bool songPaused;
    int currentSong;
    float volume;

} PlayerCTX;

PlayerCTX* player_create(void);
void player_destroy(PlayerCTX* p_ctx);

bool player_initialize(PlayerCTX* p_ctx);
void player_shutdown(PlayerCTX* p_ctx);

#ifdef __cplusplus
}
#endif

#endif