#define DB_CAMERAOPERATOR 1
#define DB_MATERIALOPERATOR 1
#define DB_ICOSAHEDRONOPERATOR 1
#define DB_PIXELSOPERATOR 1
#define DB_TIMELINEOPERATOR 1
#define DB_GLOWOPERATOR 1
#define DB_CLOUDSOPERATOR 1
#define DB_BLUROPERATOR 1
#define DB_RENDERTOTEXTUREOPERATOR 1
#define DB_CLONEMODELOPERATOR 1
#define DB_LIGHTOPERATOR 1
#define DB_ADDMODELSOPERATOR 1
#define DB_TRANSFORMMODELOPERATOR 1
#define DB_MODELOPERATOR 1
#define DB_EXTRUDOPERATOR 1
#define DB_RANDOMSELECTIONOPERATOR 1
#define DB_RELAXOPERATOR 1
#define DB_SUBDIVIDEOPERATOR 1
#define DB_BOXOPERATOR 1
#define DB_CYLINDEROPERATOR 1
#define DB_SPHEREOPERATOR 1
#define DB_TORUSOPERATOR 1
#define DB_ROTOZOOMOPERATOR 1
#define DB_RECTANGLEOPERATOR 1
#define DB_TEXTOPERATOR 1
#define DB_FLATOPERATOR 1
#define DB_NORMALSSHADEROPERATOR 1
#define DB_NORMALMAPOPERATOR 1
#define DB_BLENDOPERATOR 1
#define DB_COLORIZEOPERATOR 1
#define DB_INVERTOPERATOR 1
#define DB_CONTRASTOPERATOR 1
#define DB_MERGETEXTURESOPERATOR 1
#define DB_DISTORTIONOPERATOR 1
#define DB_WELDOPERATOR 1
#define DB_DISPLACEMENTMAPOPERATOR 1

unsigned char data[] = 
{   
    // Operators
    0x06, 0x00, // Number of operators
    0x00, // Timeline
    0x15, // CameraOperator
    0x13, // MaterialOperator
    0x0a, // IcosahedronOperator
    0x01, // PixelsOperator
    0x01, // PixelsOperator

    // Properties
    0x01, // Render
    0x00, 0x00, 0x00, 0x00, // Time offset
    0xff, 0x00, 0x00, // Color 1
    0xff, 0x00, 0xff, // Color 1
    0xff, 0xff, 0xff, // Color 2
    0xff, 0x00, 0x00, // Color 2
    0xff, 0x50, // Count
    0xff, 0x50, // Count
    0x03, 0x00, // Seed
    0x04, 0x00, // Seed
    0x00, 0x00, 0x34, 0x42, // Angle
    0x00, 0x04, // Ratio width
    0x00, 0x03, // Ration height
    0xaa, 0x80, 0x80, // Clear color
    0x00, 0x00, 0x00, 0x00, // Translation x
    0x00, 0x00, 0x00, 0x00, // Translation y
    0x00, 0x00, 0xa0, 0xc0, // Translation z
    0x00, 0x00, 0x00, 0x00, // Look at x
    0x00, 0x00, 0x00, 0x00, // Look at y
    0x00, 0x00, 0x00, 0x00, // Look at z
    0x00, 0x00, 0x00, 0x00, // Rotation

    // Connections
    0x01, // One connection For TimelineOperator
    0x01, // One connection For CameraOperator
    0x02, // Two connections For MaterialOperator
    0x01, // One connection For PixelsOperator
    0x00, // Zero connections For PixelsOperator
    0x01, 0x00, // InputId - OperatorId CameraOperator input for TimelineOperator
    0x01, 0x00, // InputId - OperatorId MaterialOperator input for CameraOperator
    0x01, 0x00, // InputId - OperatorId IcosahedronOperator input for MaterialOperator
    0x01, 0x00, // InputId - OperatorId Delta encoded PixelsOperator input for MaterialOperator
    0x01, 0x00, // InputId - OperatorId PixelsOperator input for PixelsOperator

    // Animations
    0x02, 0x00, // Number of animations
    0x01, 0x00, // Index CameraOperator
    0x01, 0x00, // Index CameraOperator
    0x06, // Property index
    0x04, // Property index
    0x01, // Channel1
    0x01, // Channel1
    0x00, // Channel2
    0x00, // Channel2
    0x00, // Channel3
    0x00, // Channel3
    0x00, 0x00, 0x80, 0x3F, // Amplify1 1.0f
    0x00, 0x00, 0xA0, 0x40, // Amplify1 1.0f
    0x00, 0x00, 0x80, 0x3F, // Amplify2 1.0f
    0x00, 0x00, 0x80, 0x3F, // Amplify2 1.0f
    0x00, 0x00, 0x80, 0x3F, // Amplify3 1.0f
    0x00, 0x00, 0x80, 0x3F, // Amplify3 1.0f

    // Timelines
    0x01, 0x00, // Number of timelines
    0x00, 0x00, // Index of TimelineOperator
    0x10, 0x00, // Beats
    0x01, // Number of generators
    0x00, // Number of splines
    0x00, 0x00, // Start beat
    0x10, 0x00, // End beat
    0x01, // Channel
    0x00, // Type
    0x00, 0x0f // Period
 };
