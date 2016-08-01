#include "core/operators/randomselectionoperator.hpp"

void RandomSelectionOperator::process(int tick)
{
    if (mesh != 0)
        delete mesh;

	mesh = getInput(0)->mesh->clone();

	int probability = getByteProperty(0);
	int seed = getByteProperty(1);

    srand(seed);

	for (int i = 0; i < mesh->getNumFaces(); i++)
	{
        mesh->faceSelected(i) = (rand() % 255) < probability;
	}
}
