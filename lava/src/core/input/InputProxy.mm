#import "InputProxy.h"

@implementation InputProxy

- ( void ) initialize
{
    NSNotificationCenter * center = [NSNotificationCenter defaultCenter];
    
    [center addObserverForName: GCMouseDidConnectNotification
                                object: nil
                                queue: nil
                                usingBlock: ^(NSNotification * note) {
                                [self onMouseConnected];
                            }
    ];
    
    [center addObserverForName: GCKeyboardDidConnectNotification
                                object: nil
                                queue: nil
                                usingBlock: ^(NSNotification * note) {
                                [self onKeyboardConnected];
                            }
    ];
}

- (bool) isKeyPressed: (GCKeyCode) key
{
    auto keyboardInput = GCKeyboard.coalescedKeyboard.keyboardInput;
    auto button = [keyboardInput buttonForKeyCode: key];
    return button.pressed;
}

- (void) onMouseConnected
{
    auto mouseInput = GCMouse.current.mouseInput;

    mouseInput.mouseMovedHandler = ^(GCMouseInput* mouseInput, float deltaX, float deltaY)
    {
       self.onMouseMove(deltaX, deltaY);
    };
    
    mouseInput.scroll.valueChangedHandler = ^(GCControllerDirectionPad* cursor, float deltaX, float deltaY)
    {
        NSLog(@"dx : %f dy : %f", deltaX, deltaY);
        self.onMouseScroll(deltaX, deltaY);
    };
}

- (void) onKeyboardConnected
{
}

@end
