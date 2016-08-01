#include "cli/Renderer.hpp"

#include "cli/Camera.hpp"
#include "cli/CoreOperator.hpp"

namespace Verkstan
{
    Renderer::Renderer()
    {
        camera = gcnew Camera();
        TextureTiling = false;
        TextureFiltering = false;
        MeshSolid = false;
        ModelLightning = true;
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::RenderOperator(CoreOperator^ op, int tick)
    {
        if (op == nullptr)
        {
            globalDirect3DDevice->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);
            return;
        }

        camera->WindowWidth = WindowWidth;
        camera->WindowHeight = WindowHeight;

        op->getOperator()->cascadeProcess(tick);

        switch (op->Type)
        {
        case Constants::OperatorTypes::Mesh:
            RenderMeshOperator(op, tick);
            break;
         case Constants::OperatorTypes::Model:
            RenderModelOperator(op, tick);
            break;
        case Constants::OperatorTypes::Texture:
            RenderTextureOperator(op, tick);
            break;
        case Constants::OperatorTypes::Renderer:
            RenderDemoSceneRendererOperator(op, tick);
            break;
        default:
            RenderUnknownOperator(op, tick);
            break;
        }
    }

    void Renderer::RenderTextureOperator(CoreOperator^ op, int tick)
    {
        Core::Operator* coreOp = op->getOperator();
        
        // Reset all channel values as we don't want any animation
        // to pollute the view.
        for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
        {
            if (coreOp->properties[i].channelValue1 != 0.0f)
            {
                coreOp->properties[i].channelValue1 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue2 != 0.0f)
            {
                coreOp->properties[i].channelValue2 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue3 != 0.0f)
            {
                coreOp->properties[i].channelValue3 = 0.0f;
                coreOp->setDirty(true);
            } 
        }

        if (coreOp->texture == 0)
            return;

        int textureWidth = coreOp->texture->width;
        int textureHeight = coreOp->texture->height;
        float textureRatioWidthHeight = textureWidth / (float)textureHeight;
        float textureRatioHeightWidth = textureHeight / (float)textureWidth;

        if (textureWidth > WindowWidth && textureHeight > WindowHeight)
        {
            if (textureWidth > textureHeight)
            {
                textureWidth = WindowWidth;
                textureHeight = (int)(textureWidth * textureRatioHeightWidth);
            }
            else
            {
                textureHeight = WindowHeight;
                textureWidth = (int)(textureHeight * textureRatioWidthHeight);
            }
        }
        else if (textureWidth > WindowWidth)
        {
            textureWidth = WindowWidth;
            textureHeight = (int)(textureWidth * textureRatioHeightWidth);
        }
        else if (textureHeight > WindowHeight)
        {
            textureHeight = WindowHeight;
            textureWidth = (int)(textureHeight * textureRatioWidthHeight);
        }

        float x, y, width, height, u1, u2, v1, v2;

        if (TextureTiling)
        {
            x = 0.0f;
            y = 0.0f;
            width = 1.0f;
            height = 1.0f;

            float texturesOnX = WindowWidth / (float)textureWidth;
            float texturesOnY = WindowHeight / (float)textureHeight;
            
            // We add 0.5f to center the texture. Why? Because if the
            // the texture width is the same as the window width
            // texturesOnX becomes 0.5f, and in that case we want
            // u1 = 0.0f and u2 = 1.0f.
            u1 = -texturesOnX / 2.0f + 0.5f;
            u2 =  texturesOnX / 2.0f + 0.5f;
            v1 = -texturesOnY / 2.0f + 0.5f;
            v2 =  texturesOnY / 2.0f + 0.5f;

            globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
            globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
            globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
        }
        else
        {
            x = (WindowWidth / 2 - textureWidth / 2) / (float)WindowWidth;
            y = (WindowHeight / 2 - textureHeight / 2) / (float)WindowHeight;
            width = textureWidth / (float)WindowWidth;
            height = textureHeight / (float)WindowHeight;
            u1 = 0.0f;
            u2 = 1.0f;
            v1 = 0.0f;
            v2 = 1.0f;

            globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
            globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
            globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_BORDER);
        }

