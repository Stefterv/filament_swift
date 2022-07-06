//
//  SwapChain.mm
//  
//
//  Created by Stef Tervelde on 29.06.22.
//

#import "Bindings/Filament/SwapChain.h"
#import <filament/SwapChain.h>


@implementation SwapChain{
    filament::SwapChain* nativeSwapChain;
}

- (id) init:(void *)swapchain{
    self->_swapchain = swapchain;
    self->nativeSwapChain = (filament::SwapChain*) swapchain;
    return self;
}

@end

