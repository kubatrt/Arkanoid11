#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "structures.hpp"
#include "collision.hpp"

sf::Color brickColors[] {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};

int main()
{
  std::cout << appName << " Version " << Arkanoid11_VERSION_MAJOR << "." << Arkanoid11_VERSION_MINOR << std::endl;


  // game objects
  Ball ball{windowWidth / 2, windowHeight / 2};
  Paddle paddle{windowWidth / 2, windowHeight - paddleHeight * 2};
  std::vector<Brick> bricks;
  bricks.reserve(countBlocksX * countBlocksY);

  for(int ix{0}; ix < countBlocksX; ++ix)
    for(int iy{0}; iy < countBlocksY; ++iy)
      bricks.emplace_back( (ix + 1) * (brickWidth + 4) + 20,
                           (iy + 1) * (brickHeight + 4),
                           brickColors[iy / 2]);

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

    for(auto& brick : bricks) testCollision(brick, ball);


    // use STL algorithm to remove all destroyed bricks
    bricks.erase(std::remove_if(std::begin(bricks), std::end(bricks),
                 [](const Brick& mBrick) { return mBrick.destroyed; }),
                 std::end(bricks));

    
    bool won = true;
    for(auto& brick : bricks)
    {
        if(brick.destroyed == false)
           won = false;
    }
    if(won)
        window.close();

    // Draw
    window.draw(paddle.shape);
    window.draw(ball.shape);
    for(auto& brick : bricks)
        window.draw(brick.shape);

    window.display();
  }

  return 0;
}