        if (TextureFiltering)
        {
            globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
        }
        else
        {
            globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_NONE);
	        globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        }

        TextureVertex quad[4];
        quad[0].x = x; 
        quad[0].y = y; 
        quad[0].z = 0.0f;
        quad[0].u = u1; 
        quad[0].v = v1; 
        quad[0].color = 0xffffffff;
        
        quad[1].x = x + width; 
        quad[1].y = y; 
        quad[1].z = 0.0f;
        quad[1].u = u2; 
        quad[1].v = v1; 
        quad[1].color = 0xffffffff;

        quad[2].x = x + width; 
        quad[2].y = y + height; 
        quad[2].z = 0.0f;
        quad[2].u = u2;
        quad[2].v = v2; 
        quad[2].color = 0xffffffff;

        quad[3].x = x; 
        quad[3].y = y + height; 
        quad[3].z = 0.0f;
        quad[3].u = u1; 
        quad[3].v = v2; 
        quad[3].color = 0xffffffff;

        D3DXMATRIX identityMatrix;
        D3DXMATRIX projectionMatrix;
        D3DXMatrixIdentity(&identityMatrix);
        D3DXMatrixOrthoOffCenterLH(&projectionMatrix, 
                                   0.0f, 
                                   1.0f, 
                                   1.0f, 
                                   0.0f, 
                                   -1.0f, 
                                   1.0f);
        globalDirect3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
        globalDirect3DDevice->SetTransform(D3DTS_VIEW, &identityMatrix);
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);     
        globalDirect3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
        globalDirect3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
        globalDirect3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);

        globalDirect3DDevice->Clear(0, 
                                    NULL, 
                                    D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                    ClearColor, 
                                    1.0f, 
                                    0);

        globalDirect3DDevice->BeginScene();
        globalDirect3DDevice->SetTexture(0, coreOp->texture->getD3D9Texture());		
        globalDirect3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);
        globalDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &quad, sizeof(TextureVertex));
        globalDirect3DDevice->SetTexture(0, 0);		
        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderUnknownOperator(CoreOperator^ op, int tick)
    {
        globalDirect3DDevice->Clear(0, 
                   NULL, 
                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                   ClearColor, 
                   1.0f, 
                   0);
    }

    void Renderer::RenderMeshOperator(CoreOperator^ op, int tick)
    {
        Core::Operator* coreOp = op->getOperator();

        // Reset all channel values as we don't want any animation
        // to pollute the view.
        for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
        {
            if (coreOp->properties[i].channelValue1 != 0.0f)
            {
                coreOp->properties[i].channelValue1 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue2 != 0.0f)
            {
                coreOp->properties[i].channelValue2 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue3 != 0.0f)
            {
                coreOp->properties[i].channelValue3 = 0.0f;
                coreOp->setDirty(true);
            } 
        }

        if (coreOp->mesh == 0)
            return;

        globalDirect3DDevice->Clear(0, 
                           NULL, 
                           D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                           ClearColor, 
                           1.0f, 
                           0);

       

        if (MeshSolid)
        {
            globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

            D3DLIGHT9 d3dLight;
            ZeroMemory(&d3dLight, sizeof(d3dLight));
            d3dLight.Type = D3DLIGHT_DIRECTIONAL;
          
            d3dLight.Diffuse.r = 1.0f;
            d3dLight.Diffuse.g = 1.0f;
            d3dLight.Diffuse.b = 1.0f;
            d3dLight.Diffuse.a = 1.0f;

            D3DVECTOR position;
            position.x = -1.0f;
            position.y = -1.0f;
            position.z = -1.0f;
            d3dLight.Position = position;

            D3DVECTOR direction;
            direction.x = 1.0f;
            direction.y = 0.0f;
            direction.z = 0.0f;
            d3dLight.Direction = direction;

            globalDirect3DDevice->SetLight(0, &d3dLight); 
            globalDirect3DDevice->LightEnable(0, TRUE);

            D3DMATERIAL9 d3d9Material;
            ZeroMemory(&d3d9Material, sizeof(d3d9Material));
            d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 0.5f;
            d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 0.5f;
            d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 0.5f;
            d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 0.5f;
            d3d9Material.Specular.r = 1.0f;
            d3d9Material.Specular.g = 1.0f;
            d3d9Material.Specular.b = 1.0f;
            d3d9Material.Specular.a = 1.0f;
            d3d9Material.Power = 0.001f;
            
            globalDirect3DDevice->SetMaterial(&d3d9Material);

            globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG); 
	        globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	        globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
            globalDirect3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
        }
        else
        {
            globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);  
        }

        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

        globalWorldMatrixStack->LoadIdentity();
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        camera->ApplyUserTransformations();
        
        globalDirect3DDevice->BeginScene();

        Mesh* mesh = coreOp->mesh;

        if (!MeshSolid)
        {
            globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
            mesh->render();

            globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
            globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);     
            globalDirect3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
            globalDirect3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
            
            for (int f = 0; f < mesh->getNumFaces(); f++)
            {
                if (mesh->faceSelected(f))
                {
                    MeshVertex selectedFaceToDraw[4];
                    int n;
                    int *face = mesh->face(f, n);
                    
                    if (n == 3)
                    {
                        Vec3 pos1 = mesh->pos(face[0]);
                        Vec3 pos2 = mesh->pos(face[1]);
                        Vec3 pos3 = mesh->pos(face[2]);
                        selectedFaceToDraw[0].x = pos1.x;
                        selectedFaceToDraw[0].y = pos1.y;
                        selectedFaceToDraw[0].z = pos1.z;
                        selectedFaceToDraw[0].color = D3DCOLOR_ARGB(128, 255, 0, 0);    
                        selectedFaceToDraw[1].x = pos2.x;
                        selectedFaceToDraw[1].y = pos2.y;
                        selectedFaceToDraw[1].z = pos2.z;
                        selectedFaceToDraw[1].color = D3DCOLOR_ARGB(128, 255, 0, 0);   
                        selectedFaceToDraw[2].x = pos3.x;
                        selectedFaceToDraw[2].y = pos3.y;
                        selectedFaceToDraw[2].z = pos3.z;
                        selectedFaceToDraw[2].color = D3DCOLOR_ARGB(128, 255, 0, 0);
                        globalDirect3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
                        globalDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &selectedFaceToDraw, sizeof(MeshVertex));
                    }
                    else
                    {
                        Vec3 pos1 = mesh->pos(face[0]);
                        Vec3 pos2 = mesh->pos(face[1]);
                        Vec3 pos3 = mesh->pos(face[2]);
                        Vec3 pos4 = mesh->pos(face[3]);
                        selectedFaceToDraw[0].x = pos1.x;
                        selectedFaceToDraw[0].y = pos1.y;
                        selectedFaceToDraw[0].z = pos1.z;
                        selectedFaceToDraw[0].color = D3DCOLOR_ARGB(128, 255, 0, 0);    
                        selectedFaceToDraw[1].x = pos2.x;
                        selectedFaceToDraw[1].y = pos2.y;
                        selectedFaceToDraw[1].z = pos2.z;
                        selectedFaceToDraw[1].color = D3DCOLOR_ARGB(128, 255, 0, 0);   
                        selectedFaceToDraw[2].x = pos4.x;
                        selectedFaceToDraw[2].y = pos4.y;
                        selectedFaceToDraw[2].z = pos4.z;
                        selectedFaceToDraw[2].color = D3DCOLOR_ARGB(128, 255, 0, 0);
                        selectedFaceToDraw[3].x = pos3.x;
                        selectedFaceToDraw[3].y = pos3.y;
                        selectedFaceToDraw[3].z = pos3.z;
                        selectedFaceToDraw[3].color = D3DCOLOR_ARGB(128, 255, 0, 0);
                        globalDirect3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
                        globalDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &selectedFaceToDraw, sizeof(MeshVertex));
                    }

                     
                }
            }
        }
        else
        {
            globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); 
            globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
            mesh->render();
        }
        
	
        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderModelOperator(CoreOperator^ op, int tick)
    {
        Core::Operator* coreOp = op->getOperator();

        for (int i = 0; i < coreNumberOfLights; i++)
            globalDirect3DDevice->LightEnable(i, FALSE);

        coreNumberOfLights = 0;

        // Reset all channel values as we don't want any animation
        // to pollute the view.
        for (int i = 0; i < DB_MAX_OPERATOR_PROPERTIES; i++)
        {
            if (coreOp->properties[i].channelValue1 != 0.0f)
            {
                coreOp->properties[i].channelValue1 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue2 != 0.0f)
            {
                coreOp->properties[i].channelValue2 = 0.0f;
                coreOp->setDirty(true);
            }
            if (coreOp->properties[i].channelValue3 != 0.0f)
            {
                coreOp->properties[i].channelValue3 = 0.0f;
                coreOp->setDirty(true);
            } 
        }

        if (ModelLightning)
        {
            globalDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); 
            globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

            D3DLIGHT9 d3dLight;
            ZeroMemory(&d3dLight, sizeof(d3dLight));
            d3dLight.Type = D3DLIGHT_DIRECTIONAL;
          
            d3dLight.Diffuse.r = 1.0f;
            d3dLight.Diffuse.g = 1.0f;
            d3dLight.Diffuse.b = 1.0f;
            d3dLight.Diffuse.a = 1.0f;

            D3DVECTOR position;
            position.x = 100.0f;
            position.y = 100.0f;
            position.z = -100.0f;
            d3dLight.Position = position;

            D3DVECTOR direction;
            direction.x = 1.0f;
            direction.y = 0.0f;
            direction.z = 0.0f;
            d3dLight.Direction = direction;

            globalDirect3DDevice->SetLight(0, &d3dLight); 
            globalDirect3DDevice->LightEnable(0, TRUE);

            D3DMATERIAL9 d3d9Material;
            ZeroMemory(&d3d9Material, sizeof(d3d9Material));
            d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 0.5f;
            d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 0.5f;
            d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 0.5f;
            d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 0.5f;
            d3d9Material.Specular.r = 1.0f;
            d3d9Material.Specular.g = 1.0f;
            d3d9Material.Specular.b = 1.0f;
            d3d9Material.Specular.a = 1.0f;
            d3d9Material.Power = 0.001f;
            
            globalDirect3DDevice->SetMaterial(&d3d9Material);

            globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
            globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG); 
	        globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	        globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
            globalDirect3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
            coreNumberOfLights++;
        }
        else
        {
            globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        }

        globalDirect3DDevice->Clear(0, 
                                   NULL, 
                                   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                   ClearColor, 
                                   1.0f, 
                                   0);

        camera->ApplyUserTransformations();
        
        globalWorldMatrixStack->LoadIdentity();
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        globalDirect3DDevice->BeginScene();
        coreOp->render();
        globalDirect3DDevice->EndScene();
    }

    void Renderer::RenderDemoSceneRendererOperator(CoreOperator^ op, int tick)
    {
        Core::Operator* coreOp = op->getOperator();

        for (int i = 0; i < coreNumberOfLights; i++)
            globalDirect3DDevice->LightEnable(i, FALSE);

        coreNumberOfLights = 0;

        globalDirect3DDevice->Clear(0, 
               NULL, 
               D3DCLEAR_TARGET, 
               D3DCOLOR_XRGB(0, 0, 0), 
               1.0f, 
               0);

       
        globalWindowHeight = WindowHeight;
        globalWindowWidth = (int)(WindowHeight / 3.0f * 4.0f);
        D3DVIEWPORT9 viewport;
        viewport.X = WindowWidth / 2 - globalWindowWidth / 2;
        viewport.Y = 0;
        viewport.Width = globalWindowWidth;
        viewport.Height = globalWindowHeight;
        viewport.MinZ   = 0.0f;
        viewport.MaxZ   = 1.0f;
        globalDirect3DDevice->SetViewport(&viewport);
     

        globalDirect3DDevice->Clear(0, 
                                     NULL, 
                                     D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
                                     ClearColor, 
                                     1.0f, 
                                     0);

        /*
        globalDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        globalDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        globalDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        globalDirect3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128));
        globalDirect3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); 
	    globalDirect3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	    globalDirect3DDevice->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	    globalDirect3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

	    globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
        globalDirect3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

        D3DLIGHT9 d3dLight;
        ZeroMemory(&d3dLight, sizeof(d3dLight));
        d3dLight.Type = D3DLIGHT_DIRECTIONAL;
      
        d3dLight.Diffuse.r = 1.0f;
        d3dLight.Diffuse.g = 1.0f;
        d3dLight.Diffuse.b = 1.0f;
        d3dLight.Diffuse.a = 1.0f;

        D3DVECTOR position;
        position.x = -1.0f;
        position.y = -1.0f;
        position.z = -1.0f;
        d3dLight.Position = position;

        D3DVECTOR direction;
        direction.x = 1.0f;
        direction.y = 0.0f;
        direction.z = 0.0f;
        d3dLight.Direction = direction;

        globalDirect3DDevice->SetLight(0, &d3dLight); 
        globalDirect3DDevice->LightEnable(0, TRUE);

        D3DMATERIAL9 d3d9Material;
        ZeroMemory(&d3d9Material, sizeof(d3d9Material));
        d3d9Material.Diffuse.r = d3d9Material.Ambient.r = 0.5f;
        d3d9Material.Diffuse.g = d3d9Material.Ambient.g = 0.5f;
        d3d9Material.Diffuse.b = d3d9Material.Ambient.b = 0.5f;
        d3d9Material.Diffuse.a = d3d9Material.Ambient.a = 0.5f;
        
        globalDirect3DDevice->SetMaterial(&d3d9Material);
        */

        //coreOp->preRender(tick);

        camera->ApplyFixedTransformations();
        
        globalWorldMatrixStack->LoadIdentity();
        globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());

        globalDirect3DDevice->BeginScene();
        coreOp->render();
        globalDirect3DDevice->EndScene();

        viewport;
        viewport.X = 0;
        viewport.Y = 0;
        viewport.Width = WindowWidth;
        viewport.Height = WindowHeight;
        viewport.MinZ   = 0.0f;
        viewport.MaxZ   = 1.0f;
        globalDirect3DDevice->SetViewport(&viewport);
    }

    void Renderer::MouseDown(int button, int x, int y)
    {
        camera->MouseDown(button, x, y);
    }

    void Renderer::MouseMove(int x, int y)
    {
         camera->MouseMove(x, y);
    }

    void Renderer::MouseUp(int button, int x, int y)
    {
         camera->MouseUp(button, x, y);
    }

    void Renderer::ResetCamera()
    {
        camera->Reset();
    }

    void Renderer::RenderMesh(Mesh* mesh)
    {      
       
    }
}