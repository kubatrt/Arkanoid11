#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.h"

using namespace std;

const char* APP_NAME = "Arkanoid11";

int main()
{
  cout << APP_NAME << " Version " << Arkanoid11_VERSION_MAJOR << "." << Arkanoid11_VERSION_MINOR << endl;

  sf::VideoMode VMode(800, 600);
  sf::RenderWindow window(VMode, APP_NAME);
  while(window.isOpen())
  {
    window.clear();
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
