#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "config.h"


const char * appName = "Arkanoid11";
constexpr int windowWidth{800}, windowHeight{600};

constexpr float ballRadius{10.0f}, ballVelocity{8.0f};
constexpr float paddleWidth{96.0f}, paddleHeight{24.0f}, paddleVelocity {6.0f};

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


template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
{
  return  mA.right() >= mB.left() && mA.left() <= mB.right()
       && mA.top() <= mB.bottom() && mA.bottom() >= mB.top();
}

void testCollision(Paddle& mPaddle, Ball& mBall)
{
  // if no collision get out from the function
  if(!isIntersecting(mPaddle, mBall)) return;

  mBall.velocity.y = -ballVelocity;

  // direct ball depends where's paddle was hit
  if(mBall.x() < mPaddle.x())
    mBall.velocity.x = -ballVelocity;
  else
    mBall.velocity.x = ballVelocity;
}


int main()
{
  std::cout << appName << " Version " << Arkanoid11_VERSION_MAJOR << "." << Arkanoid11_VERSION_MINOR << std::endl;


  // game objects
  Ball ball{windowWidth / 2, windowHeight / 2};
  Paddle paddle{windowWidth / 2, windowHeight - paddleHeight * 2};

  sf::VideoMode vmode(windowWidth, windowHeight);
  sf::RenderWindow window(vmode, appName);
  window.setFramerateLimit(60);

  while(window.isOpen())
  {
    window.clear();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        window.close();

    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
          window.close();
    }

    ball.update();
    paddle.update();
    testCollision(paddle, ball);

    window.draw(paddle.shape);
    window.draw(ball.shape);
    window.display();
  }
  return 0;
}
