#pragma once
#include "stdafx.h"

 static float DirToRadian(Vector2 Dir)
 {
     //���� �������Ͱ� �ƴҼ��������ϱ�
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

