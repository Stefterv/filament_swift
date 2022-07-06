//
//  View.m
//  
//
//  Created by Stef Tervelde on 29.06.22.
//

#import "Bindings/Filament/View.h"
#import <filament/View.h>
#import <filament/Viewport.h>

@implementation View{
    filament::View* nativeView;
}

- (id) init:(void *)view{
    self->_view = view;
    self->nativeView = (filament::View*) view;
    return self;
}

- (NSString *)getName{
    return [[NSString alloc] initWithCString:nativeView->getName() encoding:NSASCIIStringEncoding];
}
- (void)setScene:(Scene *)scene{
    nativeView->setScene((filament::Scene*) scene.scene);
}
- (Scene *)getScene{
    return [[Scene alloc] init: nativeView->getScene()];
}
- (void)setCamera:(Camera *)camera{
    nativeView->setCamera((filament::Camera*) camera.camera);
}
- (Camera *)getCamera{
    return [[Camera alloc] init: &nativeView->getCamera()];
}
- (void)setViewport:(Viewport*)viewport{
    nativeView->setViewport(FILAMENT_VIEWPORT(viewport));
}
- (Viewport *)getViewport{
    auto vp1 = nativeView->getViewport();
    auto vp2 = [[Viewport alloc] init];
    vp2.left = vp1.left;
    vp2.bottom = vp1.bottom;
    vp2.width = vp2.width;
    vp2.height = vp2.height;
    return vp2;
}
- (void)setBlendMode:(BlendMode)blendmode{
    nativeView->setBlendMode((filament::View::BlendMode) blendmode);
}
- (BlendMode)getBlendMode{
    return (BlendMode) nativeView->getBlendMode();
    
}
- (void)setVisibleLayers:(uint8_t)select :(uint8_t)values{
    nativeView->setVisibleLayers(select, values);
}
- (void)setShadowingEnabled:(bool)enabled{
    nativeView->setShadowingEnabled(enabled);
}
- (bool)isShadowingEnabled{
    return nativeView->isShadowingEnabled();
}
- (void)setScreenSpaceRefractionEnabled:(bool)enabled{
    nativeView->setScreenSpaceRefractionEnabled(enabled);
}
- (bool)isScreenSpaceRefractionEnabled{
    return nativeView->isScreenSpaceRefractionEnabled();
}
- (void)setRenderTarget:(RenderTarget *)target{
    nativeView->setRenderTarget((filament::RenderTarget*) target.target);
}
- (RenderTarget *)getRenderTarget{
    return [[RenderTarget alloc] init: nativeView->getRenderTarget()];
}
- (void)setAntiAliasing:(AntiAliasing)type{
    nativeView->setAntiAliasing((filament::View::AntiAliasing) type);
}
- (AntiAliasing)getAntiAliasing{
    return (AntiAliasing) nativeView->getAntiAliasing();
}

@end
