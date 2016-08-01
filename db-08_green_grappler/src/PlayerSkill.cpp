#include "Precompiled.hpp"
#include "PlayerSkill.hpp"

#include <iostream>

float PlayerSkill::skill = 0.5f;

void PlayerSkill::playerDidSomethingClever(float howClever, float howImportant)
{
	if (howClever > skill) {
		skill = lerp(skill, howClever, howImportant);
	}
	std::cout << "Player skill: " << skill << std::endl;
}

void PlayerSkill::playerDidSomethingStupid(float howClever, float howImportant)
{
	if (howClever < skill) {
		skill = lerp(skill, howClever, howImportant);
	}
	std::cout << "Player skill: " << skill << std::endl;
}

float PlayerSkill::get()
{
	return skill;
}