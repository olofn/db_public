#include "core/generatorclip.hpp"
#include "core/core.hpp"

float GeneratorClip::getValue(int tick)
{
    switch (type)
    {
    case 0:
		//System::Console::WriteLine(sinf((tick / (float)period) * D3DX_PI * 2.0f));
        return sinf((tick / (float)period) * D3DX_PI * 2.0f);
    case 1:
        return cosf((tick / (float)period) * D3DX_PI * 2.0f);
    case 2: // Ramp up
        return ((tick % period) / (float)period) * 2.0f - 1.0f;
    case 3: // Ramp down
        return ((1.0f - (tick % period)) / (float)period) * 2.0f + 1.0f;
    case 4: // Sawtooth
        {
            float t = ((tick % period) / (float)period);
            if (t < 0.5f)
                return (t / 0.5f) * 2.0f - 1.0f;
            else
                return (2.0f - t / 0.5f) * 2.0f - 1.0f;
        }
    }
}
