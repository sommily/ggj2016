//
//  Common.h
//  gjj2016
//
//  Created by baidu on 16/1/30.
//  Copyright © 2016年 fbee. All rights reserved.
//

#ifndef Common_h
#define Common_h

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

#include "Scene.h"

#include <memory>
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;

using std::string;

extern const char* title;
const int W = 1280;
const int H = 720;
const int w_rate = 2; // for mac high resolution
const int REMOVE_TICK = 15;
const int PERFECT_TICK = 5;

extern sf::RenderWindow *window;
extern shared_ptr<Scene> current_scene;

namespace tex {
    extern sf::Texture bg1;
    extern sf::Texture boss1[];
    extern sf::Texture items[];
    extern sf::Texture curtain[];
}

string get_name(const char* file);

inline float sqr(float x) { return x * x;  }

#endif /* Common_h */
