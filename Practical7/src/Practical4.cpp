/*
-----------------------------------------------------------------------------
Filename:    Practical4.cpp
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.8.x Application Wizard for VC10 (May 2012)
      https://bitbucket.org/jacmoe/ogreappwizards
-----------------------------------------------------------------------------
*/

#include "Practical4.h"

//-------------------------------------------------------------------------------------
Practical4::Practical4(void)
{
}
//-------------------------------------------------------------------------------------
Practical4::~Practical4(void)
{
}

//-------------------------------------------------------------------------------------
void Practical4::createScene(void)
{
    // Create the ground with grass on it
 	Ogre::Plane plane;
    plane.normal = Ogre::Vector3::UNIT_Y;
	// horizontal plane with normal up in y-direction
   	plane.d = 0;//Plane passes through the origin i.e. plane at y = 0
    Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 4500,4500,10,10,true,1,10,10,Ogre::Vector3::UNIT_Z);
   	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity("plane", "floor");
    pPlaneEnt->setMaterialName("Examples/GrassFloor");
   	pPlaneEnt->setCastShadows(false);
	Ogre::SceneNode* floorNode = mSceneMgr->createSceneNode("floor1");
	mSceneMgr->getRootSceneNode()->addChild(floorNode);
	floorNode->attachObject(pPlaneEnt);


    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);


	// Now to draw a ball on the ground at the origin
	// First create a ball Entity from an Ogre model
	Ogre::Entity* ball = mSceneMgr->createEntity("sphere1","geosphere8000.mesh");
	ball->setMaterialName("Examples/Hilite/Yellow");
	double ballModelRadius = 200; // Radius of actual model in //"geosphere8000.mesh"
	double ballScale = 0.02;//To multiply radius by this factor
	double ballRadius;  // To store actual radius used here

	// Create a new sceneNode and attach it to the rootSceneNode 
	//as a child of the scene manager
	Ogre::SceneNode* ballNode = mSceneMgr->createSceneNode("sphere1");
	mSceneMgr->getRootSceneNode()->addChild(ballNode);
	ballNode->attachObject(ball);

	// Amend the properties of the ball to suit your purposes
	ball->setCastShadows(true);
	ballNode->scale(ballScale, ballScale, ballScale);
	ballRadius = ballScale*ballModelRadius; // Actual radius 
	ballNode->setPosition(Ogre::Vector3(0,ballRadius,0)); // position //the ball on top of the ground
	// Create an instance of the PhysicsObject class
	m_sphereObject = new PhysicsObject();
	// Now initialise all of it�s properties to match the //graphics model of the sphere as in ballNode
	m_sphereObject->initialise(ballNode,ballRadius,ballNode->getPosition(),Ogre::Vector3(0,30,0), 10.0f, 10.0f);



	Ogre::Entity* target = mSceneMgr->createEntity("target1", "geosphere8000.mesh");
	target->setMaterialName("Examples/Hilite/Yellow");
	//double ballModelRadius = 200; // Radius of actual model in //"geosphere8000.mesh"
	//double ballScale = 0.02;//To multiply radius by this factor
	//double ballRadius;  // To store actual radius used here

	Ogre::SceneNode* targetNode = mSceneMgr->createSceneNode("target1");
	mSceneMgr->getRootSceneNode()->addChild(targetNode);
	targetNode->attachObject(target);

	target->setCastShadows(true);
	targetNode->scale(ballScale, ballScale, ballScale);
	targetNode->setPosition(Ogre::Vector3((rand() % 200) + 50, 0, 0));
	m_targetObject = new PhysicsObject();
    m_targetObject->initialise(targetNode,0,targetNode->getPosition(),Ogre::Vector3(0,30,0),10.0f,10.0f);


	//Ogre::Entity *cube = mSceneMgr->createEntity("cube", "cube.mesh");
	//// Choose a material texture for the cube
	//cube->setMaterialName("Examples/RustySteel");
	//// Create a new sceneNode for the cube, attach it to the rootSceneNode 
	////as a child of the scene manager
	//Ogre::SceneNode *cubeNode = mSceneMgr->createSceneNode("cubeNode");
	//mSceneMgr->getRootSceneNode( )->addChild(cubeNode);
	//cubeNode->attachObject( cube );
	//cube->setCastShadows(true);
	//float cubeModelLength = 100;  // The cube actual model size
	//float cubeLength = 2;  // The cube size that we want
	//// Change size of graphics drawing of cube to that of cubeLength
	//double cubeScale = cubeLength/cubeModelLength;
	//cubeNode->scale(cubeScale, cubeScale, cubeScale);
	//	
	//// Position the cube to sit exactly on the ground
	//cubeNode-> setPosition(Ogre::Vector3(0, cubeLength/2,0));

	tries = 0;
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Practical4 app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
