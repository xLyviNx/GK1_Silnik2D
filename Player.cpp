#include "Player.h"
#include "Calculations.h"
void Engine2D::Player::deleteMe()
{
	delete this;
}

Engine2D::Player::Player(string name, Vector2f position) : RectangleShape(name, position, 64, 64, Color::White, 2.0), ShapeObject(name, position), Collisions((TransformableObject*)this)
{
	movementSpeed = 5;
	enableGravity = true;
	isTopView = false;
	jumpForce = 10;
	gravityForce = 0;
	isGrounded = false;
	movement = Vector2f(0, 0);
}

void Engine2D::Player::Start()
{

}

void Engine2D::Player::Update(float deltaTime)
{
	Engine* engine = Engine::GetSingleton(false);
	if (engine)
	{
		Movement(engine, deltaTime);
	}
	//cout << "STAT: " << isGrounded << endl;
}

void Engine2D::Player::Movement(Engine* engine, float deltaTime)
{
	movement = Vector2f(0, 0);
	if (isTopView)
	{
		if (engine->isKeyTriggered(Keyboard::W))
		{
			movement.y -= 1;
		}
		if (engine->isKeyTriggered(Keyboard::S))
		{
			movement.y += 1;
		}
		if (engine->isKeyTriggered(Keyboard::A))
		{
			movement.x -= 1;
		}
		if (engine->isKeyTriggered(Keyboard::D))
		{
			movement.x += 1;
		}
		if (Calculations::Vector2f_Magnitude(movement) > 0.0)
		{
			Vector2f movementNorm = Calculations::Vector2f_Normalize(movement);
			Vector2f goalPosition = position+ (movementNorm * (float)(movementSpeed * 25.0) * deltaTime);
			this->Move(goalPosition, movement, NULL);
		}
	}
	else
	{
		std::set<Collisions*> ignore;
		ignore.insert((Collisions*)this);
		Vector2f bottomL = worldPosition() + Vector2f(0, bounds.y / 2.0) - Vector2f(worldBounds().x * 0.5f, 0);
		Vector2f bottomR = worldPosition() + Vector2f(0, bounds.y / 2.0) + Vector2f(worldBounds().x * 0.5f, 0);
		RaycastHit hitL = Collisions::Raycast(bottomL , bottomL + Vector2f(0, 1), ignore);
		RaycastHit hitR = Collisions::Raycast(bottomR, bottomR + Vector2f(0, 1), ignore);
		isGrounded = hitL.hit || hitR.hit;
		/*sf::CircleShape cs(5.0);
		sf::CircleShape cs2(5.0);
		cs.setPosition(hitL.point);
		cs2.setPosition(hitR.point);
		cs.setFillColor(hitL.hit ? Color::Red : Color::Green);
		cs2.setFillColor(hitR.hit ? Color::Red : Color::Green);
		renderWindow->draw(cs);
		renderWindow->draw(cs2);
		if (hitL.hit && hitL.collidedObject && hitL.collidedObject->myTransform) {
			//cout << "NAME: " << hit.collidedObject->myTransform->name << endl;
		}
		*/
		if ((isGrounded || !enableGravity) && gravityForce<=0)
			gravityForce = 0;
		else if (enableGravity && !isGrounded)
		{
			gravityForce -= Engine::Gravity * deltaTime * 100.0f;
		}
		if (engine->isKeyTriggered(Keyboard::A))
		{
			movement.x -= 1;
		}
		if (engine->isKeyTriggered(Keyboard::D))
		{
			movement.x += 1;
		}
		//cout << "GRAV: " << gravityForce << endl;
		if (Calculations::Vector2f_Magnitude(movement) > 0.0 || gravityForce != 0)
		{
			//cout << "??";
			Vector2f goalPosition = position + (movement * (float)(movementSpeed * 25.0) * deltaTime);
			this->Move(goalPosition, movement, NULL);
			Vector2f gravpos = this->worldPosition() - Vector2f(0, gravityForce) * deltaTime;
			this->Move(gravpos, movement,NULL);
		}
	}
}

