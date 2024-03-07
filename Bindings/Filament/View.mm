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

- (void)setAmbientOcclusionOptions:(AmbientOcclusionOptions)options{
    nativeView->setAmbientOcclusionOptions({
        .radius=options.radius,
        .power=options.power,
        .bias=options.bias,
        .resolution=options.resolution,
        .intensity=options.intensity,
        .bilateralThreshold=options.bilateralThreshold,
        .quality=(filament::QualityLevel)options.quality,
        .lowPassFilter=(filament::QualityLevel)options.lowPassFilter,
        .upsampling=(filament::QualityLevel)options.upsampling,
        .enabled=options.enabled,
        .bentNormals=options.bentNormals,
        .minHorizonAngleRad=options.minHorizonAngleRad,
        .ssct={
            .lightConeRad=options.ssct.lightConeRad,
            .shadowDistance=options.ssct.shadowDistance,
            .contactDistanceMax=options.ssct.contactDistanceMax,
            .intensity=options.ssct.intensity,
            .lightDirection=*(filament::math::float3*)&options.ssct.lightDirection,
            .depthBias=options.ssct.depthBias,
            .depthSlopeBias=options.ssct.depthSlopeBias,
            .sampleCount=options.ssct.sampleCount,
            .rayCount=options.ssct.rayCount,
            .enabled=options.ssct.enabled
        }
    });
}
- (AmbientOcclusionOptions)getAmbientOcclusionOptions{
    auto options = nativeView->getAmbientOcclusionOptions();
    return {
        .radius=options.radius,
        .power=options.power,
        .bias=options.bias,
        .resolution=options.resolution,
        .intensity=options.intensity,
        .bilateralThreshold=options.bilateralThreshold,
        .quality=(QualityLevel)options.quality,
        .lowPassFilter=(QualityLevel)options.lowPassFilter,
        .upsampling=(QualityLevel)options.upsampling,
        .enabled=options.enabled,
        .bentNormals=options.bentNormals,
        .minHorizonAngleRad=options.minHorizonAngleRad,
        .ssct={
            .lightConeRad=options.ssct.lightConeRad,
            .shadowDistance=options.ssct.shadowDistance,
            .contactDistanceMax=options.ssct.contactDistanceMax,
            .intensity=options.ssct.intensity,
            .lightDirection=*(simd_float3*)&options.ssct.lightDirection,
            .depthBias=options.ssct.depthBias,
            .depthSlopeBias=options.ssct.depthSlopeBias,
            .sampleCount=options.ssct.sampleCount,
            .rayCount=options.ssct.rayCount,
            .enabled=options.ssct.enabled
        }
    };
}

- (GuardBandOptions)getGuardBandOptions {
    auto options = nativeView->getGuardBandOptions();
    auto res = GuardBandOptions();
    res.enabled = options.enabled;
    return res;
}

- (simd_float4)getMaterialGlobal:(uint32_t)index {
    auto vector = nativeView->getMaterialGlobal(index);
    return simd_make_float4(vector[0], vector[1], vector[2], vector[3]);
}

- (MultiSampleAntiAliasingOptions)getMultiSampleAntiAliasingOptions {
    auto options = nativeView->getMultiSampleAntiAliasingOptions();
    auto res = MultiSampleAntiAliasingOptions();
    res.enabled = options.enabled;
    res.sampleCount = options.sampleCount;
    res.customResolve = options.customResolve;
    return res;
}

- (RenderQuality)getRenderQuality {
    auto options = nativeView->getRenderQuality();
    auto res = RenderQuality();
    res.hdrColorBuffer = (QualityLevel)options.hdrColorBuffer;
    return res;
    
}

