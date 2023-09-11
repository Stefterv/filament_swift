//
//  SwapChain.mm
//  
//
//  Created by Stef Tervelde on 29.06.22.
//

#import "Bindings/Filament/SwapChain.h"
#import "Bindings/Filament/Engine.h"
#import <filament/SwapChain.h>


@implementation SwapChain{
    filament::SwapChain* nativeSwapChain;
}

- (id) init:(void *)swapchain{
    self->_swapchain = swapchain;
    self->nativeSwapChain = (filament::SwapChain*) swapchain;
    return self;
}

+ (bool)isSRGBSwapChainSupported:(nonnull Engine *)engine {
    return filament::SwapChain::isSRGBSwapChainSupported(*(filament::Engine*) engine.engine);
}

- (nonnull void *)getNativeWindow {
    return nativeSwapChain->getNativeWindow();
}

@end

