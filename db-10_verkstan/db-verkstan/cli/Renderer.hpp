#pragma once

#include <d3d9.h>
#include "core/mesh.hpp"

struct TextureVertex
{
    float x, y, z;
    DWORD color;
    float u, v;
};

struct MeshVertex
{
    float x, y, z;
    DWORD color;
};

namespace Verkstan
{
    ref class Camera;
    ref class CoreOperator;
    
    public ref class Renderer
    {
    public:
        Renderer();
        ~Renderer();
 
        bool TextureTiling;
        bool TextureFiltering;
        bool MeshSolid;
        bool ModelLightning;

        int ClearColor;
        int WindowWidth;
        int WindowHeight;
        
        void RenderOperator(CoreOperator^ op, int tick);
        void MouseDown(int button, int x, int y);
        void MouseMove(int x, int y);
        void MouseUp(int button, int x, int y);
        void ResetCamera();

    private:
        void RenderTextureOperator(CoreOperator^ op, int tick);
        void RenderMeshOperator(CoreOperator^ op, int tick);
        void RenderModelOperator(CoreOperator^ op, int tick);
        void RenderDemoSceneRendererOperator(CoreOperator^ op, int tick);
        void RenderUnknownOperator(CoreOperator^ op, int tick);
        void RenderMesh(Mesh* mesh);

        Camera^ camera;
    };
}