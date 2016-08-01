#pragma once

class PlayerSkill
{
private:
	static float skill;

public:
	static void playerDidSomethingClever(float howClever, float howImportant);
	static void playerDidSomethingStupid(float howClever, float howImportant);
	static float get();
};