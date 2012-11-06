/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#include "Game.h"

CDECLARE_SINGLETON(Game)

void Game::Init(bool enable_http) {
    PfGame::Init(enable_http);
    
    //SetPfXomlPrefix("Debug_");
}