- (BloomOptions)getBloomOptions {
    auto options = nativeView->getBloomOptions();
    auto res = BloomOptions();
    res.dirt = [[Texture alloc] init:options.dirt];
    res.dirtStrength = options.dirtStrength;
    res.strength = options.strength;
    res.resolution = options.resolution;
    res.levels = options.levels;
    res.blendMode = (BlendMode)options.blendMode;
    res.threshold = options.threshold;
    res.enabled = options.enabled;
    res.highlight = options.highlight;

    res.lensFlare = options.lensFlare;
    res.starburst = options.starburst;
    res.chromaticAberration = options.chromaticAberration;
    res.ghostCount = options.ghostCount;
    res.ghostSpacing = options.ghostSpacing;
    res.ghostThreshold = options.ghostThreshold;
    res.haloThickness = options.haloThickness;
    res.haloRadius = options.haloRadius;
    res.haloThreshold = options.haloThreshold;
    return res;
}

- (nonnull ColorGrading *)getColorGrading {
    return [[ColorGrading alloc] init:(void*)nativeView->getColorGrading()];
}

- (DepthOfFieldOptions)getDepthOfFieldOptions {
    auto options = nativeView->getDepthOfFieldOptions();
    auto res = DepthOfFieldOptions();
    res.enabled = options.enabled;
    res.cocScale = options.cocScale;
    res.maxApertureDiameter = options.maxApertureDiameter;
    res.enabled = options.enabled;
    res.filter = (Filter)options.filter;
    res.nativeResolution = options.nativeResolution;
    res.foregroundRingCount = options.foregroundRingCount;
    res.backgroundRingCount = options.backgroundRingCount;
    res.fastGatherRingCount = options.fastGatherRingCount;
    res.maxForegroundCOC = options.maxForegroundCOC;
    res.maxBackgroundCOC = options.maxBackgroundCOC;
    return res;
    
}

- (nonnull Camera *)getDirectionalShadowCamera {
    return [[Camera alloc] init:(void*)nativeView->getDirectionalShadowCamera()];
}

- (Dithering)getDithering {
    return (Dithering)nativeView->getDithering();
}

- (DynamicResolutionOptions)getDynamicResolutionOptions {
    auto options = nativeView->getDynamicResolutionOptions();
    auto res = DynamicResolutionOptions();
    res.minScale = simd_make_float2(options.minScale[0],options.minScale[1]);
    res.maxScale = simd_make_float2(options.maxScale[0],options.maxScale[1]);
    res.sharpness = options.sharpness;
    res.enabled = options.enabled;
    res.homogeneousScaling = options.homogeneousScaling;
    res.quality = (QualityLevel)options.quality;
    return res;
}

- (Entity)getFogEntity {
    return utils::Entity::smuggle(nativeView->getFogEntity());
}

- (FogOptions)getFogOptions {
    auto options = nativeView->getFogOptions();
    auto res = FogOptions();
    res.distance = options.distance;
    res.cutOffDistance = options.cutOffDistance;
    res.maximumOpacity = options.maximumOpacity;
    res.height = options.height;
    res.heightFalloff = options.heightFalloff;
    res.color = simd_make_float3(options.color[0], options.color[1], options.color[2]);
    res.density = options.density;
    res.inScatteringStart = options.inScatteringStart;
    res.inScatteringSize = options.inScatteringSize;
    res.fogColorFromIbl = options.fogColorFromIbl;
    res.skyColor = [[Texture alloc] init:(void*)options.skyColor];
    res.enabled = options.enabled;
    return res;
}

- (ScreenSpaceReflectionsOptions)getScreenSpaceReflectionsOptions {
    auto options = nativeView->getScreenSpaceReflectionsOptions();
    auto res = ScreenSpaceReflectionsOptions();
    res.thickness = options.thickness;
    res.bias = options.bias;
    res.maxDistance = options.maxDistance;
    res.stride = options.stride;
    res.enabled = options.enabled;
    return res;
}

- (SoftShadowOptions)getSoftShadowOptions {
    auto options = nativeView->getSoftShadowOptions();
    auto res = SoftShadowOptions();
    res.penumbraScale = options.penumbraScale;
    res.penumbraRatioScale = options.penumbraRatioScale;
    return res;
}

