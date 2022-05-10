#pragma once

#include "Vector2.h"
#include <assert.h>
#include <GL/gl.h>
#include <queue>
#include "Vector3.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "AABB3.h"

struct Model
{
public:
  struct Triangle
  {
    Triangle()
    {
    }

    Triangle(int vertexIndex0, int vertexIndex1, int vertexIndex2)
    {
      vertexIndices[0] = vertexIndex0;
      vertexIndices[1] = vertexIndex1;
      vertexIndices[2] = vertexIndex2;
    }

    int vertexIndices[3];
    int normalIndices[3];
    int texCoordsIndices[3];
  };

  void Draw()
  {
    for (size_t triangleIndex = 0; triangleIndex < triangles.size(); ++triangleIndex)
    {
      glBegin(GL_TRIANGLES);
        for (int vertexNumber = 0; vertexNumber < 3; ++vertexNumber)
        {
          
          glTexCoord2f(texCoords[triangles[triangleIndex].texCoordsIndices[vertexNumber]].x, 
                       texCoords[triangles[triangleIndex].texCoordsIndices[vertexNumber]].y);
          
          glNormal3f(normals[triangles[triangleIndex].normalIndices[vertexNumber]].x,
                     normals[triangles[triangleIndex].normalIndices[vertexNumber]].y,
                     normals[triangles[triangleIndex].normalIndices[vertexNumber]].z);

          glVertex3f(vertices[triangles[triangleIndex].vertexIndices[vertexNumber]].x,
                     vertices[triangles[triangleIndex].vertexIndices[vertexNumber]].y,
                     vertices[triangles[triangleIndex].vertexIndices[vertexNumber]].z);

        }
      glEnd();
    }
  }

  void DrawWireframe()
  {
    glLineWidth(1.0);
    glColor3f(1.0, 1.0, 1.0);
    for (size_t triangleIndex = 0; triangleIndex < triangles.size(); ++triangleIndex)
    {
      for (int vertexNumber = 0; vertexNumber < 3; ++vertexNumber)
      {
        glBegin(GL_LINES);
          glVertex3f(vertices[triangles[triangleIndex].vertexIndices[vertexNumber]].x,
                     vertices[triangles[triangleIndex].vertexIndices[vertexNumber]].y,
                     vertices[triangles[triangleIndex].vertexIndices[vertexNumber]].z);

          glVertex3f(vertices[triangles[triangleIndex].vertexIndices[(vertexNumber + 1) % 3]].x,
                     vertices[triangles[triangleIndex].vertexIndices[(vertexNumber + 1) % 3]].y,
                     vertices[triangles[triangleIndex].vertexIndices[(vertexNumber + 1) % 3]].z);
        glEnd();
      }
    }
  }

  /*double GetTriangleSquare(size_t triangleIndex) const
  {
    Vector3d edge0 = voxels[triangles[triangleIndex].indices[2]].pos - voxels[triangles[triangleIndex].indices[0]].pos;
    Vector3d edge1 = voxels[triangles[triangleIndex].indices[1]].pos - voxels[triangles[triangleIndex].indices[0]].pos;
    return fabs((edge0 ^ edge1).Len()) * 0.5;
  } */

  void LoadFromObjFile(const std::string& filename)
  {
    std::string line;
    std::ifstream objFile(filename);

    if (objFile.is_open())
    {
      while (!objFile.eof()) 
      {
        getline (objFile,line);

        if (line.substr(0, 2) == "v ")
        {
          line[0] = ' ';

          Vector3d vertex;
          sscanf(line.c_str(),"%lf %lf %lf",
            &(vertex.x),
            &(vertex.y),
            &(vertex.z));
          vertices.push_back(vertex);
        } else
        if (line.substr(0, 2) == "vn")
        {
          line[0] = line[1] = ' ';
          Vector3d normal;
          sscanf(line.c_str(),"%lf %lf %lf",
            &normal.x,
            &normal.y,
            &normal.z);
          normals.push_back(normal);
        } else
        if (line.substr(0, 2) == "vt")
        {
          line[0] = line[1] = ' ';
          Vector2 tc;
          sscanf(line.c_str(),"%f %f",
            &tc.x,
            &tc.y);
          texCoords.push_back(tc);
        } else
        if (line.substr(0, 2) == "f ")  // The first character is an 'f': on this line is a point stored
        {
          line[0] = ' '; // Set first character to 0. This will allow us to use sscanf
          Triangle tri;
          int v, t, n;

          int items = sscanf(line.c_str(),"%i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i",
            &tri.vertexIndices[0],
            &tri.texCoordsIndices[0],
            &tri.normalIndices[0],

            &tri.vertexIndices[1],
            &tri.texCoordsIndices[1],
            &tri.normalIndices[1],

            &tri.vertexIndices[2],
            &tri.texCoordsIndices[2],
            &tri.normalIndices[2],
            &v, &t, &n);

          for (int i = 0; i < 3; ++i)
          {
            tri.vertexIndices[i]--;
            tri.normalIndices[i]--;
            tri.texCoordsIndices[i]--;
          }
          v--; t--; n--;
  
          if (items == 12)
          {
            Triangle auxTri;
            auxTri.vertexIndices[0] = tri.vertexIndices[0];
            auxTri.vertexIndices[1] = tri.vertexIndices[2];
            auxTri.vertexIndices[2] = v;

            auxTri.texCoordsIndices[0] = tri.texCoordsIndices[0];
            auxTri.texCoordsIndices[1] = tri.texCoordsIndices[2];
            auxTri.texCoordsIndices[2] = t;

            auxTri.normalIndices[0] = tri.normalIndices[0];
            auxTri.normalIndices[1] = tri.normalIndices[2];
            auxTri.normalIndices[2] = n;
            triangles.push_back(auxTri);
          }
          triangles.push_back(tri);
        }
      }
      objFile.close();
    } else
    {
      std::cout << "Unable to open file";
    }
/*
    for (int i = 0; i < triangles.size(); ++i)
    {
      for (int vertexNumber = 0; vertexNumber < 3; ++vertexNumber)
      {
        if (triangles[i].normalIndices[vertexNumber] >= normals.size()) std::cout << i << "\n";
        if (triangles[i].vertexIndices[vertexNumber] >= vertices.size()) std::cout << i << "\n";
        if (triangles[i].texCoordsIndices[vertexNumber] >= texCoords.size()) std::cout << i << "\n";
      }
    }
*/
  }

  AABB3d GetSceneAABB() const
  {
    AABB3d aabb;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
      aabb.Expand(vertices[i]);
    }
    return aabb;
  }

  std::vector<Vector3d> vertices;
  std::vector<Vector3d> normals;
  std::vector<Vector2>  texCoords;
  std::vector<Triangle> triangles;
};
