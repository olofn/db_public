#pragma once

#include "cli/Core.hpp"
#include "cli/Constants.hpp"

#using <mscorlib.dll>

using namespace System;
using namespace System::Collections::Generic;

namespace Verkstan
{
    ref struct Color;
    ref struct Vector;
    ref class CoreOperatorProperty;
    ref class CoreOperatorInput;

	public ref class CoreOperator 
	{
    public:
        property Constants::OperatorTypes Type { Constants::OperatorTypes get(); }
        property String^ Name { String^ get(); }
        property unsigned short Id { unsigned short get(); }
        property unsigned char Number { unsigned char get(); }
        property short NumberOfConstantInputs { short get(); }
        property List<CoreOperatorProperty^>^ Properties { List<CoreOperatorProperty^>^ get(); }
        property List<CoreOperatorInput^>^ Inputs { List<CoreOperatorInput^>^ get(); }

        CoreOperator(unsigned char number, 
                     String^ name,
                     unsigned short operatorId,
                     Constants::OperatorTypes type);
        virtual ~CoreOperator();

        unsigned char GetByteProperty(int index);
        void SetByteProperty(int index, unsigned char value);
        int GetIntProperty(int index);
        void SetIntProperty(int index, int value);
        float GetFloatProperty(int index);
        void SetFloatProperty(int index, float value);
        String^ GetStringProperty(int index);
        void SetStringProperty(int index, String^ value);
        Vector^ GetVectorProperty(int index);
        void SetVectorProperty(int index, Vector^ vector);
        Color^ GetColorProperty(int index);
        void SetColorProperty(int index, Color^ color);
        int GetPropertyChannel(int index, int valueIndex);
        void SetPropertyChannel(int index, int valueIndex, int channel);
        float GetPropertyAmplify(int index,  int valueIndex);
        void SetPropertyAmplify(int index, int valueIndex, float amplify);
        
        Core::Operator* getOperator();

        void AddProperty(String^ name, Constants::OperatorPropertyTypes type);
        void AddEnumProperty(String^ name, List<String^>^ values);
        void AddInput(Constants::OperatorTypes type, bool infinite, bool optional);

        int GetNumberOfRequiredInputs();
        void ClearInputConnections();
        void ClearOutputConnections();
        void ClearClips();
        int GetClipId(int index);
        void SetClipId(int index, int id);
        void SetNumberOfClips(int numberOfClips);
        int GetNumberOfClips();
        int GetTicks();
        void SetTicks(int ticks);
        int GetInputConnectionId(int index);
        int GetOutputConnectionId(int index);
        void SetInputConnectionId(int index, int id);
        void SetOutputConnectionId(int index, int id);
        int GetMaxInputConnections();
        int GetMaxOutputConnections();
        int GetNumberOfInputConnections();
        int GetNumberOfOutputConnections();
        void SetNumberOfInputConnections(int number);
        void SetNumberOfOutputConnections(int number);
        void SetDirty(bool dirty);
        bool IsDirty();

    private:
        unsigned char number;
        String^ name;
        unsigned short id;
        short numberOfConstantInputs;
        Constants::OperatorTypes type;
        List<CoreOperatorProperty^>^ properties;
        List<CoreOperatorInput^>^ inputs;
	};
}