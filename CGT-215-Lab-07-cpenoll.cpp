// CGT-215-Lab-07-cpenoll.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(200, 200));
	ball.setRadius(20);
	ball.applyImpulse(Vector2f(0.5, 0)); //slower impulse start -- added so that the ball hits the obstacle twice somewhat quickly
	world.AddPhysicsBody(ball);

	PhysicsRectangle floor; //creates floor
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 600));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	PhysicsRectangle left_side; //creates left side wall
	left_side.setSize(Vector2f(20, 600));
	left_side.setCenter(Vector2f(0, 300));
	left_side.setStatic(true);
	world.AddPhysicsBody(left_side);

	PhysicsRectangle right_side; //creates right side wall
	right_side.setSize(Vector2f(20, 600));
	right_side.setCenter(Vector2f(800, 300));
	right_side.setStatic(true);
	world.AddPhysicsBody(right_side);

	PhysicsRectangle ceiling; //creates ceiling
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 0));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	//callback lambdas below (&thudCount) to create function that counts thuds each time ball hits a wall
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	left_side.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	right_side.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	//create middle obstacle in the center
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(100, 100));
	obstacle.setCenter(Vector2f(400, 300)); //setting it to the center of the box
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);

	//callback lambda function for bang (when ball hits center obstacle)
	int bang(0);
	obstacle.onCollision = [&bang, &window](PhysicsBodyCollisionResult result) {
		bang++;
		cout << "bang " << bang << endl;

		if (bang >= 3) { //condition to make program exit if obstacle hit 3 times
			exit(0); //using exit to close out/exit program once middle obstacle is hit thrice
		}
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		} 
		//these create/draw each on the screen
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(left_side);
		window.draw(right_side);
		window.draw(ceiling);
		window.draw(obstacle);
		window.display();
	}
}