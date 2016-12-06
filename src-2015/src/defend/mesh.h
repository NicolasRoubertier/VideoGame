// Sylvain.Lefebvre@inria.fr  2012-04-10
// ------------------------------------------------------------------

#pragma once

#include "../common/base.h"

// ------------------------------------------------------------------

#define MAX_SURFACES 1024

typedef struct {
  TriangleMesh        *geometry;
  IndexedVertexBuffer *surfaces[MAX_SURFACES];
  Tex2DRGBA           *textures[MAX_SURFACES];
  int                  numSurfaces;
} t_mesh;

// ------------------------------------------------------------------

t_mesh *loadMesh(const char*fname);
void    drawMesh(t_mesh *m);

// ------------------------------------------------------------------
