#pragma once

#include "core/externals.hpp"
#include "core/globals.hpp"
#include "core/texture.hpp"
#include "core/mesh.hpp"

#define DB_MAX_OPERATOR_CONNECTIONS 32
#define DB_MAX_OPERATOR_PROPERTIES 32
#define DB_MAX_TIMELINE_CLIPS 64
#define DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH 1024

class Operator
{
public:
    Operator();
#ifdef DB_EDITOR
    virtual ~Operator();
#endif

#ifdef DB_EDITOR
    virtual void renderInEditor();
#endif

    Operator* getInput(int index);
    
    virtual void cascadeProcess(int tick);
    virtual void process(int tick) = 0;
    virtual void render();

    unsigned char getByteProperty(int index);
    int getIntProperty(int index);
    float getFloatProperty(int index);
    const char* getStringProperty(int index);
    D3DXCOLOR getColorProperty(int index);
    D3DXVECTOR3 getVectorProperty(int index);

    bool isDirty();
    void setDirty(bool dirty);
    
    virtual void broadcastChannelValue(int channel, float value);

    Mesh* mesh;
    Texture* texture;
    int ticks;
    int timelineClips[DB_MAX_TIMELINE_CLIPS];
    int numberOfClips;

    struct Property
    {
        unsigned char byteValue;
        int intValue;
        float floatValue;
        char stringValue[DB_MAX_OPERATOR_STRING_PROPERTY_LENGTH];
        D3DXCOLOR colorValue;
        D3DXVECTOR3 vectorValue;
        unsigned char channel1;
        unsigned char channel2;
        unsigned char channel3;
        float amplify1;
        float amplify2;
        float amplify3;
        float channelValue1;
        float channelValue2;
        float channelValue3;
    };

    Property properties[DB_MAX_OPERATOR_PROPERTIES];
    short inputs[DB_MAX_OPERATOR_CONNECTIONS];
    short outputs[DB_MAX_OPERATOR_CONNECTIONS];
    unsigned char numberOfInputs;
    unsigned char numberOfOutputs;
    bool dirty;

#ifdef DB_EDITOR
    virtual void deviceLost();
#endif
};