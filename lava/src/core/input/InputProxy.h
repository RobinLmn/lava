#pragma once
#import <GameController/GameController.h>
#include <functional>

@interface InputProxy : NSObject

- (void) initialize;
- (bool) isKeyPressed: (GCKeyCode) key;

@property std::function<void(float, float)> onMouseMove;
@property std::function<void(float, float)> onMouseScroll;

@end
