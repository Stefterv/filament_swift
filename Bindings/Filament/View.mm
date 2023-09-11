//
//  View.m
//  
//
//  Created by Stef Tervelde on 29.06.22.
//

#import "Bindings/Filament/View.h"
#import <filament/View.h>
#import <filament/Viewport.h>
#import <simd/simd.h>

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
- (void)setViewport:(Viewport)viewport{
    nativeView->setViewport(filament::Viewport(viewport.left, viewport.bottom, viewport.width, viewport.height));
}
- (Viewport)getViewport{
    auto vp1 = nativeView->getViewport();
    auto vp2 = Viewport();
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

//- (void)setAmbientOcclusionOptions:(AmbientOcclusionOptions)options{
//    nativeView->setAmbientOcclusionOptions({
//        .radius=options.radius,
//        .power=options.power,
//        .bias=options.bias,
//        .resolution=options.resolution,
//        .intensity=options.intensity,
//        .bilateralThreshold=options.bilateralThreshold,
//        .quality=(filament::QualityLevel)options.quality,
//        .lowPassFilter=(filament::QualityLevel)options.lowPassFilter,
//        .upsampling=(filament::QualityLevel)options.upsampling,
//        .enabled=options.enabled,
//        .bentNormals=options.bentNormals,
//        .minHorizonAngleRad=options.minHorizonAngleRad,
//        .ssct={
//            .lightConeRad=options.ssct.lightConeRad,
//            .shadowDistance=options.ssct.shadowDistance,
//            .contactDistanceMax=options.ssct.contactDistanceMax,
//            .intensity=options.ssct.intensity,
//            .lightDirection=*(filament::math::float3*)&options.ssct.lightDirection,
//            .depthBias=options.ssct.depthBias,
//            .depthSlopeBias=options.ssct.depthSlopeBias,
//            .sampleCount=options.ssct.sampleCount,
//            .rayCount=options.ssct.rayCount,
//            .enabled=options.ssct.enabled
//        }
//    });
//}
//- (AmbientOcclusionOptions)getAmbientOcclusionOptions{
//    auto options = nativeView->getAmbientOcclusionOptions();
//    return {
//        .radius=options.radius,
//        .power=options.power,
//        .bias=options.bias,
//        .resolution=options.resolution,
//        .intensity=options.intensity,
//        .bilateralThreshold=options.bilateralThreshold,
//        .quality=(QualityLevel)options.quality,
//        .lowPassFilter=(QualityLevel)options.lowPassFilter,
//        .upsampling=(QualityLevel)options.upsampling,
//        .enabled=options.enabled,
//        .bentNormals=options.bentNormals,
//        .minHorizonAngleRad=options.minHorizonAngleRad,
//        .ssct={
//            .lightConeRad=options.ssct.lightConeRad,
//            .shadowDistance=options.ssct.shadowDistance,
//            .contactDistanceMax=options.ssct.contactDistanceMax,
//            .intensity=options.ssct.intensity,
//            .lightDirection=*(simd_float3*)&options.ssct.lightDirection,
//            .depthBias=options.ssct.depthBias,
//            .depthSlopeBias=options.ssct.depthSlopeBias,
//            .sampleCount=options.ssct.sampleCount,
//            .rayCount=options.ssct.rayCount,
//            .enabled=options.ssct.enabled
//        }
//    };
//}

@end
