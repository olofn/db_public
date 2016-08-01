#include "core/graphicsloader.hpp"
#include "64k/graphicsdata.hpp"
#include "core/core.hpp"
#define OPERATOR_HEADERS 1
#include "core/operators.hpp"
#undef OPERATOR_HEADERS
#include "core/generatorclip.hpp"
#include "core/splineclip.hpp"

// I know this piece of code doesn't look very pretty, but hey, it works!

// We define a couple of macros we don't need (they are used
// for the editor) to do nothing.
#define DEF_OP_FOR_EDITOR(opNumber, opNameChars, opClass, opType)
#define ADD_BYTE_PROP(name, value)
#define ADD_INT_PROP(name, value)
#define ADD_FLOAT_PROP(name, value)
#define ADD_STRING_PROP(name, value)
#define ADD_TEXT_PROP(name, value)
#define ADD_COLOR_PROP(name, r, g, b)
#define ADD_VECTOR_PROP(name, x, y, z)
#define ADD_ENUM_PROP(name, enumValues, value)
#define ADD_INPUT(inType)
#define ADD_INFINITE_INPUT(inType)
#define ADD_OPTIONAL_INPUT(inType)
#define END_OP_FOR_EDITOR()

// We define the DEF_OP_LOADER macro to retrieve information about operators,
// such as number of properties, property types etc...
#define DEF_OP_FOR_LOADER(opNumber, opClass, _numberOfConstantInputs, _numberOfProperties, ...) \
    unsigned char opClass##NumberOfProperties = _numberOfProperties; \
    unsigned char opClass##PropertyTypes[_numberOfProperties] = {__VA_ARGS__}; \
    char opClass##NumberOfConstantInputs = _numberOfConstantInputs;
#define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opNumber, opClass, _numberOfConstantInputs) \
     char opClass##NumberOfConstantInputs = _numberOfConstantInputs;
// We includes all operator defines to create the variables.
#define OPERATOR_DEFINES 1
#include "core/operators.hpp"
#undef OPERATOR_DEFINES

unsigned char findLowestOperatorType(short type)
{
    unsigned char result = 255;
    for (int i = 0; i < coreNumberOfOperators; i++)
    {
        short index = i + 2;
        if (graphicsData[index] < result && graphicsData[index] > type)
            result = graphicsData[index];
    }

    return result;
}

short findNextIndexOfOperatorType(short type, short index)
{    
    for (int i = 0; i < coreNumberOfOperators; i++)
    {
        if (i > index && graphicsData[i + 2] == type)
            return i;
    }

    return -1;
}

/**
 * Loads the graphics by going through the graphics data in the graphicsdata.hpp header.
 */
