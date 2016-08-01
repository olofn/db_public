//#include <stdio.h> 
//#include <stdlib.h>
#include <vcclr.h>
#include "cli/Core.hpp"
#include "cli/Color.hpp"
#include "cli/CoreOperator.hpp"
#include "cli/CoreOperatorInput.hpp"
#include "cli/CoreOperatorProperty.hpp"
#include "cli/Vector.hpp"

namespace Verkstan
{
    CoreOperator::CoreOperator(unsigned char number,
                               String^ name,
                               unsigned short operatorId,
                               Constants::OperatorTypes type)
    {
        this->number = number;
        this->name = name;
        this->id = operatorId;
        this->type = type;
        this->properties = gcnew List<CoreOperatorProperty^>(); 
        this->inputs = gcnew List<CoreOperatorInput^>();
    }

    CoreOperator::~CoreOperator()
    {
        delete Core::coreOperators[id];
        Core::coreOperators[id] = 0;
    }

    unsigned char CoreOperator::Number::get()
    {
        return number;
    }

    unsigned short CoreOperator::Id::get()
    {
        return id;
    }

    String^ CoreOperator::Name::get()
    {
        return name;
    }

    short CoreOperator::NumberOfConstantInputs::get()
    {
        short result = 0;
        for (int i = 0; i < inputs->Count; i++)
        {
            CoreOperatorInput^ input = inputs[i];

            if (input->Infinite || input->Optional)
                return -1;

            result++;
        }

        return result;
    }

    List<CoreOperatorProperty^>^ CoreOperator::Properties::get() 
    {
        return properties;
    }

    List<CoreOperatorInput^>^ CoreOperator::Inputs::get() 
    {
        return inputs;
    }

    Constants::OperatorTypes CoreOperator::Type::get() 
    {
        return type;
    }

    void CoreOperator::AddProperty(String^ name, Constants::OperatorPropertyTypes type)
    {
        CoreOperatorProperty^ prop = gcnew CoreOperatorProperty(properties->Count,
                                                        name,
                                                        type);
        properties->Add(prop);
    }

    void CoreOperator::AddEnumProperty(String^ name, List<String^>^ values)
    {
        CoreOperatorProperty^ prop = gcnew CoreOperatorProperty(properties->Count,
                                                        name,
                                                        Constants::OperatorPropertyTypes::Enum,
                                                        values);
        properties->Add(prop);
    }

    void CoreOperator::AddInput(Constants::OperatorTypes type, bool infinite, bool optional)
    {
        CoreOperatorInput^ input = gcnew CoreOperatorInput(inputs->Count, type, infinite, optional);
        inputs->Add(input);
    }

    unsigned char CoreOperator::GetByteProperty(int index)
    {
        return getOperator()->properties[index].byteValue;
    }

    void CoreOperator::SetByteProperty(int index, unsigned char value)
    {
        getOperator()->properties[index].byteValue = value; 
        getOperator()->setDirty(true);
        getOperator()->properties[index].channelValue1 = 0.0f;
    }

    int CoreOperator::GetIntProperty(int index)
    {
         return getOperator()->properties[index].intValue;
    }

    void CoreOperator::SetIntProperty(int index, int value)
    {
        getOperator()->properties[index].intValue = value; 
        getOperator()->setDirty(true);
        getOperator()->properties[index].channelValue1 = 0.0f;
    }

    float CoreOperator::GetFloatProperty(int index)
    {
        return getOperator()->properties[index].floatValue;
    }

    void CoreOperator::SetFloatProperty(int index, float value)
    {
        getOperator()->properties[index].floatValue = value; 
        getOperator()->setDirty(true);
        getOperator()->properties[index].channelValue1 = 0.0f;
    }

    String^ CoreOperator::GetStringProperty(int index)
    {   
        return gcnew String(getOperator()->getStringProperty(index));   
    }

    void CoreOperator::SetStringProperty(int index, String^ string)
    {
        // Pin memory so GC can't move it while native function is called
        pin_ptr<const wchar_t> wch = PtrToStringChars(string);
     
        // Conversion to char* :
        // Can just convert wchar_t* to char* using one of the 
        // conversion functions such as: 
        // WideCharToMultiByte()
        // wcstombs_s()
        // ... etc
        size_t convertedChars = 0;
        size_t sizeInBytes = ((string->Length + 1) * 2);
        errno_t err = 0;
        char *ch = (char*)malloc(sizeInBytes);

        err = wcstombs_s(&convertedChars, 
                         ch, 
                         sizeInBytes,
                         wch, 
                         sizeInBytes);

        strcpy(getOperator()->properties[index].stringValue, ch);
        getOperator()->setDirty(true);
    }

    Vector^ CoreOperator::GetVectorProperty(int index)
    {
        D3DXVECTOR3 vector = getOperator()->properties[index].vectorValue;
        return gcnew Vector(vector.x, vector.y, vector.z);
    }

    void CoreOperator::SetVectorProperty(int index, Vector^ vector)
    {
        getOperator()->properties[index].vectorValue.x = vector->X;
        getOperator()->properties[index].vectorValue.y = vector->Y;
        getOperator()->properties[index].vectorValue.z = vector->Z;
        getOperator()->properties[index].channelValue1 = 0.0f;
        getOperator()->properties[index].channelValue2 = 0.0f;
        getOperator()->properties[index].channelValue3 = 0.0f;
        getOperator()->setDirty(true);
    }

