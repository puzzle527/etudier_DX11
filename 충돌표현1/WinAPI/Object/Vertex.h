#pragma once
#include "stdafx.h"

//���������� �������̷��
//�̵�,Ȯ�� ���,ȸ��ǥ���� �����ϴ�
namespace Vertex
{

    //���� ����ü
    //3��ȸ�� ����ϱ����� Vector3���
    struct VertexP
    {
        VertexP() { Position.z = 0.0f; }

        VertexP(Vector3 position)
            : Position(position) //�̴ϼȶ�����
        {
            Position.z = 0.0f;
        }

        Vector3 Position;
    };

    struct VertexPC
    {
        VertexPC() { Position.z = 0.0f; }

        VertexPC(Vector3 position, Color  color)
            : Position(position), color(color)
        {
            Position.z = 0.0f;
        }

        Vector3 Position;
        Color   color;
    };

    //struct VertexPT
    //{
    //    VertexPT() { Position.z = 0.0f; }

    //    VertexPT(Vector3 position, Vector2  uv)
    //        : Position(position), Uv(uv)
    //    {
    //        Position.z = 0.0f;
    //    }

    //    Vector3 Position;
    //    Vector2 Uv; //�ؽ��� ��ǥ
    //};


}