void loadGraphics()
{
    unsigned char* dataptr = graphicsData;

    // Loop through all operators and create them. Also retrieve information
    // about the operators.
    coreNumberOfOperators = *dataptr;
    dataptr += 2;

    // These variables contain information about the operators.
    unsigned char* instanceNumberOfProperties = new unsigned char[coreNumberOfOperators];
    int* instancePropertyTypes = new int[coreNumberOfOperators];
    char* instanceNumberOfConstantInputs = new char[coreNumberOfOperators];

    for (short operatorIndex = 0; operatorIndex < coreNumberOfOperators; operatorIndex++)
    {
        unsigned char id = *dataptr++;
        // We redefine the macros to instanciate operators and fill the instance variables with values.
    #undef DEF_OP_FOR_LOADER
    #undef DEF_OP_FOR_LOADER_WITH_NO_PROPS
    #define DEF_OP_FOR_LOADER(opNumber, opClass, _numberOfConstantInputs, _numberOfProperties, ...) \
        if (opNumber == id) \
        {\
            coreOperators[operatorIndex] = new opClass##();\
            instanceNumberOfProperties[operatorIndex] = opClass##NumberOfProperties;\
            instancePropertyTypes[operatorIndex] =  (int)opClass##PropertyTypes;\
            instanceNumberOfConstantInputs[operatorIndex] = opClass##NumberOfConstantInputs;\
        }
    #define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opNumber, opClass, _numberOfConstantInputs)\
        if (opNumber == id) \
        {\
            coreOperators[operatorIndex] = new opClass##();\
            instanceNumberOfProperties[operatorIndex] = 0;\
            instanceNumberOfConstantInputs[operatorIndex] = opClass##NumberOfConstantInputs;\
        }
    #define OPERATOR_DEFINES 1
    #include "core/operators.hpp"
    #undef OPERATOR_DEFINES
    }

    // Load the operators properties
    short operatorType = -1;
    while (true)
    {
        operatorType = findLowestOperatorType(operatorType);

        if (operatorType == 255)
            break;

        short operatorIndex = findNextIndexOfOperatorType(operatorType, -1);
        unsigned char numberOfProperties = instanceNumberOfProperties[operatorIndex];
        operatorIndex = -1;
        for (unsigned char propertyIndex = 0; 
             propertyIndex < numberOfProperties; 
             propertyIndex++)
        {
            while (true)
            {        
                operatorIndex = findNextIndexOfOperatorType(operatorType, operatorIndex);

                if (operatorIndex < 0)
                    break;

                Operator* op =  coreOperators[operatorIndex];
                unsigned char* propertyTypes = (unsigned char*)instancePropertyTypes[operatorIndex];
                unsigned char propertyType = propertyTypes[propertyIndex];
                switch (propertyType)
                {
                case 0: // Byte
                    op->properties[propertyIndex].byteValue = *dataptr++;
                    break;
                case 1: // Int
                    op->properties[propertyIndex].intValue = *(reinterpret_cast<short*>(dataptr));
                    dataptr += 2;
                    break;
                case 2: // Float
                    op->properties[propertyIndex].floatValue = *(reinterpret_cast<float*>(dataptr));
                    dataptr += 4;
                    break;
                case 3: // Color
                    op->properties[propertyIndex].colorValue.r = *dataptr++ / 256.0f;
                    op->properties[propertyIndex].colorValue.g = *dataptr++ / 256.0f;
                    op->properties[propertyIndex].colorValue.b = *dataptr++ / 256.0f;
                    break;
                case 4: // Vector
                    {
                    float x = *(reinterpret_cast<float*>(dataptr));
                    dataptr += 4;
                    float y = *(reinterpret_cast<float*>(dataptr));
                    dataptr += 4;
                    float z = *(reinterpret_cast<float*>(dataptr));
                    dataptr += 4;
                    op->properties[propertyIndex].vectorValue = D3DXVECTOR3(x, y, z);
                    break;
                    }
                case 5: // String
                    {
                    unsigned short length = *(reinterpret_cast<unsigned short*>(dataptr));
                    dataptr += 2;
                    for (unsigned short charIndex = 0; charIndex < length; charIndex++)
                        op->properties[propertyIndex].stringValue[charIndex] = *dataptr++;
                    op->properties[propertyIndex].stringValue[length] = '\0';
                    break;
                    }
                   
                }
            }
           
        }
    }
    // Load the operators inputs
    unsigned char* instanceNumberOfInputs = new unsigned char[coreNumberOfOperators];
    for (unsigned short operatorIndex = 0; operatorIndex < coreNumberOfOperators; operatorIndex++)
    {
        if (instanceNumberOfConstantInputs[operatorIndex] == -1)
            instanceNumberOfInputs[operatorIndex] = *dataptr++;
        else
            instanceNumberOfInputs[operatorIndex] = instanceNumberOfConstantInputs[operatorIndex];
    }
   
    for (unsigned short operatorIndex = 0; operatorIndex < coreNumberOfOperators; operatorIndex++)
    {
        unsigned char numberOfInputs = instanceNumberOfInputs[operatorIndex];
        short inputIndex;

        while(numberOfInputs > 0)
        {
            if (numberOfInputs == instanceNumberOfInputs[operatorIndex])
                inputIndex = (*(reinterpret_cast<short*>(dataptr))) + operatorIndex;
            else
                inputIndex += *(reinterpret_cast<short*>(dataptr));

            dataptr+=2;
            coreOperators[operatorIndex]->inputs[coreOperators[operatorIndex]->numberOfInputs] = inputIndex;
            coreOperators[operatorIndex]->numberOfInputs++;
            coreOperators[inputIndex]->outputs[coreOperators[inputIndex]->numberOfOutputs] = operatorIndex;
            coreOperators[inputIndex]->numberOfOutputs++;
            numberOfInputs--;
        }
    }
   
    // Load the operator's animations
    unsigned short numberOfAnimations = *(reinterpret_cast<unsigned short*>(dataptr));
    dataptr+=2;
    unsigned short* animationOperatorIndexes = new unsigned short[numberOfAnimations];
    unsigned char* animationPropertyIndexes = new unsigned char[numberOfAnimations];
    for (unsigned short animationIndex = 0; animationIndex < numberOfAnimations; animationIndex++)
    {
        unsigned short index = *(reinterpret_cast<unsigned short*>(dataptr));
        animationOperatorIndexes[animationIndex] = index;
        dataptr+=2;
    }
    for (unsigned short animationIndex = 0; animationIndex < numberOfAnimations; animationIndex++)
    {
        unsigned char index = *dataptr++;
        animationPropertyIndexes[animationIndex] = index;
    }
    for (unsigned short animationIndex = 0; animationIndex < numberOfAnimations; animationIndex++)
    {
        Operator* op = coreOperators[animationOperatorIndexes[animationIndex]];
        unsigned char propertyIndex = animationPropertyIndexes[animationIndex];
        op->properties[propertyIndex].channel1 = *dataptr++;
    }
    for (unsigned short animationIndex = 0; animationIndex < numberOfAnimations; animationIndex++)
    {
        Operator* op = coreOperators[animationOperatorIndexes[animationIndex]];
        unsigned char propertyIndex = animationPropertyIndexes[animationIndex];
        op->properties[propertyIndex].channel2 = *dataptr++;
    }
    for (unsigned short animationIndex = 0; animationIndex < numberOfAnimations; animationIndex++)
    {
        Operator* op = coreOperators[animationOperatorIndexes[animationIndex]];
        unsigned char propertyIndex = animationPropertyIndexes[animationIndex];
        op->properties[propertyIndex].channel3 = *dataptr++;
    }
    for (unsigned short animationIndex = 0; animationIndex < numberOfAnimations; animationIndex++)
    {
        Operator* op = coreOperators[animationOperatorIndexes[animationIndex]];
        unsigned char propertyIndex = animationPropertyIndexes[animationIndex];
        op->properties[propertyIndex].amplify1 = *(reinterpret_cast<float*>(dataptr));
        dataptr += 4;
    }
    for (unsigned short animationIndex = 0; animationIndex < numberOfAnimations; animationIndex++)
    {
        Operator* op = coreOperators[animationOperatorIndexes[animationIndex]];
        unsigned char propertyIndex = animationPropertyIndexes[animationIndex];
        op->properties[propertyIndex].amplify2 = *(reinterpret_cast<float*>(dataptr));
        dataptr += 4;
    }
    for (unsigned short animationIndex = 0; animationIndex < numberOfAnimations; animationIndex++)
    {
        Operator* op = coreOperators[animationOperatorIndexes[animationIndex]];
        unsigned char propertyIndex = animationPropertyIndexes[animationIndex];
        op->properties[propertyIndex].amplify3 = *(reinterpret_cast<float*>(dataptr));
        dataptr += 4;
    }

    // Load timelines
    unsigned short numberOfTimelines = *(reinterpret_cast<unsigned short*>(dataptr));
    dataptr+=2;
    // Timeline indexes
    unsigned short* timelineOperatorIndexes = new unsigned short[numberOfAnimations];
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned short index = *(reinterpret_cast<unsigned short*>(dataptr));
        timelineOperatorIndexes[timelineIndex] = index;
        dataptr+=2;
    }
    // Timeline ticks
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned short beats = *(reinterpret_cast<unsigned short*>(dataptr));
        coreOperators[timelineOperatorIndexes[timelineIndex]]->ticks = beats * DB_TICKS_PER_BEAT;
        dataptr+=2;
    }
    unsigned short numberOfClips = 0;
    // Creating generators
    unsigned char* timelineNumberOfGenerators = new unsigned char[numberOfAnimations];
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = *dataptr++;
        timelineNumberOfGenerators[timelineIndex] = numberOfGenerators;
        for (unsigned short i = 0; i < numberOfGenerators; i++)
        {
            GeneratorClip* clip = new GeneratorClip();
            coreClips[numberOfClips] = clip;
            coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[coreOperators[timelineOperatorIndexes[timelineIndex]]->numberOfClips] = numberOfClips;
            coreOperators[timelineOperatorIndexes[timelineIndex]]->numberOfClips++;
            numberOfClips++;
        }
    }
    // Creating splines
    unsigned char* timelineNumberOfSplines = new unsigned char[numberOfAnimations];
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfSplines = *dataptr++;
        timelineNumberOfSplines[timelineIndex] = numberOfSplines;
        for (unsigned short i = 0; i < numberOfSplines; i++)
        {
            SplineClip* clip = new SplineClip();
            coreClips[numberOfClips] = clip;
            coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[coreOperators[timelineOperatorIndexes[timelineIndex]]->numberOfClips] = numberOfClips;
            coreOperators[timelineOperatorIndexes[timelineIndex]]->numberOfClips++;
            numberOfClips++;
        }
    }
    // Clip start
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        unsigned char numberOfSplines = timelineNumberOfSplines[timelineIndex];
        for (unsigned short i = 0; i < numberOfGenerators + numberOfSplines; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[i];
            coreClips[clipId]->start = *(reinterpret_cast<unsigned short*>(dataptr)) * DB_TICKS_PER_BEAT;
            dataptr += 2;
        }
    }
    // Clip end
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        unsigned char numberOfSplines = timelineNumberOfSplines[timelineIndex];
        for (unsigned short i = 0; i < numberOfGenerators + numberOfSplines; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[i];
            coreClips[clipId]->end = *(reinterpret_cast<unsigned short*>(dataptr)) * DB_TICKS_PER_BEAT;
            dataptr += 2;   
        }
    }
    // Clip channels
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        unsigned char numberOfSplines = timelineNumberOfSplines[timelineIndex];
        for (unsigned short i = 0; i < numberOfGenerators + numberOfSplines; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[i];
            unsigned char channel = *dataptr++;
            coreClips[clipId]->channel = channel;
        }
    }
    // Generator type
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        for (unsigned short i = 0; i < numberOfGenerators; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[i];
            ((GeneratorClip*)coreClips[clipId])->type = *dataptr++;   
        }
    }
    // Generator period
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        for (unsigned short i = 0; i < numberOfGenerators; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[i];
            ((GeneratorClip*)coreClips[clipId])->period = *(reinterpret_cast<unsigned short*>(dataptr));
            dataptr += 2;
        }
    }
    // Spline type
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        unsigned char numberOfSplines = timelineNumberOfSplines[timelineIndex];
        for (unsigned short i = 0; i < numberOfSplines; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[numberOfGenerators + i];
            ((SplineClip*)coreClips[clipId])->type = *dataptr++;   
        }
    }
    // Spline number of control points
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        unsigned char numberOfSplines = timelineNumberOfSplines[timelineIndex];
        for (unsigned short i = 0; i < numberOfSplines; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[numberOfGenerators + i];
            unsigned char numberOfControlPoints = *dataptr++;
            ((SplineClip*)coreClips[clipId])->numberOfControlPoints = numberOfControlPoints;   
        }
    }
     // Spline ticks
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        unsigned char numberOfSplines = timelineNumberOfSplines[timelineIndex];
        for (unsigned short i = 0; i < numberOfSplines; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[numberOfGenerators + i];
            SplineClip* clip = (SplineClip*)coreClips[clipId]; 

            int lastTick = 0;
            for (unsigned char controlPointIndex = 0; controlPointIndex < clip->numberOfControlPoints; controlPointIndex++)
            {
                clip->controlPoints[controlPointIndex].tick = *(reinterpret_cast<int*>(dataptr)) + lastTick;
                lastTick = clip->controlPoints[controlPointIndex].tick;
                dataptr += 4;
            }
        }
    }
    // Spline values
    for (unsigned short timelineIndex = 0; timelineIndex < numberOfTimelines; timelineIndex++)
    {
        unsigned char numberOfGenerators = timelineNumberOfGenerators[timelineIndex];
        unsigned char numberOfSplines = timelineNumberOfSplines[timelineIndex];
        for (unsigned short i = 0; i < numberOfSplines; i++)
        {
            unsigned short clipId = coreOperators[timelineOperatorIndexes[timelineIndex]]->timelineClips[i + numberOfGenerators];
            SplineClip* clip = (SplineClip*)coreClips[clipId]; 

            short lastValue = 0;
            for (unsigned char controlPointIndex = 0; controlPointIndex < clip->numberOfControlPoints; controlPointIndex++)
            {
                char value = *dataptr++;
                clip->controlPoints[controlPointIndex].value = value + lastValue; 
                lastValue = value;
            }
        }
    }
}