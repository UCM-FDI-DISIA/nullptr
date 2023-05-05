#include "BossAnimator.h"
#include "../../data/constants.h"
#include "BossBehaviour.h"

BossAnimator::BossAnimator(string txtr_key, int sprtW, int sprtH, int rws, int cols, Animation idle)
	: CharacterAnimator(SDLApplication::getTexture(txtr_key), sprtW, sprtH, rws, cols, idle, idle) {
}

void BossAnimator::initComponent() {

	Image::initComponent();

	_bhvr = gObj->getComponent<BossBehaviour>();

	//crear animaciones de BulletHell y Grenade.
	addAction(BOSS_ENEMY_BULLETHELL_KEY, BOSS_ENEMY_BULLETHELL_ANIMATION,
		[&]() {return _bhvr->getBossState() == boss_BHELL; }
	);

	addAction(BOSS_ENEMY_GRENADE_ATTACK_KEY, BOSS_ENEMY_GRENADE_ATTACK_ANIMATION,
		[&]() {return _bhvr->getBossState() == boss_GRENADE; }
	);
	
	addAction(BOSS_ENEMY_COMBINED_ATTACK_KEY, BOSS_ENEMY_COMBINED_ATTACK_ANIMATION,
		[&]() {return _bhvr->getBossState() == boss_COMBINED; }
	);

}