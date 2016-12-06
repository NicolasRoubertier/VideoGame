// Sylvain.Lefebvre@inria.fr  2012-04-10
// ------------------------------------------------------------------

#include "grid.h"

// ------------------------------------------------------------------

v2i     g_Path[PATH_LENGTH] = {V2I(0,1),V2I(10,1),V2I(10,3),V2I(0,3),V2I(0,5),V2I(10,5),V2I(10,7),V2I(0,7),V2I(0,9),V2I(11,9)};
t_Cell *g_Grid[GRID_SZ][GRID_SZ];

// ------------------------------------------------------------------

void initGrid()
{
  ForIndex(j,GRID_SZ) {
    ForIndex(i,GRID_SZ) {
      g_Grid[i][j]           = new t_Cell;
      g_Grid[i][j]->tower    = NULL;
      g_Grid[i][j]->canBuild = true;
    }
  }
  // follow path and flag as non contructible
  v2i cur = g_Path[0];
  for (int p=1 ; p<PATH_LENGTH ; p++ ) {
    while (cur != g_Path[p]) {
      g_Grid[cur[0]][cur[1]]->canBuild = false;
      cur += normalize(g_Path[p]-cur);
    }
    g_Grid[cur[0]][cur[1]]->canBuild = false;
  }
}

// ------------------------------------------------------------------
