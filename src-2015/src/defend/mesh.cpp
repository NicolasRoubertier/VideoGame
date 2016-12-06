// Sylvain.Lefebvre@inria.fr  2012-04-10
// ------------------------------------------------------------------

#include "mesh.h"

// ------------------------------------------------------------------

IndexedVertexBuffer *makeBuffer(TriangleMesh *mesh)
{
  IndexedVertexBuffer *buf = new IndexedVertexBuffer();
  buf->begin(GPUMESH_TRIANGLELIST);
  ForIndex(v,mesh->numVertices()) {
    buf->vertex_raw( mesh->vertexDataAt(v), mesh->sizeOfVertexData() );
  }
  ForIndex(t,mesh->numTriangles()) {
    v3u tri = mesh->triangleAt(t);
    ForIndex(i,3) {
      buf->index( tri[i] );
    }
  }
  buf->end();
  return buf;
}

// ------------------------------------------------------------------

IndexedVertexBuffer *makeBufferForSurface(TriangleMesh *mesh, int srf)
{
  IndexedVertexBuffer *buf = new IndexedVertexBuffer();
  buf->begin(GPUMESH_TRIANGLELIST);
  // add all vertices
  ForIndex(v,mesh->numVertices()) {
    buf->vertex_raw( mesh->vertexDataAt(v), mesh->sizeOfVertexData() );
  }
  // add triangles for the surface only
  ForIndex(j,mesh->surfaceNumTriangles(srf)) {
    int t   = mesh->surfaceTriangleIdAt(srf,j);
    v3u tri = mesh->triangleAt(t);
    ForIndex(i,3) {
      buf->index( tri[i] );
    }
  }
  buf->end();
  return buf;
}

// ------------------------------------------------------------------

TriangleMesh *loadTriangleMesh_cached(std::string fname)
{
  std::string cached = fname + ".mesh";
  if (LibSL::System::File::exists( cached.c_str() )) {
    return loadTriangleMesh( cached.c_str() );
  } else {
    TriangleMesh *g = loadTriangleMesh( fname.c_str() );
    saveTriangleMesh( cached.c_str(), g );
    return g;
  }
}

// ------------------------------------------------------------------

t_mesh *loadMesh(const char *fname)
{
  t_mesh *m      = new t_mesh;
  m->geometry    = loadTriangleMesh_cached( DATA_PATH + std::string(fname) );
  std::cerr << fname << " \t" << m->geometry->numTriangles() << " triangles." << std::endl;
  m->numSurfaces = m->geometry->numSurfaces();
  if ( m->numSurfaces >= MAX_SURFACES ) {
    std::cerr << "Too many surfaces in object. Increase MAX_SURFACES." << std::endl;
    exit (-1);
    return NULL;
  }
  if ( m->numSurfaces == 0 ) {
    // untextured model
    m->numSurfaces = 1;
    m->surfaces[0] = makeBuffer( m->geometry );
    m->textures[0] = NULL;
  } else {
    std::map<std::string,Tex2DRGBA*> textures;
    ForIndex(srf, m->numSurfaces ) {
      std::cerr << '.';
      m->surfaces[srf]    = makeBufferForSurface( m->geometry,srf );
      std::string imgfile = (DATA_PATH + std::string(m->geometry->surfaceTextureName(srf)));
      if (LibSL::System::File::exists(imgfile.c_str())) {
        std::map<std::string,Tex2DRGBA*>::iterator T = textures.find( imgfile );
        if (T == textures.end() ) {
          ImageRGBA *img      = loadImageRGBA( imgfile.c_str() );
          m->textures[srf]    = new Tex2DRGBA( img->pixels(), GPUTEX_AUTOGEN_MIPMAP );
          textures.insert( make_pair(imgfile,m->textures[srf]) );
          delete (img);
        } else {
          m->textures[srf]    = T->second;
        }
      } else {
        m->textures[srf] = NULL;
      }
    }
  }
  return m;
}

// ------------------------------------------------------------------

void    drawMesh(t_mesh *m)
{
  glDisable( GL_CULL_FACE );
  ForIndex(srf, m->numSurfaces ) {
    if ( m->textures[srf] != NULL ) {
      glActiveTextureARB( GL_TEXTURE0 );
      glBindTexture( GL_TEXTURE_2D, m->textures[srf]->handle() );
    }
    m->surfaces[srf]->render();
  }
}

// ------------------------------------------------------------------
