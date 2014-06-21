#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "config.h"


const char * appName = "Arkanoid11";

int main()
{
  std::cout << appName << " Version " << Arkanoid11_VERSION_MAJOR << "." << Arkanoid11_VERSION_MINOR << std::endl;

  sf::VideoMode vmode(800, 600);
  sf::RenderWindow window(vmode, appName);
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
    window.display();
  }
  return 0;
}
