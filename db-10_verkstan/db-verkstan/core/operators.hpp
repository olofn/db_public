#ifdef OPERATOR_HEADERS
#include "core/operators/flatoperator.hpp"
#include "core/operators/pixelsoperator.hpp"
#include "core/operators/textoperator.hpp"
#include "core/operators/rectangleoperator.hpp"
#include "core/operators/rotozoomoperator.hpp"
#include "core/operators/torusoperator.hpp"
#include "core/operators/sphereoperator.hpp"
#include "core/operators/cylinderoperator.hpp"
#include "core/operators/boxoperator.hpp"
#include "core/operators/transformmodeloperator.hpp"
#include "core/operators/basicmaterialoperator.hpp"
#include "core/operators/modeloperator.hpp"
#include "core/operators/addmodelsoperator.hpp"
#include "core/operators/lightoperator.hpp"
#include "core/operators/cameraoperator.hpp"
#include "core/operators/clonemodeloperator.hpp"
#include "core/operators/timelineoperator.hpp"
#include "core/operators/icosahedronoperator.hpp"
#include "core/operators/subdivideoperator.hpp"
#include "core/operators/relaxoperator.hpp"
#include "core/operators/randomselectionoperator.hpp"
#include "core/operators/extrudeoperator.hpp"
#include "core/operators/rendertotextureoperator.hpp"
#include "core/operators/bluroperator.hpp"
#include "core/operators/cloudsoperator.hpp"
#include "core/operators/glowoperator.hpp"
#include "core/operators/normalsshaderoperator.hpp"
#include "core/operators/normalmapoperator.hpp"
#include "core/operators/blendoperator.hpp"
#include "core/operators/colorizeoperator.hpp"
#include "core/operators/invertoperator.hpp"
#include "core/operators/contrastoperator.hpp"
#include "core/operators/mergetexturesoperator.hpp"
#include "core/operators/distortionoperator.hpp"
#include "core/operators/darkbitslogooperator.hpp"
#include "core/operators/weldoperator.hpp"
#include "core/operators/displacementmapoperator.hpp"
#include "core/operators/spherizeoperator.hpp"
#include "core/operators/twodimensionalplaneoperator.hpp"
#include "core/operators/planeoperator.hpp"
#include "core/operators/megaextrudeoperator.hpp"
#include "core/operators/particlesystemoperator.hpp"
#include "core/operators/crackleoperator.hpp"
#include "core/operators/transformuvoperator.hpp"
#include "core/operators/transformmeshoperator.hpp"
#include "core/operators/mergemeshesoperator.hpp"
#include "core/operators/clonemeshoperator.hpp"
#endif

#ifdef OPERATORS_IN_NAMESPACE_CORE
namespace Verkstan
{
    namespace Core
    {
        using ::FlatOperator;
        using ::PixelsOperator;
        using ::TextOperator;
        using ::RectangleOperator;
        using ::RotozoomOperator;
        using ::TorusOperator;
        using ::SphereOperator;
        using ::CylinderOperator;
        using ::BoxOperator;
        using ::TransformModelOperator;
        using ::BasicMaterialOperator;
        using ::ModelOperator;
        using ::AddModelsOperator;
        using ::LightOperator;
        using ::CameraOperator;
        using ::CloneModelOperator;
		using ::IcosahedronOperator;
		using ::SubdivideOperator;
		using ::RelaxOperator;
		using ::RandomSelectionOperator;
		using ::ExtrudeOperator;
        using ::TimelineOperator;
        using ::RenderToTextureOperator;
        using ::BlurOperator;
        using ::CloudsOperator;
        using ::GlowOperator;
        using ::NormalsShaderOperator;
        using ::NormalMapOperator;
        using ::BlendOperator;
        using ::ColorizeOperator;
        using ::InvertOperator;
        using ::ContrastOperator;
        using ::MergeTexturesOperator;
        using ::DistortionOperator;
        using ::DarkbitsLogoOperator;
		using ::WeldOperator;
		using ::DisplacementMapOperator;
		using ::SpherizeOperator;
        using ::TwoDimensionalPlaneOperator;
        using ::PlaneOperator;
        using ::MegaExtrudeOperator;
        using ::ParticleSystemOperator;
		using ::CrackleOperator;
        using ::TransformUVOperator;
        using ::TransformMeshOperator;
        using ::MergeMeshesOperator;
        using ::CloneMeshOperator;
    }
}
#endif