    Color^ CoreOperator::GetColorProperty(int index)
    {
        D3DXCOLOR color = getOperator()->properties[index].colorValue;
        return gcnew Color((unsigned char)(color.r * 255), 
                           (unsigned char)(color.g * 255), 
                           (unsigned char)(color.b * 255));
    }

    void CoreOperator::SetColorProperty(int index, Color^ color)
    {
        getOperator()->properties[index].colorValue.r = color->R / 255.0f;
        getOperator()->properties[index].colorValue.g = color->G / 255.0f;
        getOperator()->properties[index].colorValue.b = color->B / 255.0f;
        getOperator()->properties[index].channelValue1 = 0.0f;
        getOperator()->properties[index].channelValue2 = 0.0f;
        getOperator()->properties[index].channelValue3 = 0.0f;
        getOperator()->setDirty(true);
    }

    int CoreOperator::GetPropertyChannel(int index, int valueIndex)
    {
        if (valueIndex == 0)
            return getOperator()->properties[index].channel1;
        if (valueIndex == 1)
            return getOperator()->properties[index].channel2;
        if (valueIndex == 2)
            return getOperator()->properties[index].channel3;
        return -1;
    }

    void CoreOperator::SetPropertyChannel(int index, int valueIndex, int channel)
    {
        if (valueIndex == 0)
            getOperator()->properties[index].channel1 = channel;
        if (valueIndex == 1)
            getOperator()->properties[index].channel2 = channel;
        if (valueIndex == 2)
            getOperator()->properties[index].channel3 = channel;
    }

    float CoreOperator::GetPropertyAmplify(int index, int valueIndex)
    {
        if (valueIndex == 0)
            return getOperator()->properties[index].amplify1;
        if (valueIndex == 1)
            return getOperator()->properties[index].amplify2;
        if (valueIndex == 2)
            return getOperator()->properties[index].amplify3;
        return 0.0f;
    }

    void CoreOperator::SetPropertyAmplify(int index, int valueIndex, float amplify)
    {
        if (valueIndex == 0)
            getOperator()->properties[index].amplify1 = amplify;
        if (valueIndex == 1)
            getOperator()->properties[index].amplify2 = amplify;
        if (valueIndex == 2)
            getOperator()->properties[index].amplify3 = amplify;
    }

    Core::Operator* CoreOperator::getOperator()
    {
        return Core::coreOperators[id];
    }

    void CoreOperator::ClearInputConnections()
    {
        for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
            getOperator()->inputs[i] = -1;
        getOperator()->numberOfInputs = 0;
    }

    void CoreOperator::ClearOutputConnections()
    {
        for (int i = 0; i < DB_MAX_OPERATOR_CONNECTIONS; i++)
            getOperator()->outputs[i] = -1;
        getOperator()->numberOfOutputs = 0;
    }

    int CoreOperator::GetInputConnectionId(int index)
    {
        return getOperator()->inputs[index];
    }

    int CoreOperator::GetOutputConnectionId(int index)
    {
        return getOperator()->outputs[index];
    }

    void CoreOperator::SetInputConnectionId(int index, int id)
    {
        getOperator()->inputs[index] = id;
    }

    void CoreOperator::SetOutputConnectionId(int index, int id)
    {
        getOperator()->outputs[index] = id;
    }

    int CoreOperator::GetMaxInputConnections()
    {
        return DB_MAX_OPERATOR_CONNECTIONS;
    }

    int CoreOperator::GetMaxOutputConnections()
    {
        return DB_MAX_OPERATOR_CONNECTIONS;
    }

    int CoreOperator::GetNumberOfInputConnections()
    {
        return getOperator()->numberOfInputs;
    }

    int CoreOperator::GetNumberOfOutputConnections()
    {
        return getOperator()->numberOfOutputs;
    }

    void CoreOperator::SetNumberOfInputConnections(int number)
    {
        getOperator()->numberOfInputs = number;
    }

    void CoreOperator::SetNumberOfOutputConnections(int number)
    {
        getOperator()->numberOfOutputs = number;
    }

    void CoreOperator::SetDirty(bool dirty)
    {
        getOperator()->setDirty(dirty);
    }

    bool CoreOperator::IsDirty()
    {
        return getOperator()->isDirty();
    }

    int CoreOperator::GetNumberOfRequiredInputs()
    {
        int result = 0;

        for (int i = 0; i < inputs->Count; i++)
        {
            if (!inputs[i]->Optional && !inputs[i]->Infinite)
                result++;
        }

        return result;
    }

    void CoreOperator::ClearClips()
    {
        for (int i = 0; i < DB_MAX_TIMELINE_CLIPS; i++)
            getOperator()->timelineClips[i] = -1;
    }

    int CoreOperator::GetClipId(int index)
    {
        return getOperator()->timelineClips[index];
    }

    void CoreOperator::SetClipId(int index, int id)
    {
        getOperator()->timelineClips[index] = id;
    }

    int CoreOperator::GetTicks()
    {
        return getOperator()->ticks;
    }

    void CoreOperator::SetTicks(int ticks)
    {
        getOperator()->ticks = ticks;
    }

    void CoreOperator::SetNumberOfClips(int numberOfClips)
    {
        getOperator()->numberOfClips = numberOfClips;
    }

    int CoreOperator::GetNumberOfClips()
    {
        return getOperator()->numberOfClips;
    }
}