//
//  MainGame.h
//  gjj2016
//
//  Created by baidu on 16/1/30.
//  Copyright © 2016年 fbee. All rights reserved.
//

#ifndef MainGame_h
#define MainGame_h
#include "common.h"
#include "Animation.hpp"

struct EventNode {
    int type;
    int proper_tick;
    
    EventNode() {
        type = 0;
        proper_tick = 0;
    }
    
    bool operator < (const EventNode& b) const {
        return proper_tick < b.proper_tick;
    }
};

class MainGame;
class EventList {
public:
    EventList(MainGame* game) {
        this->_game = game;
    }
    
    ~EventList();
    
    void add_event(const EventNode& event);
    void prepare();
    
    void Update();
    void Render(int base_x, int base_y);
    
    void reset();
    
    bool done();
private:
    std::vector<EventNode> _events;
    int _tick;
    int _left_event;
    int _speed;
    
    std::map<int, Animation*> _ani;
    MainGame* _game;
};

class MainGame : public Scene
{
public:
    MainGame();
    ~MainGame();
    
    void Init(int stage);
    
    void Update() override;
    void Render() override;
    
private:
    bool LoadStage(const char* filename);
    
    void SetupStage1();
    
private:
    int _current_tick;
    EventList _event_list;
    Animation _boss;
    sf::Sprite _bg;
    
    Animation _curtain_left;
    Animation _curtain_right;
    int _curtain_time_open;
    int _curtain_time_closed;
    int _mode;
};

#endif /* MainGame_h */