#ifdef OPERATOR_CATEGORY_DEFINES
ADD_OP_TO_CAT("Clouds",          "Texture");
ADD_OP_TO_CAT("Pixels",          "Texture");
ADD_OP_TO_CAT("Flat",            "Texture");
ADD_OP_TO_CAT("Text",            "Texture");
ADD_OP_TO_CAT("Rectangle",       "Texture");
ADD_OP_TO_CAT("Glow",            "Texture");
ADD_OP_TO_CAT("Rotozoom",        "Texture");
ADD_OP_TO_CAT("Blur",            "Texture");
ADD_OP_TO_CAT("Render To",       "Texture");
ADD_OP_TO_CAT("Normal Map",      "Texture");
ADD_OP_TO_CAT("Blend",           "Texture");
ADD_OP_TO_CAT("Colorize",        "Texture");
ADD_OP_TO_CAT("Invert",          "Texture");
ADD_OP_TO_CAT("Contrast",        "Texture");
ADD_OP_TO_CAT("Merge Textures",  "Texture");
ADD_OP_TO_CAT("Distortion",      "Texture");
ADD_OP_TO_CAT("Darkbits Logo",   "Texture");
ADD_OP_TO_CAT("Crackle",         "Texture");
ADD_OP_TO_CAT("Torus",           "Mesh");
ADD_OP_TO_CAT("Sphere",          "Mesh");
ADD_OP_TO_CAT("Cylinder",        "Mesh");
ADD_OP_TO_CAT("Box",             "Mesh");
ADD_OP_TO_CAT("Icosahedron",     "Mesh");
ADD_OP_TO_CAT("Subdivide",       "Mesh");
ADD_OP_TO_CAT("Relax",	         "Mesh");
ADD_OP_TO_CAT("Random Selection","Mesh");
ADD_OP_TO_CAT("Extrude",		 "Mesh");
ADD_OP_TO_CAT("Weld",			 "Mesh");
ADD_OP_TO_CAT("Displacement Map","Mesh");
ADD_OP_TO_CAT("Spherize",        "Mesh");
ADD_OP_TO_CAT("Plane",           "Mesh");
ADD_OP_TO_CAT("Mega Extrude",    "Mesh");
ADD_OP_TO_CAT("Transform UV",    "Mesh");
ADD_OP_TO_CAT("Merge Meshes",    "Mesh");
ADD_OP_TO_CAT("Transform Mesh",  "Mesh");
ADD_OP_TO_CAT("Clone Mesh",      "Mesh");
ADD_OP_TO_CAT("Model",           "Model");
ADD_OP_TO_CAT("Particle System", "Model");
ADD_OP_TO_CAT("Transform Model", "Model");
ADD_OP_TO_CAT("Add Models",      "Model");
ADD_OP_TO_CAT("Clone Model",     "Model");
ADD_OP_TO_CAT("Basic Material",  "Model");
ADD_OP_TO_CAT("Normals Shader",  "Model");
ADD_OP_TO_CAT("Camera",          "Renderer");
ADD_OP_TO_CAT("Timeline",        "Renderer");
ADD_OP_TO_CAT("Transform",       "Renderer");
ADD_OP_TO_CAT("2D Plane",        "Renderer");
ADD_OP_TO_CAT("Light",           "Renderer");
#endif

#define DB_BYTE_PROP 0x00
#define DB_ENUM_PROP 0x00
#define DB_INT_PROP  0x01
#define DB_FLOAT_PROP 0x02
#define DB_COLOR_PROP 0x03
#define DB_VECTOR_PROP 0x04
#define DB_STRING_PROP 0x05
#define DB_TEXT_PROP 0x05

//DEF_OP_FOR_LOADER params
// Id, e.i 0
// Class, e.i TimelineOperator
// Number of constant inputs, e.i -1 for no constant inputs or 2 for two constant inputs
// Number of properties, e.i 2
// Property types, e.i DB_BYTE_PROP, DB_FLOAT_PROP for a byte property and a float property. 


