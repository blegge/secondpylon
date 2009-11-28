// Copyright 2009 Brian Legge

// This is a simple application demonstrating the use of secondpylon to build a
// basic little renderering. Note that this is meant for a simple, one-off
// application window. Subwindows within another application and full screen
// window support is more complex.

#include <windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <cstdio>
#include "secondpylon/plat/plat_types.h"
#include "secondpylon/diag/diag_assert.h"
#include "secondpylon/math/math_vec2.h"
#include "secondpylon/math/math_vec3.h"
#include "secondpylon/renderer/renderer_color.h"
#include "secondpylon/renderer/renderer_device.h"
#include "secondpylon/renderer/renderer_dynamicmesh.h"
#include "secondpylon/renderer/renderer_material.h"
#include "secondpylon/renderer/renderer_deviceparameters.h"
#include "secondpylon/data/data_outstream.h"
#include "./viewscene_windowutils.h"
#include "./viewscene_applicationutils.h"


namespace secondpylon {
namespace viewscene {

static renderer::Device* g_device = NULL;

float Random(float min, float max) {
  return min + (max-min)* (rand() / static_cast<float>(RAND_MAX));
}

void renderpoly() {
  // Create a mesh and fill in a few verts
  renderer::DynamicMesh* mesh = g_device->CreateDynamicMesh(3, 3);

  {
    plat::uint32* indices = mesh->LockIndices(3);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    mesh->UnlockIndices();
  }

  {
    renderer::DynamicMesh::Vertex* vertices =
      (renderer::DynamicMesh::Vertex*)mesh->LockVertices(3);
    vertices[0].Write(math::vec3<float>(Random(-1, 1), Random(-1, 1), 0));
    vertices[1].Write(math::vec3<float>(Random(-1, 1), Random(-1, 1), 0));
    vertices[2].Write(math::vec3<float>(Random(-1, 1), Random(-1, 1), 0));
    mesh->UnlockVertices();
  }

  const char vertexShader[] =
    "float4 entry(float4 inPos : POSITION) : POSITION"
    "{"
      "return inPos;"
    "}";

  const char pixelShader[] =
    "float4 entry() : COLOR"
    "{"
      "return float4 (1, 0, 0, 1);"
    "}";

  typedef data::OutStream<data::MemStorage, data::SBytePacker>
    TOutMemoryStream;

  typedef data::InStream<data::MemStorage, data::SBytePacker>
    TInMemoryStream;

  data::MemStorage vertex_shader_buffer;
  {
    TOutMemoryStream vertex_shader_stream(&vertex_shader_buffer);
    vertex_shader_stream.Write(vertexShader);
  }

  data::MemStorage pixel_shader_buffer;
  {
    TOutMemoryStream pixel_shader_stream(&pixel_shader_buffer);
    pixel_shader_stream.Write(pixelShader);
  }

  TInMemoryStream pixel_shader_in_stream(&pixel_shader_buffer);
  TInMemoryStream vertex_shader_in_stream(&vertex_shader_buffer);
  renderer::Material* material = g_device->CreateMaterial(
    &pixel_shader_in_stream, &vertex_shader_in_stream);

  // @todo We need to add references here to avoid the resources getting
  // released before rendering. We also don't have a way to handle possibly
  // in-place modifications before rendering occurs. This will be simplest to
  // handle at the source end. Consider updating resources to get released
  // prior to write and recreated.
  renderer::SubMeshRenderRequest poly_request;
  poly_request.pixel_shader_ = material->GetPixelShader();
  poly_request.vertex_shader_ = material->GetVertexShader();
  poly_request.index_buffer_ = mesh->GetIndices();
  poly_request.vertex_buffer_ = mesh->GetVertices();
  poly_request.vertex_declaration_ = mesh->GetVertexDecl();
  poly_request.vertex_stride_ = mesh->GetVertexStride();
  poly_request.vertex_count_ = mesh->GetVertexCount();
  poly_request.index_count_ = mesh->GetIndexCount();

  g_device->Draw(poly_request);

  mesh->Destroy();
  mesh = NULL;

  material->Destroy();
  material = NULL;
}

void render() {
  renderer::Color clearColor;
  clearColor.Encode(0, 255, 255, 255);
  g_device->Clear(clearColor);

  if (g_device->BeginScene()) {
    renderpoly();
    g_device->EndScene();
    g_device->Flip();
  }
}

}  // namespace viewscene
}  // namespace secondpylon


int WINAPI WinMain(HINSTANCE instance,
           HINSTANCE /*hPrevInstance*/,
           LPSTR   /*lpCmdLine*/,
           int     /*nCmdShow*/) {
  // Create Window and run the application
  secondpylon::viewscene::WindowUtils::register_classes(instance);
  secondpylon::viewscene::WindowUtils::window app_window;
  secondpylon::viewscene::WindowUtils::create_window(
    &app_window, instance, L"viewscene", vec2i(128, 128));

  secondpylon::renderer::DeviceParameters params;
  params.adapter = 0;
  params.dims = vec2i(128, 128);
  params.parent_window = app_window.window_;
  params.vsync = false;

  {
    secondpylon::renderer::Device device(params);
    secondpylon::viewscene::g_device = &device;
    ApplicationUtils::run_app(secondpylon::viewscene::render);
    secondpylon::viewscene::g_device = NULL;
  }

  secondpylon::viewscene::WindowUtils::destroy_window(&app_window);
  secondpylon::viewscene::WindowUtils::unregister_classes(instance);

  return 0;
}
