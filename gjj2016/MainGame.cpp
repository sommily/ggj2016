//
//  MainGame.cpp
//  gjj2016
//  Created by baidu on 16/1/30.
//  Copyright © 2016年 fbee. All rights reserved.
//

#include "MainGame.h"
#include "ActionCollector.hpp"

EventList::~EventList()
{
    for (auto it : _ani) {
        delete it.second;
    }
}

void EventList::add_event(const EventNode &event) {
    _events.push_back(event);
}

void EventList::prepare() {
    reset();
    
    std::sort(_events.begin(), _events.end());
    
    // build type dict
    Animation * ani = new Animation;
    _ani[1] = ani;
    ani->AddSprite(make_shared<sf::Sprite>(tex::items[0]));
    ani = new Animation;
    _ani[2] = ani;
    ani->AddSprite(make_shared<sf::Sprite>(tex::items[1]));
}

void EventList::Update() {
    _tick += 1;
    if (_events.empty()) {
        return;
    }
    
    if (_left_event < _events.size() &&
        _events[_left_event].proper_tick + REMOVE_TICK < _tick ) {
        ++ _left_event;
        fprintf(stderr, "miss\n");
    }
    
    if (_left_event < _events.size()) {
        bool action_1 = ActionCollector::instance().get_action_1();
        
        if (action_1) {
            int diff = abs(_tick - _events[_left_event].proper_tick);
            if (diff < PERFECT_TICK) {
                ++ _left_event;
                fprintf(stderr, "Perfect\n");
            } else if (diff < REMOVE_TICK) {
                ++ _left_event;
                fprintf(stderr, "Good\n");
            }
        }
    }
    
}

bool EventList::done() {
    return _left_event >= _events.size();
}

void EventList::Render(int base_x, int base_y) {
    for (int i = _left_event; i < _events.size(); ++i) {
        int event_x = (_events[i].proper_tick - _tick) * _speed + base_x;
        if (event_x > W) {
            return;
        }
        
        auto it = _ani.find(_events[i].type);
        if (it == _ani.end()) {
            fprintf(stderr, "type mismatch: %d", _events[i].type);
        }
        
        it->second->Render(event_x, base_y);
    }
}

void EventList::reset() {
    _tick = 0;
    _left_event = 0;
    _speed = 8;
}

MainGame::MainGame()
 : _event_list(this), _boss(10),  _curtain_left(30), _curtain_right(30), _curtain_time_open(200) {
     _curtain_time_closed = _curtain_time_open;
}

MainGame::~MainGame() {
    
}

bool MainGame::LoadStage(const char* filename) {
    FILE * fp = fopen(filename, "r");
    char buf[1024];
    int type, period;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        type = 1;
        period = -100;
        sscanf(buf, "%d%d", &type, &period);
        if (period != -100) {
            EventNode event;
            event.type = type;
            event.proper_tick = period;
            _event_list.add_event(event);
        }
        
    }
    fclose(fp);
    
    _event_list.prepare();
}

void MainGame::Init(int stage) {
    if (stage == 1) {
        SetupStage1();
        LoadStage(get_name("1.txt").c_str());
    }
    
    _mode = 0;
    for (int i = 0; i <= 4; ++i) {
        auto spr = make_shared<sf::Sprite>(tex::curtain[4 - i]);
        _curtain_left.AddSprite(spr);
        
        spr = make_shared<sf::Sprite>(tex::curtain[4 - i]);
        spr->setTextureRect(sf::IntRect(W, 0, -W, H));
        _curtain_right.AddSprite(spr);
    }
    
    _curtain_left.loop = false;
    _curtain_right.loop = false;
}

void MainGame::Update() {
    if (_mode == 0) {
        _curtain_left.Update();
        _curtain_right.Update();
        if (--_curtain_time_open <= 0) {
            _mode = 1;
        }
    } else if (_mode == 1) {
        _event_list.Update();
        _boss.Update();
        
        if (_event_list.done()) {
            _mode = 2;
            _curtain_left.reverse();
            _curtain_right.reverse();
            _curtain_left.set_frame(0);
            _curtain_right.set_frame(0);
        }
    } else {
        _curtain_left.Update();
        _curtain_right.Update();
        if (--_curtain_time_closed <= 0) {
            // enter next scene
        }
    }
}

void MainGame::Render() {
    window->draw(_bg);
    
    _boss.Render(800, 380);
    _event_list.Render(330, 87);
    
    if (_mode == 0 || _mode == 2) {
        _curtain_left.Render(0, 0);
        _curtain_right.Render(0, 0);
    }
}

void MainGame::SetupStage1() {
    _bg.setTexture(tex::bg1);
    int boss_list[] = {2,2,2,3,3,3,3,2,2,2,2,3,3,3,3,2,2,2,2,1,1,1,1,1,2,2,2,2,3,3,3,3,2,2,2,2,3,3,3,3,2,2,2,2,1,1,1, -1};
    for (int i = 0; boss_list[i] != -1; ++i) {
        auto spr = make_shared<sf::Sprite>();
        spr->setTexture(tex::boss1[boss_list[i] - 1]);
        spr->setScale(0.5, 0.5);
        
        _boss.AddSprite(spr);
    }
}