//
//  Animation.cpp
//  gjj2016
//
//  Created by baidu on 16/1/30.
//  Copyright © 2016年 fbee. All rights reserved.
//

#include "Animation.hpp"

Animation::Animation(int delay) {
    loop = true;
    _current_frame = 0;
    _delay = delay;
    _delay_cnt = _delay + 1;
}

void Animation::Update() {
    if (--_delay_cnt <= 0) {
        _delay_cnt = _delay;
        _current_frame += 1;
        
        if (_current_frame == _frames.size()) {
            if (loop) {
                _current_frame = 0;
            } else {
                _current_frame -= 1;
            }
        }
    }
}

void Animation::Render(int x, int y) {
    if (!_frames.empty()) {
        _frames[_current_frame].spr->setPosition(x, y);
        _frames[_current_frame].spr->move(_frames[_current_frame].dx, _frames[_current_frame].dy);
        window->draw(*_frames[_current_frame].spr);
    }
}