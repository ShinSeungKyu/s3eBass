/*
  Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#if !defined(_GAME_H_)
#define _GAME_H_

#include "misc/PfMacro.h"
#include "game/PfGame.h"

#define	GAME Game::getInstance()

class Game : public PfGame
{
	CDEFINE_SINGLETON(Game)
public:
	void Init(bool enable_http);
};

#endif // _GAME_H_