//DEF_OP_FOR_LOADER_WITH_NO_PROPS params
// Id, e.i 0
// Class, e.i TimelineOperator
// Number of constant inputs, e.i -1 for no constant inputs or 2 for two constant inputs

#ifdef OPERATOR_DEFINES
#if defined(DB_TIMELINEOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(0, TimelineOperator, -1, 2, DB_BYTE_PROP, DB_FLOAT_PROP);
DEF_OP_FOR_EDITOR(0, "Timeline", TimelineOperator, Renderer);
ADD_BYTE_PROP("Render", 1);
ADD_FLOAT_PROP("Time offset", 0);
ADD_INPUT(Unspecified);
ADD_INFINITE_INPUT(Unspecified);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_PIXELSOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(1, PixelsOperator, -1, 4, 
                  DB_COLOR_PROP, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(1, "Pixels", PixelsOperator, Texture);
ADD_COLOR_PROP("Color 1", 255, 255, 255);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_BYTE_PROP("Count", 1);
ADD_BYTE_PROP("Seed",  0);
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_FLATOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(2, FlatOperator, 0, 1, 
                  DB_COLOR_PROP);
DEF_OP_FOR_EDITOR(2, "Flat", FlatOperator, Texture);
ADD_COLOR_PROP("Color", 255, 255, 255);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_TEXTOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(3, TextOperator, -1, 6, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_STRING_PROP, 
                  DB_TEXT_PROP);
DEF_OP_FOR_EDITOR(3, "Text", TextOperator, Texture);
ADD_COLOR_PROP("Color", 255, 255, 255);
ADD_BYTE_PROP("Height", 30);
ADD_BYTE_PROP("X", 10);
ADD_BYTE_PROP("Y", 5);
ADD_STRING_PROP("Font", "");
ADD_TEXT_PROP("Text", "Text!");
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_RECTANGLEOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(4, RectangleOperator, -1, 5, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP,
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP,
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(4, "Rectangle", RectangleOperator, Texture);
ADD_COLOR_PROP("Color", 255, 255, 0);
ADD_BYTE_PROP("X",      10);
ADD_BYTE_PROP("Y",      10);
ADD_BYTE_PROP("Width",  100);
ADD_BYTE_PROP("Height", 100);
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_ROTOZOOMOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(5, RotozoomOperator, 1, 4, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(5, "Rotozoom", RotozoomOperator, Texture);
ADD_BYTE_PROP("Center X", 128);
ADD_BYTE_PROP("Center Y", 128);
ADD_BYTE_PROP("Rotation", 0);
ADD_BYTE_PROP("Zoom",    128);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_TORUSOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(6, TorusOperator, 0, 4, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(6, "Torus", TorusOperator, Mesh);
ADD_FLOAT_PROP("Inner radius", 0.3f);
ADD_FLOAT_PROP("Outer radius", 0.7f);
ADD_BYTE_PROP("Sides",         5);
ADD_BYTE_PROP("Rings",         10);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_SPHEREOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(7, SphereOperator, 0, 3, 
                  DB_FLOAT_PROP,
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(7, "Sphere", SphereOperator, Mesh);
ADD_FLOAT_PROP("Radius", 1.0f);
ADD_BYTE_PROP("Slices",  10);
ADD_BYTE_PROP("Stacks",  10);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CYLINDEROPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(8, CylinderOperator, 0, 7, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP,
                  DB_BYTE_PROP,
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(8, "Cylinder", CylinderOperator, Mesh);
ADD_FLOAT_PROP("Radius 1", 1.0f);
ADD_FLOAT_PROP("Radius 2", 1.0f);
ADD_FLOAT_PROP("Length",   1.0f);
ADD_BYTE_PROP("Slices",    10);
ADD_BYTE_PROP("Stacks",    1);
ADD_BYTE_PROP("Bottom Rings",1);
ADD_BYTE_PROP("Top Rings",1);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_BOXOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(9, BoxOperator, 0, 6, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP,
                  DB_BYTE_PROP,
                  DB_BYTE_PROP,
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(9, "Box", BoxOperator, Mesh);
ADD_FLOAT_PROP("Width",  1.0f);
ADD_FLOAT_PROP("Height", 1.0f);
ADD_FLOAT_PROP("Depth",  1.0f);
ADD_BYTE_PROP("X Slices", 1);
ADD_BYTE_PROP("Y Slices", 1);
ADD_BYTE_PROP("Z Slices", 1);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_ICOSAHEDRONOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(10, IcosahedronOperator, 0);
DEF_OP_FOR_EDITOR(10, "Icosahedron", IcosahedronOperator, Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_SUBDIVIDEOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(11, SubdivideOperator, 1, 2, 
                  DB_BYTE_PROP,
                  DB_FLOAT_PROP);
DEF_OP_FOR_EDITOR(11, "Subdivide", SubdivideOperator, Mesh);
ADD_BYTE_PROP("Repetitions", 1);
ADD_FLOAT_PROP("Smoothness", 0.5f);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_RELAXOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(12, RelaxOperator, 1, 2, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(12, "Relax", RelaxOperator, Mesh);
ADD_FLOAT_PROP("Strength", 0.1f);
ADD_BYTE_PROP("Repetitions", 2);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_RANDOMSELECTIONOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(13, RandomSelectionOperator, 1, 2, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(13, "Random Selection", RandomSelectionOperator, Mesh);
ADD_BYTE_PROP("Probablility", 128);
ADD_BYTE_PROP("Seed", 1);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_EXTRUDOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(14, ExtrudeOperator, 1, 1,
                  DB_FLOAT_PROP);
DEF_OP_FOR_EDITOR(14, "Extrude", ExtrudeOperator, Mesh);
ADD_FLOAT_PROP("Distance", 0.1f);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_MODELOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(15, ModelOperator, 1, 2,
                  DB_ENUM_PROP,
                  DB_ENUM_PROP);
DEF_OP_FOR_EDITOR(15, "Model", ModelOperator, Model);
ADD_ENUM_PROP("Cull mode", "CCW,CW,None", "CCW");
ADD_ENUM_PROP("Fill mode", "Solid,Wireframe,Point", "Solid");
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_TRANSFORMMODELOPERATOR) || defined(DB_TRANSFORMOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(16, TransformModelOperator, 1, 3, 
                  DB_VECTOR_PROP,
                  DB_VECTOR_PROP, 
                  DB_VECTOR_PROP);
DEF_OP_FOR_EDITOR(16, "Transform Model", TransformModelOperator, Model);
ADD_VECTOR_PROP("Scale",     1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate",    0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Model);
END_OP_FOR_EDITOR();
DEF_OP_FOR_EDITOR(16, "Transform", TransformModelOperator, Renderer);
ADD_VECTOR_PROP("Scale",     1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate",    0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Renderer);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_ADDMODELSOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(17, AddModelsOperator, -1);
DEF_OP_FOR_EDITOR(17, "Add Models", AddModelsOperator, Model);
ADD_INPUT(Model);
ADD_INPUT(Model);
ADD_INFINITE_INPUT(Model);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_LIGHTOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(18, LightOperator, -1, 13, 
                  DB_ENUM_PROP,
                  DB_COLOR_PROP, 
                  DB_COLOR_PROP,
                  DB_COLOR_PROP,
                  DB_VECTOR_PROP, 
                  DB_VECTOR_PROP, 
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP);
DEF_OP_FOR_EDITOR(18, "Light", LightOperator, Renderer);
ADD_ENUM_PROP("Type", "Point,Spot,Directional", "Point");
ADD_COLOR_PROP("Diffuse", 255, 255, 0);
ADD_COLOR_PROP("Specular", 255, 255, 255);
ADD_COLOR_PROP("Ambient", 0, 0, 0);
ADD_VECTOR_PROP("Position", 0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Direction", 1.0f, 0.0f, 0.0f);
ADD_FLOAT_PROP("Range", 10.0f);
ADD_FLOAT_PROP("Falloff", 10.0f);
ADD_FLOAT_PROP("Attenuation0", 1.0f);
ADD_FLOAT_PROP("Attenuation1", 1.0f);
ADD_FLOAT_PROP("Attenuation2", 1.0f);
ADD_FLOAT_PROP("Theta", 1.0f);
ADD_FLOAT_PROP("Phi", 1.0f);
ADD_OPTIONAL_INPUT(Unspecified);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_BASICMATERIALOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(19, BasicMaterialOperator, -1, 8, 
                  DB_COLOR_PROP, 
                  DB_COLOR_PROP,
                  DB_COLOR_PROP,
                  DB_FLOAT_PROP,
                  DB_ENUM_PROP,
                  DB_ENUM_PROP,
                  DB_ENUM_PROP,
                  DB_ENUM_PROP);
DEF_OP_FOR_EDITOR(19, "Basic Material", BasicMaterialOperator, Model);
ADD_COLOR_PROP("Diffuse", 255, 255, 255);
ADD_COLOR_PROP("Specular", 255, 255, 255);
ADD_COLOR_PROP("Ambient", 128, 128, 128);
ADD_FLOAT_PROP("Power", 100.0f);
ADD_ENUM_PROP("Lightning", "No,Yes", "No");
ADD_ENUM_PROP("Texture Address", "Wrap,Mirror,Border,Clamp", "Wrap");
ADD_ENUM_PROP("Texture Filtiring", "Anisotropic,Convolution Mono,Gaussion Quad,Linear,None", "Anisotropic");
ADD_ENUM_PROP("Alpha blend", "Yes,No", "Yes");
ADD_INPUT(Model);
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CLONEMODELOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(20, CloneModelOperator, 1, 4, 
                  DB_BYTE_PROP,
                  DB_VECTOR_PROP, 
                  DB_VECTOR_PROP,
                  DB_VECTOR_PROP);
DEF_OP_FOR_EDITOR(20, "Clone Model", CloneModelOperator, Model);
ADD_BYTE_PROP("Clones",      2);
ADD_VECTOR_PROP("Scale",     1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate",    0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Model);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CAMERAOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(21, CameraOperator, -1, 7, 
                  DB_FLOAT_PROP,
                  DB_INT_PROP, 
                  DB_INT_PROP, 
                  DB_COLOR_PROP, 
                  DB_VECTOR_PROP, 
                  DB_VECTOR_PROP, 
                  DB_FLOAT_PROP);
DEF_OP_FOR_EDITOR(21, "Camera", CameraOperator, Renderer);
ADD_FLOAT_PROP("Angle", 45.0f);
ADD_INT_PROP("Aspect width", 1024);
ADD_INT_PROP("Aspect height", 768);
ADD_COLOR_PROP("Clear color", 255, 0, 255);
ADD_VECTOR_PROP("Translation", 0.0f, 0.0f, -2.0f);
ADD_VECTOR_PROP("Look at", 0.0f, 0.0f, 0.0f);
ADD_FLOAT_PROP("Rotation", 0.0f);
ADD_INPUT(Unspecified);
ADD_INFINITE_INPUT(Unspecified);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_RENDERTOTEXTUREOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(22, RenderToTextureOperator, -1);
DEF_OP_FOR_EDITOR(22, "Render To", RenderToTextureOperator, Texture);
ADD_INPUT(Unspecified);
ADD_INFINITE_INPUT(Unspecified);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_BLUROPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(23, BlurOperator, 1, 4, 
                  DB_ENUM_PROP, 
                  DB_ENUM_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(23, "Blur", BlurOperator, Texture);
ADD_ENUM_PROP("Type", "Box,Triangle,Gaussien", "Box");
ADD_ENUM_PROP("Direction", "X,Y,X and Y", "X and Y");
ADD_BYTE_PROP("Width", 1);
ADD_BYTE_PROP("Amplify", 16);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CLOUDSOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(24, CloudsOperator, 0, 4, 
                  DB_COLOR_PROP, 
                  DB_COLOR_PROP, 
                  DB_ENUM_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(24, "Clouds", CloudsOperator, Texture);
ADD_COLOR_PROP("Color 1", 0, 0, 0);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_ENUM_PROP("Size", "1,2,4,8,16,32,64,128", "2");
ADD_BYTE_PROP("Seed", 1);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_GLOWOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(25, GlowOperator, -1, 7, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(25, "Glow", GlowOperator, Texture);
ADD_COLOR_PROP("Color", 255, 0, 0);
ADD_BYTE_PROP("Center X", 128);
ADD_BYTE_PROP("Center Y", 128);
ADD_BYTE_PROP("Radius X", 128);
ADD_BYTE_PROP("Radius Y", 128);
ADD_BYTE_PROP("Gamma", 1);
ADD_BYTE_PROP("Alpha", 255);
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_NORMALSSHADEROPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(26, NormalsShaderOperator, 1);
DEF_OP_FOR_EDITOR(26, "Normals Shader", NormalsShaderOperator, Model);
ADD_INPUT(Model);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_NORMALMAPOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(27, NormalMapOperator, 1, 1, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(27, "Normal Map", NormalMapOperator, Texture);
ADD_BYTE_PROP("Amplify", 16);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_BLENDOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(28, BlendOperator, -1);
DEF_OP_FOR_EDITOR(28, "Blend", BlendOperator, Texture);
ADD_INPUT(Texture);
ADD_INPUT(Texture);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_COLORIZEOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(29, ColorizeOperator, 1, 3, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(29, "Colorize", ColorizeOperator, Texture);
ADD_BYTE_PROP("Hue", 0);
ADD_BYTE_PROP("Saturation", 255);
ADD_BYTE_PROP("Light", 128);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_INVERTOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(30, InvertOperator, 1);
DEF_OP_FOR_EDITOR(30, "Invert", InvertOperator, Texture);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CONTRASTOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(31, ContrastOperator, 1, 1, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(31, "Contrast", ContrastOperator, Texture);
ADD_BYTE_PROP("Contrast", 128);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_MERGETEXTURESOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(32, MergeTexturesOperator, -1, 1, 
                  DB_ENUM_PROP);
DEF_OP_FOR_EDITOR(32, "Merge Textures", MergeTexturesOperator, Texture);
ADD_ENUM_PROP("Mode", "Add Clamp,Add Wrap,Sub Clamp,Sub Wrap,Mult,Alpha", "Add Clamp");
ADD_INPUT(Texture);
ADD_INPUT(Texture);
ADD_INFINITE_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_DISTORTIONOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(33, DistortionOperator, 1, 1, 
                  DB_ENUM_PROP,
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(33, "Distortion", DistortionOperator, Texture);
ADD_ENUM_PROP("Mode", "Green-Blue,Normal Map", "Green-Blue");
ADD_BYTE_PROP("Amount", 0);
ADD_INPUT(Texture);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_DARKBITSLOGOOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(34, DarkbitsLogoOperator, -1, 1, DB_ENUM_PROP);
DEF_OP_FOR_EDITOR(34, "Darkbits Logo", DarkbitsLogoOperator, Texture);
ADD_ENUM_PROP("Outline", "No,Yes", "No");
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_WELDOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(35, WeldOperator, -1);
DEF_OP_FOR_EDITOR(35, "Weld", WeldOperator, Mesh);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_DISPLACEMENTMAPOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(36, DisplacementMapOperator, 2, 1, 
                  DB_FLOAT_PROP);
DEF_OP_FOR_EDITOR(36, "Displacement Map", DisplacementMapOperator, Mesh);
ADD_INPUT(Mesh);
ADD_INPUT(Texture);
ADD_FLOAT_PROP("Distance", 0.25f);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_SPHERIZEOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(37, SpherizeOperator, 1, 2, 
                  DB_FLOAT_PROP,
				  DB_FLOAT_PROP);
DEF_OP_FOR_EDITOR(37, "Spherize", SpherizeOperator, Mesh);
ADD_INPUT(Mesh);
ADD_FLOAT_PROP("Radius", 1.0f);
ADD_FLOAT_PROP("Amount", 1.0f);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_2DPLANEOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(38, TwoDimensionalPlaneOperator, -1, 12,
                  DB_COLOR_PROP,
                  DB_BYTE_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_FLOAT_PROP,
                  DB_ENUM_PROP);
DEF_OP_FOR_EDITOR(38, "2D Plane", TwoDimensionalPlaneOperator, Renderer);
ADD_COLOR_PROP("Color", 255, 255, 255);
ADD_BYTE_PROP("Alpha", 255);
ADD_FLOAT_PROP("X", 0.0f);
ADD_FLOAT_PROP("Width", 1.0f);
ADD_FLOAT_PROP("Y", 0.0f);
ADD_FLOAT_PROP("Height", 1.0f);
ADD_FLOAT_PROP("Z", 0.0f);
ADD_FLOAT_PROP("U Offset", 0.0f);
ADD_FLOAT_PROP("V Offset", 0.0f);
ADD_FLOAT_PROP("U Scale", 1.0f);
ADD_FLOAT_PROP("V Scale", 1.0f);
ADD_ENUM_PROP("Stretch texture", "No,Yes", "No");
ADD_INFINITE_INPUT(Unspecified);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_PLANEOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(39, PlaneOperator, 0, 4, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(39, "Plane", PlaneOperator, Mesh);
ADD_FLOAT_PROP("Width",   1.0f);
ADD_FLOAT_PROP("Height",  1.0f);
ADD_BYTE_PROP("X Slices", 10);
ADD_BYTE_PROP("Y Slices", 10);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_MEGAEXTRUDE) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(40, MegaExtrudeOperator, 1, 5, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP, 
                  DB_VECTOR_PROP, 
                  DB_VECTOR_PROP,
                  DB_VECTOR_PROP);
DEF_OP_FOR_EDITOR(40, "Mega Extrude", MegaExtrudeOperator, Mesh);
ADD_FLOAT_PROP("Distance",   0.2f);
ADD_BYTE_PROP("Count", 3);
ADD_VECTOR_PROP("Scale", 1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotation", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_PARTICLESYSTEMOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(41, ParticleSystemOperator, 1, 1,
                  DB_FLOAT_PROP);
DEF_OP_FOR_EDITOR(41, "Particle System", ParticleSystemOperator, Model);
ADD_FLOAT_PROP("Particle Size", 0.2f);
ADD_FLOAT_PROP("Lighting Range", 0.2f);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CRACKLEOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(42, CrackleOperator, 0, 5,
                  DB_COLOR_PROP,
				  DB_COLOR_PROP,
				  DB_BYTE_PROP,
                  DB_BYTE_PROP,
				  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(42, "Crackle", CrackleOperator, Texture);
ADD_COLOR_PROP("Color 1", 0, 0, 0);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_BYTE_PROP("Count", 8);
ADD_BYTE_PROP("Randomness", 128);
ADD_BYTE_PROP("Seed", 1);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_TRANSFORMUVOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(43, TransformUVOperator, 1, 4,
                  DB_BYTE_PROP,
				  DB_VECTOR_PROP,
				  DB_VECTOR_PROP,
                  DB_VECTOR_PROP);
DEF_OP_FOR_EDITOR(43, "Transform UV", TransformUVOperator, Mesh);
ADD_BYTE_PROP("Set", 0);
ADD_VECTOR_PROP("Scale", 1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate", 0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_TRANSFORMMESHOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(44, TransformMeshOperator, 1, 3,
				  DB_VECTOR_PROP,
				  DB_VECTOR_PROP,
                  DB_VECTOR_PROP);
DEF_OP_FOR_EDITOR(44, "Transform Mesh", TransformMeshOperator, Mesh);
ADD_VECTOR_PROP("Scale", 1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate", 0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif


#if defined(DB_MERGEMESHESOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(45, MergeMeshesOperator, -1);
DEF_OP_FOR_EDITOR(45, "Merge Meshes", MergeMeshesOperator, Mesh);
ADD_INPUT(Mesh);
ADD_INPUT(Mesh);
ADD_INFINITE_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CLONEMESHOPERATOR) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(46, CloneMeshOperator, 1, 4, 
                  DB_BYTE_PROP,
                  DB_VECTOR_PROP, 
                  DB_VECTOR_PROP,
                  DB_VECTOR_PROP);
DEF_OP_FOR_EDITOR(46, "Clone Mesh", CloneMeshOperator, Mesh);
ADD_BYTE_PROP("Clones",      2);
ADD_VECTOR_PROP("Scale",     1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate",    0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#endif
