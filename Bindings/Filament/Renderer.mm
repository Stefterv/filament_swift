//
//  Renderer.mm
//  
//
//  Created by Stef Tervelde on 29.06.22.
//

#import "Bindings/Filament/Renderer.h"
#import <backend/PixelBufferDescriptor.h>
#import <filament/Renderer.h>
#import <filament/Texture.h>
#import <filament/Viewport.h>
#import "../Math.h"

@implementation ClearOptions

@end

@implementation DisplayInfo


@end

@implementation FrameRateOptions


@end

@implementation Renderer{
    filament::Renderer* nativeRenderer;
}

- (id) init:(void *)renderer{
    self->_renderer = renderer;
    self->nativeRenderer = (filament::Renderer*) renderer;
    return self;
}

- (void)setDisplayInfo:(DisplayInfo *) displayInfo{
    auto info = filament::Renderer::DisplayInfo();
    info.refreshRate = displayInfo.refreshRate;
    nativeRenderer->setDisplayInfo(info);
}
- (void)setFrameRateOptions:(FrameRateOptions *)options{
    auto info = filament::Renderer::FrameRateOptions();
    info.interval = options.interval;
    info.headRoomRatio = options.headRoomRatio;
    info.history = options.history;
    info.scaleRate = options.scaleRate;
    nativeRenderer->setFrameRateOptions(info);
}
- (void)setClearOptions:(ClearOptions *)info{
    auto options = filament::Renderer::ClearOptions();
    options.clear = info.clear;
    auto color = info.clearColor;
    options.clearColor = filament::math::float4(color.red, color.green, color.blue, color.alpha);
    options.discard = info.discard;
    nativeRenderer->setClearOptions(options);
}
- (void)setPresentationTime:(long)monotonicClockNanos{
    nativeRenderer->setPresentationTime(monotonicClockNanos);
}
- (bool)beginFrame:(SwapChain *)swapChain{
    return nativeRenderer->beginFrame( (filament::SwapChain*) swapChain.swapchain);
}
- (void)endFrame{
    nativeRenderer->endFrame();
}
- (void)render:(View *)view{
    nativeRenderer->render( (filament::View*) view.view);
}
- (void)renderStandaloneView:(View *)view{
    nativeRenderer->renderStandaloneView( (filament::View*) view.view);
}
- (void)copyFrame:(SwapChain *)dstSwapChain :(Viewport *)dstViewport :(Viewport *)srcViewport :(int)flags{
    nativeRenderer->copyFrame( (filament::SwapChain*) dstSwapChain.swapchain, FILAMENT_VIEWPORT(dstViewport), FILAMENT_VIEWPORT(srcViewport));
}
- (void)readPixels:(int)xoffset :(int)yoffset :(int)width :(int)height :(NSData *)buffer{
#warning Return Pixel data
//    nativeRenderer->readPixels(<#uint32_t xoffset#>, <#uint32_t yoffset#>, <#uint32_t width#>, <#uint32_t height#>, <#backend::PixelBufferDescriptor &&buffer#>)
}
- (void)readPixels:(RenderTarget *)target :(int)xoffset :(int)yoffset :(int)width :(int)height :(NSData *)buffer{
    
}

- (double)getUserTime{
    return nativeRenderer->getUserTime();
}
- (void)resetUserTime{
    nativeRenderer->resetUserTime();
}

@end
