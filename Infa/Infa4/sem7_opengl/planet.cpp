#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Maths/Vector2.h"
#include <assert.h>
#include <iostream>
#include <glut.h>
#include <queue>
#include "Maths/Vector3.h"
#include <math.h>

const double pi = 3.141592653;

struct Voxel
{
  Vector3d pos;
  Vector3d normal;
  Vector2  texCoords;
};

std::vector<Voxel> voxels;

struct Triangle
{
  Triangle()
  {
  }

  Triangle(int voxelIndex0, int voxelIndex1, int voxelIndex2)
  {
    indices[0] = voxelIndex0;
    indices[1] = voxelIndex1;
    indices[2] = voxelIndex2;
  }

  int indices[3];

  double Square() const
  {
    Vector3d edge0 = voxels[indices[2]].pos - voxels[indices[0]].pos;
    Vector3d edge1 = voxels[indices[1]].pos - voxels[indices[0]].pos;
    return fabs((edge0 ^ edge1).Len()) * 0.5;
  }
};

std::vector<Triangle> triangles;

void BuildSphere(const Vector3d& center, double radius)
{
  voxels.clear();
  triangles.clear();

  std::queue<Triangle> triangleQueue;

  Vector3d icosaVertices[12];

  double theta = 26.56505117707799 * pi / 180.0; // refer paper for theta value
  double stheta = std::sin(theta);
  double ctheta = std::cos(theta);

  icosaVertices[0] = Vector3d(0.0f, 0.0f, -1.0f); // the lower vertex

  // the lower pentagon
  double phi = pi / 5.0;
  for (int i = 1; i < 6; ++i) 
  {
    icosaVertices[i] = Vector3d(ctheta * std::cos(phi), ctheta * std::sin(phi), -stheta);
    phi += 2.0 * pi / 5.0;
  }

  // the upper pentagon
  phi = 0.0;
  for (int i = 6; i < 11; ++i) 
  {
    icosaVertices[i] = Vector3d(ctheta * std::cos(phi), ctheta * std::sin(phi), stheta);
    phi += 2.0 * pi / 5.0;
  }

  icosaVertices[11] = Vector3d(0.0f, 0.0f, 1.0f); // the upper vertex

  for (int i = 0; i < 12; ++i)
  {
    Voxel voxel;
    voxel.pos = icosaVertices[i];
    voxel.normal = Vector3d(0, 0, 0); // unused in this program
    voxels.push_back(voxel);
  }

  triangleQueue.push(Triangle(0, 2, 1));
  triangleQueue.push(Triangle(0, 3, 2));
  triangleQueue.push(Triangle(0, 4, 3));
  triangleQueue.push(Triangle(0, 5, 4));
  triangleQueue.push(Triangle(0, 1, 5));

  triangleQueue.push(Triangle(1, 2, 7));
  triangleQueue.push(Triangle(2, 3, 8));
  triangleQueue.push(Triangle(3, 4, 9));
  triangleQueue.push(Triangle(4, 5, 10));
  triangleQueue.push(Triangle(5, 1, 6));

  triangleQueue.push(Triangle(1, 7, 6));
  triangleQueue.push(Triangle(2, 8, 7));
  triangleQueue.push(Triangle(3, 9, 8));
  triangleQueue.push(Triangle(4, 10, 9));
  triangleQueue.push(Triangle(5, 6, 10));

  triangleQueue.push(Triangle(6, 7, 11));
  triangleQueue.push(Triangle(7, 8, 11));
  triangleQueue.push(Triangle(8, 9, 11));
  triangleQueue.push(Triangle(9, 10, 11));
  triangleQueue.push(Triangle(10, 6, 11));

  double initialSquare = triangleQueue.front().Square();

  while (triangleQueue.front().Square() * 100 > initialSquare) {
    Triangle tri = triangleQueue.front();
    triangleQueue.pop();

    Vector3d p01 = (voxels[tri.indices[0]].pos + voxels[tri.indices[1]].pos) * 0.5;
    Vector3d p02 = (voxels[tri.indices[0]].pos + voxels[tri.indices[2]].pos) * 0.5;
    Vector3d p12 = (voxels[tri.indices[1]].pos + voxels[tri.indices[2]].pos) * 0.5;

    Voxel  v;
    v.pos = p01;
    voxels.push_back(v);

    v.pos = p02;
    voxels.push_back(v);

    v.pos = p12;
    voxels.push_back(v);

    Triangle newbie;
    newbie.indices[0] = tri.indices[0];
    newbie.indices[1] = voxels.size() - 3; // p01
    newbie.indices[2] = voxels.size() - 2; // p02
    triangleQueue.push(newbie);

    newbie.indices[0] = voxels.size() - 3; // p01
    newbie.indices[1] = tri.indices[1]; 
    newbie.indices[2] = voxels.size() - 1; // p12
    triangleQueue.push(newbie);

    newbie.indices[0] = voxels.size() - 2; // p02
    newbie.indices[1] = voxels.size() - 1; // p12
    newbie.indices[2] = tri.indices[2]; 
    triangleQueue.push(newbie);

    newbie.indices[0] = voxels.size() - 1; 
    newbie.indices[1] = voxels.size() - 2; 
    newbie.indices[2] = voxels.size() - 3;
    triangleQueue.push(newbie);
  }

  while (!triangleQueue.empty())
  {
    Triangle tri = triangleQueue.front();
    triangleQueue.pop();
    triangles.push_back(tri);
  }

  for (size_t voxelIndex = 0; voxelIndex < voxels.size(); ++voxelIndex)
  {
    voxels[voxelIndex].pos.Normalize();
    voxels[voxelIndex].pos *= radius;
    voxels[voxelIndex].pos += center;

    double x = atan2(voxels[voxelIndex].pos.x , voxels[voxelIndex].pos.z);
    x /= pi;
    x += 1.0;
    x *= 0.5;

    double y = acos(voxels[voxelIndex].pos.y / voxels[voxelIndex].pos.Len());
    y /= pi;

    voxels[voxelIndex].texCoords = Vector2(x, y);
  }
}

