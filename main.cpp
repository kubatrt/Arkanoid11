#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "config.h"


const char * appName = "Arkanoid11";
constexpr int windowWidth{800}, windowHeight{600};

constexpr float ballRadius{10.0f}, ballVelocity{8.0f};
constexpr float paddleWidth{64.0f}, paddleHeight{24.0f}, paddleVelocity {6.0f};

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

int main()
{
  std::cout << appName << " Version " << Arkanoid11_VERSION_MAJOR << "." << Arkanoid11_VERSION_MINOR << std::endl;

  Ball ball{windowWidth / 2, windowHeight / 2};

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
    window.draw(ball.shape);
    window.display();
  }
  return 0;
}
