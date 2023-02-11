#pragma once
#ifndef ECS_H_
#define ECS_H_

using cmpId_type = int;
enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	_IMAGE,
	// ... (compoment ids)
	_HEALTH,
	_RANGE_BEHAVIOR,
	// do not remove this
	_LAST_CMP_ID
};
constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

#endif // !ECS_H_