int main()
{
  // create the window
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
  window.setVerticalSyncEnabled(true);

  // load resources, initialize the OpenGL states, ...
  // Set color and depth clear value
  glClearDepth(10.f);
  glClearColor(0.f, 0.f, 0.f, 0.f);

  // Enable Z-buffer read and write
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  // Setup a perspective projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.f, 800.0f / 600.0f, 0.1f, 10.f);

  Vector3d cameraPoint(1.0, 1.0, 1.0);

  sf::Clock clock;
  const double CubeEdge = 1.0;

  sf::Texture texture;
  // if (!texture.loadFromFile("resources/group.jpg"))
  //if (!texture.loadFromFile("resources/notbad.png"))
  //if (!texture.loadFromFile("resources/jupiter.jpg"))
  // if (!texture.loadFromFile("resources/moon.jpg"))
  if (!texture.loadFromFile("resources/earth.jpg"))
  {
    return EXIT_FAILURE;
  }

  // Bind the texture
  glEnable(GL_TEXTURE_2D);
  sf::Texture::bind(&texture);

  BuildSphere(Vector3d(0, 0, 0), 1.0);

  // run the main loop
  bool running = true;
  while (running)
  {
    // handle events
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        // end the program
        running = false;
      } else 
      if (event.type == sf::Event::Resized)
      {
        // adjust the viewport when the window is resized
        glViewport(0, 0, event.size.width, event.size.height);
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
    {
      cameraPoint *= (1.0 + 1e-2);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
    {
      cameraPoint *= (1.0 - 1e-2);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      cameraPoint.Rotate((Vector3d(0.0, 1.0, 0.0) ^ cameraPoint).GetNorm(), 1.0 * pi / 180);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      cameraPoint.Rotate((Vector3d(0.0, 1.0, 0.0) ^ cameraPoint).GetNorm(), -1.0 * pi / 180);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      cameraPoint.Rotate(Vector3d(0.0, 1.0, 0.0), 1.0 * pi / 180);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      cameraPoint.Rotate(Vector3d(0.0, 1.0, 0.0), -1.0 * pi / 180);
    }

    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPoint.x, cameraPoint.y, cameraPoint.z, 
      0, 0, 0, 
      0, 1, 0); 

    /*glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -0.f);
    glRotatef(clock.getElapsedTime().asMicroseconds() * 1e-6f, 1.f, 0.f, 0.f);
    glRotatef(clock.getElapsedTime().asMicroseconds() * 3e-6f, 0.f, 1.f, 0.f);
    glRotatef(clock.getElapsedTime().asMicroseconds() * 9e-6f, 0.f, 0.f, 1.f);
    */


    for (size_t triangleIndex = 0; triangleIndex < triangles.size(); ++triangleIndex)
    {
      
      glBegin(GL_TRIANGLES);
        for (int vertexNumber = 0; vertexNumber < 3; ++vertexNumber)
        {
          glTexCoord2f(voxels[triangles[triangleIndex].indices[vertexNumber]].texCoords.x, 
                       voxels[triangles[triangleIndex].indices[vertexNumber]].texCoords.y);

          glVertex3f(voxels[triangles[triangleIndex].indices[vertexNumber]].pos.x,
                     voxels[triangles[triangleIndex].indices[vertexNumber]].pos.y,
                     voxels[triangles[triangleIndex].indices[vertexNumber]].pos.z);
        }
      glEnd();
      
      /*
      glLineWidth(1.0); 
      glColor3f(1.0, 0.0, 0.0);

      for (int edgeNumber = 0; edgeNumber < 3; ++edgeNumber)
      {
        glBegin(GL_LINES);
          glVertex3f(triangles[triangleIndex].p[edgeNumber].x, triangles[triangleIndex].p[edgeNumber].y, triangles[triangleIndex].p[edgeNumber].z);
          glVertex3f(triangles[triangleIndex].p[(edgeNumber + 1) % 3].x, 
                     triangles[triangleIndex].p[(edgeNumber + 1) % 3].y, 
                     triangles[triangleIndex].p[(edgeNumber + 1) % 3].z);
        glEnd();
      }*/
    }

    /*
    // draw...
    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0);
    glVertex3f(  CubeEdge / 2.0, -CubeEdge / 2.0, CubeEdge / 2.0 );
    glVertex3f(  CubeEdge / 2.0,  CubeEdge / 2.0, CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0,  CubeEdge / 2.0, CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0, -CubeEdge / 2.0, CubeEdge / 2.0 );
    glEnd();
 
    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( CubeEdge / 2.0, -CubeEdge / 2.0, -CubeEdge / 2.0 );
    glVertex3f( CubeEdge / 2.0,  CubeEdge / 2.0, -CubeEdge / 2.0 );
    glVertex3f( CubeEdge / 2.0,  CubeEdge / 2.0,  CubeEdge / 2.0 );
    glVertex3f( CubeEdge / 2.0, -CubeEdge / 2.0,  CubeEdge / 2.0 );
    glEnd();
 
    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -CubeEdge / 2.0, -CubeEdge / 2.0,  CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0,  CubeEdge / 2.0,  CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0,  CubeEdge / 2.0, -CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0, -CubeEdge / 2.0, -CubeEdge / 2.0 );
    glEnd();
 
    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  CubeEdge / 2.0,  CubeEdge / 2.0,  CubeEdge / 2.0 );
    glVertex3f(  CubeEdge / 2.0,  CubeEdge / 2.0, -CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0,  CubeEdge / 2.0, -CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0,  CubeEdge / 2.0,  CubeEdge / 2.0 );
    glEnd();
 
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  CubeEdge / 2.0, -CubeEdge / 2.0, -CubeEdge / 2.0 );
    glVertex3f(  CubeEdge / 2.0, -CubeEdge / 2.0,  CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0, -CubeEdge / 2.0,  CubeEdge / 2.0 );
    glVertex3f( -CubeEdge / 2.0, -CubeEdge / 2.0, -CubeEdge / 2.0 );
    glEnd();
    */
    // end the current frame (internally swaps the front and back buffers)
    window.display();
  }

  // release resources...

  return EXIT_SUCCESS;
}
