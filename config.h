#pragma once

#include "target.h"

#include "timeattack.h"
#include "scoreattack.h"

#define UI_BUFFER_SIZE 32
#define TIMEATTACK_N_TARGETS 20
#define SCOREATTACK_DURATION 30000

#define GAME_NAMESPACE ScoreAttack
#define GAME_SETUP GAME_NAMESPACE::setup
#define GAME_UPDATE GAME_NAMESPACE::update

extern Target TARGETS[];
extern size_t NTARGETS;