- (TemporalAntiAliasingOptions)getTemporalAntiAliasingOptions {
    auto options = nativeView->getTemporalAntiAliasingOptions();
    auto res = TemporalAntiAliasingOptions();
    res.enabled = options.enabled;
    res.feedback = options.feedback;
    res.filterWidth = options.filterWidth;
    return res;
}

- (uint8_t)getVisibleLayers {
    return nativeView->getVisibleLayers();
}

- (VsmShadowOptions)getVsmShadowOptions {
    auto options = nativeView->getVsmShadowOptions();
    auto res = VsmShadowOptions();
    res.anisotropy = options.anisotropy;
    res.mipmapping = options.mipmapping;
    res.msaaSamples = options.msaaSamples;
    res.highPrecision = options.highPrecision;
    res.minVarianceScale = options.minVarianceScale;
    res.lightBleedReduction = options.lightBleedReduction;
    return res;
}

- (bool)isFrontFaceWindingInverted {
    return nativeView->isFrontFaceWindingInverted();
}

- (bool)isFrustumCullingEnabled {
    return nativeView->isFrustumCullingEnabled();
}

- (bool)isPostProcessingEnabled {
    return nativeView->isPostProcessingEnabled();
}

- (bool)isStencilBufferEnabled {
    return nativeView->isStencilBufferEnabled();
}

- (void)setBloomOptions:(BloomOptions)options {
}

- (void)setColorGrading:(nonnull ColorGrading *)colorGrading {
    nativeView->setColorGrading((filament::ColorGrading*)colorGrading.grading);
}

- (void)setDebugCamera:(nonnull Camera *)camera {
    nativeView->setDebugCamera((filament::Camera*)camera.camera);
}

- (void)setDepthOfFieldOptions:(DepthOfFieldOptions)options {
}

- (VignetteOptions)getVignetteOptions {
    auto options = nativeView->getVignetteOptions();
    auto res = VignetteOptions();
    res.midPoint = options.midPoint;
    res.roundness = options.roundness;
    res.feather = options.feather;
    res.color = simd_make_float4(options.color[0], options.color[1], options.color[2], options.color[3]);
    res.enabled = options.enabled;
    return res;
    
}

- (void)setDithering:(Dithering)dithering {
    nativeView->setDithering((filament::Dithering)dithering);
}

- (void)setDynamicLightingOptions:(float)zLightNear :(float)zLightFar {
    nativeView->setDynamicLightingOptions(zLightNear, zLightFar);
}

- (void)setDynamicResolutionOptions:(DynamicResolutionOptions)options {
    auto res = filament::DynamicResolutionOptions();
    res.minScale = filament::math::float2(options.minScale[0],options.minScale[1]);
    res.maxScale = filament::math::float2(options.maxScale[0],options.maxScale[1]);
    res.sharpness = options.sharpness;
    res.enabled = options.enabled;
    res.homogeneousScaling = options.homogeneousScaling;
    res.quality = (filament::QualityLevel)options.quality;
    nativeView->setDynamicResolutionOptions(res);
}

- (void)setFogOptions:(FogOptions)options {
    auto res = filament::FogOptions();
    res.distance = options.distance;
    res.cutOffDistance = options.cutOffDistance;
    res.maximumOpacity = options.maximumOpacity;
    res.height = options.height;
    res.heightFalloff = options.heightFalloff;
    res.color = filament::math::float3(options.color[0], options.color[1], options.color[2]);
    res.density = options.density;
    res.inScatteringStart = options.inScatteringStart;
    res.inScatteringSize = options.inScatteringSize;
    res.fogColorFromIbl = options.fogColorFromIbl;
    res.skyColor = (filament::Texture*)options.skyColor.texture;
    res.enabled = options.enabled;
    nativeView->setFogOptions(res);
}

