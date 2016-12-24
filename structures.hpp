#pragma once

//#include <SFML/Window.hpp>
#include "constants.hpp"
#include <SFML/Graphics.hpp>

struct Ball
{
  sf::CircleShape shape;
  sf::Vector2f    velocity{-ballVelocity, -ballVelocity};

  Ball(float mX, float mY)
  {
    shape.setPosition(mX, mY);
    shape.setRadius(ballRadius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(ballRadius, ballRadius);
  }

  void checkBoundaries()
  {
    if(left() < 0) velocity.x = ballVelocity;
    else if(right() > windowWidth) velocity.x = -ballVelocity;

    else if(top() < 0) velocity.y = ballVelocity;
    else if(bottom() > windowHeight) velocity.y = -ballVelocity;
  }

  void update()
  {
    shape.move(velocity);
    checkBoundaries();
  }

  // "property" methods
  float x()       { return shape.getPosition().x; }
  float y()       { return shape.getPosition().y; }
  float left()    { return x() - shape.getRadius(); }
  float right()   { return x() + shape.getRadius(); }
  float top()     { return y() - shape.getRadius(); }
  float bottom()  { return y() + shape.getRadius(); }
};


struct Paddle
{
  sf::RectangleShape  shape;
  sf::Vector2f        velocity;

  Paddle(float mX, float mY)
  {
    shape.setPosition(mX, mY);
    shape.setSize({paddleWidth, paddleHeight});
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
  }

  void update()
  {
    shape.move(velocity);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
      velocity.x = -paddleVelocity;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < windowWidth)
      velocity.x = paddleVelocity;
    else
      velocity.x = 0;
  }

  // "property" methods
  float x()       { return shape.getPosition().x; }
  float y()       { return shape.getPosition().y; }
  float left()    { return x() - shape.getSize().x / 2.f; }
  float right()   { return x() + shape.getSize().x / 2.f; }
  float top()     { return y() - shape.getSize().y / 2.f; }
  float bottom()  { return y() + shape.getSize().y / 2.f; }
};

struct Brick
{
  sf::RectangleShape  shape;

  bool destroyed{false};

  Brick(float mX, float mY, sf::Color mColor)
  {
    shape.setPosition(mX, mY);
    shape.setSize({brickWidth, brickHeight});
    shape.setFillColor(mColor);
    shape.setOrigin(brickWidth / 2.f, brickHeight / 2.f);
  }

  void update()
  {

  }

  // "property" methods
  float x()       { return shape.getPosition().x; }
  float y()       { return shape.getPosition().y; }
  float left()    { return x() - shape.getSize().x / 2.f; }
  float right()   { return x() + shape.getSize().x / 2.f; }
  float top()     { return y() - shape.getSize().y / 2.f; }
  float bottom()  { return y() + shape.getSize().y / 2.f; }
};
