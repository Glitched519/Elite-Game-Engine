#include "PhysicsSystem.h"
#include "Engine.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "SFML/Graphics.hpp"

PhysicsSystem::PhysicsSystem()
{
	_gravity = b2Vec2(0.0f, 0);
	_world = new b2World(_gravity);
	componentMask = Position::getMask() || Rigidbody::getMask();
	_lasWorldStepTime = system_clock::now();
	timeStep = 1.0f / 60.f;
	positionIterations = 3;
	velocityIterations = 8;
}


PhysicsSystem::~PhysicsSystem()
{
	delete _world;
}

void PhysicsSystem::update(void) {

	float physicsscale = Engine::getInstance().physicsScale;

	duration<float> delta = system_clock::now() - _lasWorldStepTime;
	if (delta.count() > timeStep) {
		_lasWorldStepTime = system_clock::now();
		_world->Step(timeStep, velocityIterations, positionIterations);
	}
	
	for (Entities& entity : Entities::getEntityList()) {
		if ((entity.getComponentMask() & Position::getMask()) == Position::getMask()) {
			Position& position = entity.getComponent< Position >();      

			// CircleCollider
			if ((entity.getComponentMask() & CircleCollider::getMask()) == CircleCollider::getMask()) {
				if (_bodies.count(entity.getID()) < 1) {
					b2Body* body = createBody(entity.getID(), position, physicsscale);
					body->SetType(b2BodyType::b2_staticBody);
				}
				b2Body* body = _bodies[entity.getID()];
				//Check if the body has a collider shape (fixture)       
				if (body->GetFixtureList() == nullptr) {
					b2CircleShape shape = b2CircleShape();
					
					CircleCollider& collider = entity.getComponent< CircleCollider >();
					shape.m_radius = collider.radius / physicsscale;
					body->CreateFixture(&shape, collider.mass);
				}
			}

			// RectangleCollider
			if ((entity.getComponentMask() & RectangleCollider::getMask()) == RectangleCollider::getMask()) {
				if (_bodies.count(entity.getID()) < 1) {
					if ((entity.getComponentMask() & Sprite::getMask()) == Sprite::getMask()) {
						Sprite& sp = entity.getComponent<Sprite>();
						if (!sp.isOriginCenter) {
							position.X += sp.width / 2;
							position.Y += sp.height / 2;
						}
					}
					b2Body* body = createBody(entity.getID(), position, physicsscale);
					body->SetType(b2BodyType::b2_staticBody);
				}
				b2Body* body = _bodies[entity.getID()];
				//Check if the body has a collider shape (fixture)       
				if (body->GetFixtureList() == nullptr) {
					b2PolygonShape shape = b2PolygonShape();
					RectangleCollider& collider = entity.getComponent< RectangleCollider >();
					shape.SetAsBox(collider.width / 2.0f / physicsscale, collider.height / 2.0f / physicsscale);
					body->CreateFixture(&shape, 1.0f);
				}
			}

			//Rigidbody            
			if( ( entity.getComponentMask() & Rigidbody::getMask() ) == Rigidbody::getMask() ) {
				if( _bodies.count( entity.getID() ) < 1 ) {
					if ((entity.getComponentMask() & Sprite::getMask()) == Sprite::getMask()) {
						Sprite& sp = entity.getComponent<Sprite>();
						if (!sp.isOriginCenter) {
							position.X += sp.width / 2;
							position.Y += sp.height / 2;
						}
					}
					b2Body* body = createBody( entity.getID(), position, physicsscale ); 
				}
				b2Body* body = _bodies[ entity.getID() ];    
				if( body->GetType() != b2BodyType::b2_dynamicBody) {
					body->SetType( b2BodyType::b2_dynamicBody );                
				}        
				// Apply Physics to object
				Rigidbody& rb = entity.getComponent<Rigidbody>();
				body->ApplyForce(b2Vec2(rb.xForce, rb.yForce),body->GetWorldCenter(),true);

				//Update the Position Component based on the Physics Engine    
				b2Vec2 bodyPos = _bodies[ entity.getID() ]->GetPosition();     
				position.X = bodyPos.x * physicsscale;         
				position.Y = bodyPos.y * physicsscale;        
				

				//Change rotation on object
				Sprite& sp = entity.getComponent<Sprite>();
				sp.sprite.setRotation(rb.rotationAngle);
				sp.sprite.getOrigin();
			}
		} 
	}
}

b2Body* PhysicsSystem::createBody(size_t entityID, Position& position, float physicsScale) {
	//Create a new b2Body    
	b2BodyDef bodyDef;    
	bodyDef.position.x = position.X / physicsScale;
	bodyDef.position.y = position.Y / physicsScale;       //Add the body to the Box2D world  
	b2Body* body = _world->CreateBody( &bodyDef );  
	_bodies[ entityID ] = body;  
	return body; } 