- (void)setFrontFaceWindingInverted:(bool)inverted {
    nativeView->setFrontFaceWindingInverted(inverted);
}

- (void)setFrustumCullingEnabled:(bool)culling {
    nativeView->setFrustumCullingEnabled(culling);
}

- (void)setGuardBandOptions:(GuardBandOptions)options {
    auto res = filament::GuardBandOptions();
    res.enabled = options.enabled;
    nativeView->setGuardBandOptions(res);
}

- (void)setLayerEnabled:(size_t)layer :(bool)enabled {
    nativeView->setLayerEnabled(layer, enabled);
}

- (void)setMaterialGlobal:(uint32_t)index :(simd_float4)value {
    nativeView->setMaterialGlobal(index, (filament::math::float4(value[0],value[1],value[2],value[3])));
}

- (void)setMultiSampleAntiAliasingOptions:(MultiSampleAntiAliasingOptions)options {
    auto res = filament::MultiSampleAntiAliasingOptions();
    res.enabled = options.enabled;
    res.sampleCount = options.sampleCount;
    res.customResolve = options.customResolve;
    nativeView->setMultiSampleAntiAliasingOptions(res);
}

- (void)setName:(nonnull NSString *)name {
    nativeView->setName(name.UTF8String);
}

- (void)setPostProcessingEnabled:(bool)enabled {
    nativeView->setPostProcessingEnabled(true);
}

- (void)setRenderQuality:(RenderQuality)renderQuality {
    auto res = filament::RenderQuality();
    res.hdrColorBuffer = (filament::QualityLevel)res.hdrColorBuffer;
    nativeView->setRenderQuality(res);
}

- (void)setScreenSpaceReflectionsOptions:(ScreenSpaceReflectionsOptions)options {
    auto res = filament::ScreenSpaceReflectionsOptions();
    res.thickness = options.thickness;
    res.bias = options.bias;
    res.maxDistance = options.maxDistance;
    res.stride = options.stride;
    res.enabled = options.enabled;
    nativeView->setScreenSpaceReflectionsOptions(res);
}

- (void)setShadowType:(ShadowType)shadow {
    nativeView->setShadowType((filament::ShadowType) shadow);
}

- (void)setSoftShadowOptions:(SoftShadowOptions)options {
    auto res = filament::SoftShadowOptions();
    res.penumbraScale = options.penumbraScale;
    res.penumbraRatioScale = options.penumbraRatioScale;
    nativeView->setSoftShadowOptions(res);
}

- (void)setStencilBufferEnabled:(bool)enabled {
    nativeView->setStencilBufferEnabled(enabled);
}

- (void)setTemporalAntiAliasingOptions:(TemporalAntiAliasingOptions)options {
    auto res = filament::TemporalAntiAliasingOptions();
    res.enabled = options.enabled;
    res.feedback = options.feedback;
    res.filterWidth = options.filterWidth;
    nativeView->setTemporalAntiAliasingOptions(res);
}

- (void)setVignetteOptions:(VignetteOptions)options {
    auto res = filament::VignetteOptions();
    res.midPoint = options.midPoint;
    res.roundness = options.roundness;
    res.feather = options.feather;
    res.color = filament::math::float4(options.color[0], options.color[1], options.color[2], options.color[3]);
    res.enabled = options.enabled;
    nativeView->setVignetteOptions(res);
}

- (void)setVsmShadowOptions:(VsmShadowOptions)options {
    auto res = filament::VsmShadowOptions();
    res.anisotropy = options.anisotropy;
    res.mipmapping = options.mipmapping;
    res.msaaSamples = options.msaaSamples;
    res.highPrecision = options.highPrecision;
    res.minVarianceScale = options.minVarianceScale;
    res.lightBleedReduction = options.lightBleedReduction;
    nativeView->setVsmShadowOptions(res);
}

@end
