#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(void)
{
	coefficientOfRestitution = -0.5f;
	coefficientOfFriction = -0.6f;
}

PhysicsObject::~PhysicsObject(void)
{
}

//  1st param:	Ogre::SceneNode*  
//	the node for the graphics model of the physicsObject
//	2nd param:	double  
//			for the radius of the physicsObject
//  3rd param: 	Ogre::Vector3
//			for the vector position of the physicsObject
//  4th param:	Ogre::Vector3
//			for the vector velocity of the physicsObject 

void PhysicsObject::initialise(Ogre::SceneNode* myNode, double myRadius,Ogre::Vector3 myPosition,Ogre::Vector3 myVelocity)
{
	m_accel = Ogre::Vector3(0, -9.81, 0);
	m_objectNode = myNode;	// The scene node for the model
	setMove(false);	// Or to true if you want the sphere to move now
	m_radius = myRadius;	// fix the radius the same as the model
	m_velocity = myVelocity;	// fix velocity
	m_position = myPosition;	// fix position
	m_timeMoving = 0;	//set/reset time
}

void PhysicsObject::update(double timeChange)
{
	//only apply friction if moving along plane
	if(m_velocity.normalisedCopy() != Ogre::Vector3::UNIT_Y && m_position.y == m_radius)
	{
		//a = -coeffFriction * 9.81 * v.normalised
		m_accel = coefficientOfFriction * 9.81 * m_velocity.normalisedCopy();

		if(m_velocity.x < 0 || m_velocity.z < 0)
			setMove(false);
	}

	//s = s0 + ut + (1/2)at^2
	m_position = m_position + (m_velocity * timeChange) + (0.5 * m_accel * (timeChange*timeChange));

	//v = u + at
	m_velocity = m_velocity + m_accel * timeChange;

	//update max displacement
	if(m_position.y > m_maxDisplacement.y)
	{
		m_maxDisplacement.y = m_position.y;
		m_timeMoving += timeChange;
	}
	if(m_position.x > m_maxDisplacement.x)
	{
		m_maxDisplacement.x = m_position.x;
		m_timeMoving += timeChange;
	}
	if(m_position.z > m_maxDisplacement.z)
	{
		m_maxDisplacement.z = m_position.z;
		m_timeMoving += timeChange;
	}

	//update position of the node to match physics
	m_objectNode->setPosition(m_position);
}

void PhysicsObject::bounce()
{
	m_velocity *= coefficientOfRestitution;
}

void PhysicsObject::shove(Ogre::Vector3 direction)
{
	direction.normalise();

	m_velocity = direction * 44.2;

	//if moving vertically...
	if(direction == Ogre::Vector3::UNIT_Y)
	{
		//...only gravity affects us.
		m_accel = Ogre::Vector3(0, -9.81, 0);
	}
	//if moving horizontally...
	else
	{	//...friction affects us.
		m_accel = coefficientOfFriction * 9.81 * m_velocity;
	}

	setMove(true);
}

Ogre::Vector3 PhysicsObject::getPosition()
{
	return m_position;
}

Ogre::Vector3 PhysicsObject::getVelocity()
{
	return m_velocity;
}

Ogre::Vector3 PhysicsObject::getAccel()
{
	return m_accel;
}

Ogre::Vector3 PhysicsObject::getMaxDisplacement()
{
	return m_maxDisplacement;
}

//Ogre::SceneNode* getNode()
//{
//	return m_objectNode;
//}

double PhysicsObject::getRadius()
{
	return m_radius;
}

bool PhysicsObject::getMove()
{
	return m_move;
}

float PhysicsObject::getTimeMoving()
{
	return m_timeMoving;
}

void PhysicsObject::setAccel(Ogre::Vector3 myAccel)
{
	m_accel = myAccel;
}

void PhysicsObject::setPosition(Ogre::Vector3 myPosition)
{
	m_position = myPosition;
}

void PhysicsObject::setVelocity(Ogre::Vector3 myVelocity)
{
	m_velocity = myVelocity;
}

void PhysicsObject::setMove(bool myMove)
{
	m_move = myMove;
	m_position.y = m_radius;
}

