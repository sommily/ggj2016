//
//  ActionCollector.cpp
//  gjj2016
//
//  Created by baidu on 16/1/30.
//  Copyright © 2016年 fbee. All rights reserved.
//

#include "ActionCollector.hpp"
#include <signal.h>
#include <cstdio>

ActionCollector::ActionCollector() {
    action_1 = false;
}

ActionCollector& ActionCollector::instance() {
    static ActionCollector ac;
    return ac;
}

bool ActionCollector::init() {
    struct sigaction new_action;
    new_action.sa_handler = usr1_action;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    
    sigaction(SIGUSR1, &new_action, nullptr);
    return true;
}

void ActionCollector::set_action_1() {
    action_1 = true;
}

bool ActionCollector::get_action_1() {
    bool result = action_1;
    action_1 = false;
    return result;
}

void ActionCollector::usr1_action(int) {
    ActionCollector::instance().set_action_1();
    fprintf(stderr, "test\n");
}