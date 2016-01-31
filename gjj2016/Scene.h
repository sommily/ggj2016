//
//  Scene.h
//  gjj2016
//
//  Created by baidu on 16/1/30.
//  Copyright © 2016年 fbee. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

class Scene {
public:
    virtual ~Scene() {}
    virtual void Update() = 0;
    virtual void Render() = 0;
};

#endif /* Scene_h */
