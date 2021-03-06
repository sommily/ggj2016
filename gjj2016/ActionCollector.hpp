//
//  ActionCollector.hpp
//  gjj2016
//
//  Created by baidu on 16/1/30.
//  Copyright © 2016年 fbee. All rights reserved.
//

#ifndef ActionCollector_hpp
#define ActionCollector_hpp

class ActionCollector {
public:
    ActionCollector();
    
    static ActionCollector& instance();
    
    bool init();
    void set_action_1();
    bool get_action_1();
    void set_action_2();
    bool get_action_2();
private:
    static void usr1_action(int);
    bool action_1;
    static void usr2_action(int);
    bool action_2;
};

#endif /* ActionCollector_hpp */