void Engine2D::Player::KeyPressed(sf::Keyboard::Key keyPressed)
{
	if (keyPressed == Keyboard::Space)
	{
		if (!isTopView && ((isGrounded && jumpForce >= 0) || canJumpMidAir) && !jumped)
		{
			if (canJumpMidAir && jumpForce < 0)
				jumpForce = 0;
			if (gravityForce <= (jumpForce * 20))
			{
				gravityForce += jumpForce * 50;
				jumped = true;
			}
		}
	}
}
void Engine2D::Player::KeyReleased(sf::Keyboard::Key keyReleased)
{
	if (keyReleased == Keyboard::Space && jumped)
	{
		jumped = false;
	}
}

void Engine2D::Player::OnCollisionEnter(Collisions* col)
{
	if (gravityForce > 0)
		gravityForce = 0;
}

void Engine2D::Player::OnCollisionStay(Collisions* col)
{
	/*Engine::PrintLog("ENTER COLLISION");
	sf::CircleShape cs(5);
	cs.setPosition(col->myTransform->worldPosition());
	cs.setFillColor(Color::Cyan);
	renderWindow->draw(cs);*/
}

void Engine2D::Player::OnCollisionExit(Collisions* col)
{
	if (gravityForce < 0 && !isGrounded)
		gravityForce = -10;
}


void Engine2D::Player::Move(Vector2f position, Vector2f dir, bool* collided)
{
	this->Move(position, dir, collided, true);
}
void Engine2D::Player::Move(Vector2f position, Vector2f dir, bool* collided, bool collisionsMoveOut)
{
	set<Collisions*>ignores;
	ignores.insert((Collisions*)this);
	/*Vector2f normalizedDirection = dir;
	sf::CircleShape cs1(3.0);

	cs1.setPosition(worldPosition());
	renderWindow->draw(cs1);
	float diagonal = sqrt(pow(getGlobalBounds().width, 2) + pow(getGlobalBounds().height, 2));
	diagonal /= 2.0;
	Vector2f startPos = worldPosition() + Vector2f(getGlobalBounds().width/2.0 * normalizedDirection.x, getGlobalBounds().height/2.0 * normalizedDirection.y);


	sf::CircleShape cs(3.0);
	renderWindow->draw(cs);
	
	cs.setPosition(position);

	position = Vector2f(raycast.pointBefore.x, raycast.pointBefore.y);
	if (raycast.hit)
	{
		//Engine2D::Shapes::CircleShape* ns = new Shapes::CircleShape(position, 3, 1, Color::Transparent, Color::Red);
	}*/
	Vector2f xPos(position.x, worldPosition().y);
	Vector2f yPos(worldPosition().x, position.y);
	RaycastHit raycastX = Collisions::RaycastBox((Collisions*)this, worldPosition(), xPos, ignores);
	bool furtherX = false;
	bool furtherY = false;
	/*if (raycastX.hit)
	{
		sf::CircleShape cs(5);
		cs.setFillColor(Color::Red);
		cs.setPosition(raycastX.point);
		renderWindow->draw(cs);
	}*/
	RaycastHit raycastY = Collisions::RaycastBox((Collisions*)this, worldPosition(), yPos, ignores);
	if (raycastY.collidedObject && raycastY.collidedObject->myTransform)
	{
		float normalDist = Calculations::Vector2f_Magnitude(worldPosition() - raycastY.collidedObject->myTransform->worldPosition());
		float goalDist = Calculations::Vector2f_Magnitude(position - raycastY.collidedObject->myTransform->worldPosition());
		furtherY = goalDist > normalDist;
	}
	if (raycastX.collidedObject && raycastX.collidedObject->myTransform)
	{
		float normalDist = Calculations::Vector2f_Magnitude(worldPosition() - raycastX.collidedObject->myTransform->worldPosition());
		float goalDist = Calculations::Vector2f_Magnitude(position - raycastX.collidedObject->myTransform->worldPosition());
		furtherX = goalDist > normalDist;
	}
	position = worldPosition();
	if (!raycastX.hit || furtherX)
		position.x = xPos.x;
	if (!raycastY.hit || furtherY)
		position.y = yPos.y;
	setPosition(position);
	//printCorners(this->myCorners);
}

void Engine2D::Player::Draw()
{
	Shapes::RectangleShape::Draw();
}
