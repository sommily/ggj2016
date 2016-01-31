
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include "Common.h"
#include "MainGame.h"
#include "ActionCollector.hpp"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

const char* title = "Title";

sf::RenderWindow *window;
shared_ptr<Scene> current_scene;

string get_name(const char* file) {
    return resourcePath() + string("/data/") + file;
}

namespace tex {
    sf::Texture bg1;
    sf::Texture boss1[3];
    sf::Texture items[2];
    sf::Texture curtain[5];
}

void init()
{
    window = new sf::RenderWindow(sf::VideoMode(W, H), title, sf::Style::Titlebar | sf::Style::Close);
    
    using namespace tex;
    bg1.loadFromFile(get_name("bg1.jpg"));
    boss1[0].loadFromFile(get_name("boss1-1.png"));
    boss1[1].loadFromFile(get_name("boss1-2.png"));
    boss1[2].loadFromFile(get_name("boss1-3.png"));
    items[0].loadFromFile(get_name("i1.png"));
    items[1].loadFromFile(get_name("i2.png"));
    
    for (int i = 0; i < 5; ++i) {
        char buf[32];
        snprintf(buf, sizeof(buf), "curtain/%d.png", i + 1);
        curtain[i].loadFromFile(get_name(buf));
    }
    auto main_game = make_shared<MainGame>();
    main_game->Init(1);
    current_scene = main_game;
    
}

int main(int, char const**)
{
    try {
        init();
        
        ActionCollector::instance().init();
        
        sf::Clock clock_;
        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
                else if (event.type == sf::Event::KeyPressed &&
                         event.key.code == sf::Keyboard::J) {
                    fprintf(stderr, "J\n");
                    ActionCollector::instance().set_action_1();
                }
            }
            
            if (clock_.getElapsedTime().asMicroseconds() < 16667) continue;
            
            clock_.restart();
            //expect = 33 - expect;
            current_scene->Update();
            
            window->clear();
            current_scene->Render();
            window->display();
        }
    }
    catch (std::exception& e) {
        printf("err: %s\n", e.what());
    }
    
    return 0;
    return EXIT_SUCCESS;
}
