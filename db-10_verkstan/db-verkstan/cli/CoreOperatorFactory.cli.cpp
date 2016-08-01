#define OPERATOR_HEADERS 1
#define OPERATORS_IN_NAMESPACE_CORE 1
#include "core/operators.hpp"
#undef OPERATOR_HEADERS
#undef OPERATORS_IN_NAMESPACE_CORE

#include "cli/CoreOperatorFactory.hpp"
#include "cli/CoreOperator.hpp"
#include "cli/Color.hpp"
#include "cli/Vector.hpp"

namespace Verkstan
{
#define ADD_OP_TO_CAT(name, category) \
if (!categories->ContainsKey(category)) \
    categories[category] = gcnew List<String^>(); \
categories[category]->Add(name);

    void CoreOperatorFactory::CreateCategories()
    {
        categories = gcnew Dictionary<String^, List<String^>^>();
#define OPERATOR_CATEGORY_DEFINES 1
#include "core/operators.hpp"
#undef OPERATOR_CATEGORY_DEFINES

        if (!categories->ContainsKey("Misc"))
            categories->Add("Misc", gcnew List<String^>());
        
        if (!categories["Misc"]->Contains("Store"))
            categories["Misc"]->Add("Store");

        if (!categories["Misc"]->Contains("Load"))
            categories["Misc"]->Add("Load");
        
        if (!categories["Misc"]->Contains("Propagate"))
            categories["Misc"]->Add("Propagate");
    }

    ICollection<String^>^ CoreOperatorFactory::GetCategories()
    {
        if (!categories)
            CreateCategories();

        return categories->Keys;
    }

    ICollection<String^>^ CoreOperatorFactory::GetNamesInCategory(String^ category)
    {
        if (!categories)
            CreateCategories();

        if (!categories->ContainsKey(category))
            return gcnew List<String^>();
        
        return categories[category];
    }

#define DEF_OP_FOR_LOADER(opNumber, opClass, numberOfConstantInputs, numberOfProps, ...) 
#define DEF_OP_FOR_LOADER_WITH_NO_PROPS(opId, opClass, numberOfConstantInputs) 
#define DEF_OP_FOR_EDITOR(opNumber, opNameChars, opClass, opType)\
    opName = gcnew String(opNameChars);             \
    if (name->ToLower() == opName->ToLower())   \
    {                                               \
        Core::Operator* o = new Core::opClass##();  \
        int id;                                     \
        for (int i = 0; i < DB_MAX_OPERATORS; i++)  \
        {                                           \
        if (Core::coreOperators[i] == 0)            \
            {                                       \
            Core::coreOperators[i] = o;             \
                id = i;                             \
                break;                              \
            }                                       \
        }                                           \
        op = gcnew CoreOperator(opNumber,           \
                                opName,             \
                                id,                 \
                                Constants::OperatorTypes::##opType);
#define ADD_BYTE_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Byte);  \
    op->SetByteProperty(op->Properties->Count - 1, value);
#define ADD_INT_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Int);  \
    op->SetIntProperty(op->Properties->Count - 1, value);
#define ADD_FLOAT_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Float);  \
    op->SetFloatProperty(op->Properties->Count - 1, value);
#define ADD_STRING_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::String);  \
    op->SetStringProperty(op->Properties->Count - 1, value);
#define ADD_TEXT_PROP(name, value) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Text);  \
    op->SetStringProperty(op->Properties->Count - 1, value);
#define ADD_COLOR_PROP(name, r, g, b) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Color);  \
    op->SetColorProperty(op->Properties->Count - 1, gcnew Color(r, g, b));
#define ADD_VECTOR_PROP(name, x, y, z) \
    op->AddProperty(name, Constants::OperatorPropertyTypes::Vector);  \
    op->SetVectorProperty(op->Properties->Count - 1, gcnew Vector(x, y, z));
#define ADD_ENUM_PROP(name, enumValues, value) \
    {\
    String^ tmpEnumValues = gcnew String(enumValues); \
    array<String^>^ splitted = tmpEnumValues->Split(gcnew array<Char>{','}); \
    List<String^>^ enumValuesList = gcnew List<String^>();  \
    for (int enumIndex = 0; enumIndex < splitted->Length; enumIndex++) \
        enumValuesList->Add(splitted[enumIndex]);   \
    op->AddEnumProperty(name, enumValuesList);  \
    int defaultValue;   \
    String^ defaultValueString = gcnew String(value);   \
    for (int listIndex = 0; listIndex < enumValuesList->Count; listIndex++) \
    {   \
        if (enumValuesList[listIndex] == defaultValueString)   \
        {   \
            defaultValue = listIndex;\
            break;\
        }\
    }\
    op->SetByteProperty(op->Properties->Count - 1, defaultValue); \
    }
#define ADD_INPUT(inType) \
    op->AddInput(Constants::OperatorTypes::##inType, false, false);
#define ADD_INFINITE_INPUT(inType) \
    op->AddInput(Constants::OperatorTypes::##inType, true, false);
#define ADD_OPTIONAL_INPUT(inType) \
    op->AddInput(Constants::OperatorTypes::##inType, false, true);
#define END_OP_FOR_EDITOR() }

    CoreOperator^ CoreOperatorFactory::Create(String^ name)
    {
        String^ opName;
        CoreOperator^ op;
#define OPERATOR_DEFINES 1
#include "core/operators.hpp"
#undef OPERATOR_DEFINES

        return op;
     }
}