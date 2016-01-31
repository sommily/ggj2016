//
//  Animation.hpp
//  gjj2016
//
//  Created by baidu on 16/1/30.
//  Copyright © 2016年 fbee. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include "Common.h"

class Animation
{
public:
    explicit Animation(int delay = 0);
    
    void AddSprite(shared_ptr<sf::Sprite> sprite, int dx = 0, int dy = 0) {
        _frames.push_back(Frame(sprite, dx, dy));
    }
    
    void Update(); // goto next frame
    void Render(int x, int y);
    
    void reverse() {
        std::reverse(_frames.begin(), _frames.end());
    }
    
    void set_frame(int frame) {
        _current_frame = frame;
        _delay_cnt = _delay;
    }
    
    bool loop; // set loop
private:
    
    struct Frame {
        Frame(shared_ptr<sf::Sprite> a, int b, int c) : spr(a), dx(b), dy(c) {}
        shared_ptr<sf::Sprite> spr;
        int dx;
        int dy;
    };
    std::vector<Frame> _frames;
    int _current_frame;
    int _delay;
    int _delay_cnt;
};

#endif /* Animation_hpp */
