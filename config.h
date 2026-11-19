#pragma once

#include "target.h"

#define UI_BUFFER_SIZE 16
#define TIMEATTACK_N_TARGETS 20

#define GAME_FUNC(f) timeattack##_##f
#define GAME_SETUP GAME_FUNC(setup)
#define GAME_UPDATE GAME_FUNC(update)

extern Target TARGETS[];
extern size_t NTARGETS;