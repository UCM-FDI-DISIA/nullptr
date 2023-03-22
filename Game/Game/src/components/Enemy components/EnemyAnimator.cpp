#include "EnemyAnimator.h"
EnemyAnimator::EnemyAnimator(EnemyBehaviour* enmyBhvr, string txtr_key, int sprtW,int sprtH, int rws, int cols, Animation idle, Animation mvment, Animation atck) :
	CharacterAnimator(&sdlutils().images().at(txtr_key),
		sprtW,sprtH,rws, cols,idle, mvment), _bhvr(nullptr){
	_bhvr = enmyBhvr;
	addAttack(atck, [&]() { return attacking(); });
}
void EnemyAnimator::initComponent() {
	CharacterAnimator::initComponent();
	assert(_bhvr != nullptr);
}