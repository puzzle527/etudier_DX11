#pragma once
#include "stdafx.h"

 static float DirToRadian(Vector2 Dir)
 {
     //만약 단위벡터가 아닐수도있으니까
     D3DXVec2Normalize(&Dir, &Dir);
     float Seta;
     if(Dir.y < 0)
     {
         //          360.0*TORADIAN
         Seta = 2.0f*PI - acosf(Dir.x);
     }
     else
     {
         Seta = acosf(Dir.x);
     }
     return Seta;
 }

