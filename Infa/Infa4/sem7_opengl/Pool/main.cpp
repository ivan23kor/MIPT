#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>

#include <iostream>

#include "Model.h"

const double pi = 3.141592653;
const double CubeEdge = 1.0;

Model model;

void Rotate(const Vector3d& sceneCenter, const Vector3d& axis, double angle, Vector3d& cameraPoint)
{
  Vector3d delta = cameraPoint - sceneCenter;
  delta.Rotate(axis.GetNorm(), angle);
  cameraPoint = sceneCenter + delta;
}

int main()
{
  // create the window
  sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
  window.setVerticalSyncEnabled(true);

  // load resources, initialize the OpenGL states, ...
  // set color and depth clear value
  glClearDepth(10000.f);
  glClearColor(0.f, 0.f, 0.f, 1.f);

  // Enable Z-buffer read and write
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  // Setup a perspective projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.f, 800.0f / 600.0f, 0.01f, 10000.f);

  sf::Clock clock;

  sf::Texture texture;
   //if (!texture.loadFromFile("resources/group.jpg"))
  //if (!texture.loadFromFile("resources/notbad.png"))
  // if (!texture.loadFromFile("resources/jupiter.jpg"))
  // if (!texture.loadFromFile("resources/moon.jpg"))
  if (!texture.loadFromFile("earth.jpg"))
  // if (!texture.loadFromFile("resources/white.png"))
  {
    return EXIT_FAILURE;
  }

  // Bind the texture
  glEnable(GL_TEXTURE_2D);
  sf::Texture::bind(&texture);
  texture.setRepeated(true);
  texture.setSmooth(true);

  // Bind shader
  sf::Shader shader;
  std::cout << shader.loadFromFile("Lightning.vert", "Lightning.frag");
  
  shader.setParameter("ambientIntensity", 0.5f);
  shader.setParameter("diffuseIntensity", 0.8f);
  shader.setParameter("shininess", 1000.0f);
  shader.setParameter("lightSource", sf::Vector3f(10.0f, 10.0f, 10.0f));
  shader.setParameter("texture", texture);
  sf::Shader::bind(&shader);

  // model.LoadFromObjFile("ob_chair_wood.obj");
  // model.LoadFromObjFile("hornbug.obj");
   model.LoadFromObjFile("dna_exported_from_max2011.obj");

  AABB3d sceneAABB = model.GetSceneAABB();

  Vector3d sceneCenter = (sceneAABB.boxPoint1 + sceneAABB.boxPoint2) * 0.5;
  Vector3d cameraPoint = sceneCenter + (sceneAABB.boxPoint2 - sceneCenter) * 2;

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

    const double Angle = 1.0 * pi / 180;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
    {
      cameraPoint = sceneCenter + (cameraPoint - sceneCenter) * (1.0 + 1e-2);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
    {
      cameraPoint = sceneCenter + (cameraPoint - sceneCenter) * (1.0 - 1e-2);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      Rotate(sceneCenter, Vector3d(0.0, 1.0, 0.0) ^ (cameraPoint - sceneCenter), Angle, cameraPoint);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      Rotate(sceneCenter, Vector3d(0.0, 1.0, 0.0) ^ (cameraPoint - sceneCenter), -Angle, cameraPoint);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      Rotate(sceneCenter, Vector3d(0.0, 1.0, 0.0), Angle, cameraPoint);
    } else
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      Rotate(sceneCenter, Vector3d(0.0, 1.0, 0.0), -Angle, cameraPoint); 
    }

    // clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sf::Shader::bind(&shader);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPoint.x, cameraPoint.y, cameraPoint.z, 
      sceneCenter.x, sceneCenter.y, sceneCenter.z,
      0, 1, 0);
    
    model.Draw();
    // model.DrawWireframe();

    /*
    // draw...
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 
      0, 0, 0,
      0, 1, 0);

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
