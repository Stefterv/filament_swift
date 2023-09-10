//
//  View.h
//
//  Created by Stef Tervelde on 29.06.22.
//
#import <Foundation/Foundation.h>
#import "Scene.h"
#import "Camera.h"
#import "Viewport.h"
#import "RenderTarget.h"

#ifndef View_h
#define View_h

typedef NS_ENUM(NSInteger, BlendMode) {
    BlendModeOpaque,
    BlendModeTranslucent,
};

typedef NS_ENUM(NSInteger, QualityLevel) {
    QualityLevelLow,
    QualityLevelMedium,
    QualityLevelHigh,
    QualityLevelUltra,
};

typedef NS_ENUM(NSInteger, AntiAliasing) {
    AntiAliasingNOAA,
    AntiAliasingFXAA
};

typedef struct{
    float lightConeRad;
    float shadowDistance;
    float contactDistanceMax;
    float intensity;
    simd_float3 lightDirection;
    float depthBias;
    float depthSlopeBias;
    uint8_t sampleCount;
    uint8_t rayCount;
    bool enabled;
} Ssct;

typedef struct{
    float radius;
    float power;
    float bias;
    float resolution ;
    float intensity;
    float bilateralThreshold ;
    QualityLevel quality;
    QualityLevel lowPassFilter;
    QualityLevel upsampling;
    bool enabled;
    bool bentNormals;
    float minHorizonAngleRad;
    Ssct ssct;
} AmbientOcclusionOptions;
NS_SWIFT_NAME(AmbientOcclusionOptions.Default)
const AmbientOcclusionOptions AmbientOcclusionOptionsDefault = {
    .radius=0.3f,                       //!< Ambient Occlusion radius in meters, between 0 and ~10.
    .power=1.0f,                        //!< Controls ambient occlusion's contrast. Must be positive.
    .bias=0.0005f,                      //!< Self-occlusion bias in meters. Use to avoid self-occlusion. Between 0 and a few mm.
    .resolution=0.5f,                   //!< How each dimension of the AO buffer is scaled. Must be either 0.5 or 1.0.
    .intensity=1.0f,                    //!< Strength of the Ambient Occlusion effect.
    .bilateralThreshold=0.05f,          //!< depth distance that constitute an edge for filtering
    .quality=QualityLevelLow,           //!< affects # of samples used for AO.
    .lowPassFilter=QualityLevelMedium,  //!< affects AO smoothness
    .upsampling=QualityLevelLow,        //!< affects AO buffer upsampling quality
    .enabled=false,                     //!< enables or disables screen-space ambient occlusion
    .bentNormals=false,                 //!< enables bent normals computation from AO, and specular AO
    .minHorizonAngleRad=0.0f,           //!< min angle in radian to consider
    .ssct={
        .lightConeRad = 1.0f,           //!< full cone angle in radian, between 0 and pi/2
        .shadowDistance = 0.3f,         //!< how far shadows can be cast
        .contactDistanceMax = 1.0f,     //!< max distance for contact
        .intensity = 0.8f,              //!< intensity
        .lightDirection ={ 0, -1, 0 },  //!< light direction
        .depthBias = 0.01f,             //!< depth bias in world units (mitigate self shadowing)
        .depthSlopeBias = 0.01f,        //!< depth slope bias (mitigate self shadowing)
        .sampleCount = 4,               //!< tracing sample count, between 1 and 255
        .rayCount = 1,                  //!< # of rays to trace, between 1 and 255
        .enabled = false                //!< enables or disables SSCT
    }
};

/**
 * Encompasses all the state needed for rendering a {@link Scene}.
 *
 * <p>
 * {@link Renderer#render} operates on <code>View</code> objects. These <code>View</code> objects
 * specify important parameters such as:
 * </p>
 *
 * <ul>
 * <li>The Scene</li>
 * <li>The Camera</li>
 * <li>The Viewport</li>
 * <li>Some rendering parameters</li>
 * </ul>
 *
 * <p>
 * <code>View</code> instances are heavy objects that internally cache a lot of data needed for
 * rendering. It is not advised for an application to use many View objects.
 * </p>
 *
 * <p>
 * For example, in a game, a <code>View</code> could be used for the main scene and another one for
 * the game's user interface. More <code>View</code> instances could be used for creating special
 * effects (e.g. a <code>View</code> is akin to a rendering pass).
 * </p>
 *
 * @see Renderer
 * @see Scene
 * @see Camera
 * @see RenderTarget
 */
@interface View : NSObject

@property (nonatomic, readonly, nonnull) void* view NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) view NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

- (nonnull NSString*) getName;

/**
 * Sets this View instance's Scene.
 *
 * <p>
 * This method associates the specified Scene with this View. Note that a particular scene can
 * be associated with several View instances. To remove an existing association, simply pass
 * null.
 * </p>
 *
 * <p>
 * The View does not take ownership of the Scene pointer. Before destroying a Scene, be sure
 * to remove it from all assoicated Views.
 * </p>
 *
 * @see #getScene
 */
- (void) setScene: (nullable Scene*) scene;
- (nullable Scene*) getScene;

/**
 * Sets this View's Camera.
 *
 * <p>
 * This method associates the specified Camera with this View. A Camera can be associated with
 * several View instances. To remove an existing association, simply pass
 * null.
 * </p>
 *
 * <p>
 * The View does not take ownership of the Scene pointer. Before destroying a Camera, be sure
 * to remove it from all assoicated Views.
 * </p>
 *
 * @see #getCamera
 */
- (void) setCamera: (nullable Camera*) camera;
- (nullable Camera*) getCamera;

/**
 * Specifies the rectangular rendering area.
 *
 * <p>
 * The viewport specifies where the content of the View (i.e. the Scene) is rendered in
 * the render target. The render target is automatically clipped to the Viewport.
 * </p>
 *
 * <p>
 * If you wish subsequent changes to take effect please call this method again in order to
 * propagate the changes down to the native layer.
 * </p>
 *
 * @param viewport  The Viewport to render the Scene into.
 */
- (void) setViewport: (nonnull Viewport*) viewport;
- (nonnull Viewport*) getViewport;

- (void) setBlendMode: (BlendMode) blendmode;
- (BlendMode) getBlendMode;

/**
 * Sets which layers are visible.
 *
 * <p>
 * Renderable objects can have one or several layers associated to them. Layers are
 * represented with an 8-bits bitmask, where each bit corresponds to a layer.
 * By default all layers are visible.
 * </p>
 *
 * @see RenderableManager#setLayerMask
 *
 * @param select    a bitmask specifying which layer to set or clear using <code>values</code>.
 * @param values    a bitmask where each bit sets the visibility of the corresponding layer
 *                  (1: visible, 0: invisible), only layers in <code>select</code> are affected.
 */
- (void) setVisibleLayers: (uint8_t) select :(uint8_t)values;
/**
 * Enables or disables shadow mapping. Enabled by default.
 *
 * @see LightManager.Builder#castShadows
 * @see RenderableManager.Builder#receiveShadows
 * @see RenderableManager.Builder#castShadows
 */
- (void) setShadowingEnabled: (bool) enabled;
- (bool) isShadowingEnabled;

- (void) setScreenSpaceRefractionEnabled: (bool) enabled;
- (bool) isScreenSpaceRefractionEnabled;

/**
 * Specifies an offscreen render target to render into.
 *
 * <p>
 * By default, the view's associated render target is null, which corresponds to the
 * SwapChain associated with the engine.
 * </p>
 *
 * <p>
 * A view with a custom render target cannot rely on Renderer.ClearOptions, which only applies
 * to the SwapChain. Such view can use a Skybox instead.
 * </p>
 *
 * @param target render target associated with view, or null for the swap chain
 */
- (void) setRenderTarget: (nullable RenderTarget*) target;
- (nullable RenderTarget*) getRenderTarget;

/**
 * Enables or disables anti-aliasing in the post-processing stage. Enabled by default.
 *
 * <p>
 * For MSAA anti-aliasing, see {@link #setSampleCount}.
 * </p>
 *
 * @param type FXAA for enabling, NONE for disabling anti-aliasing.
 */
- (void) setAntiAliasing: (AntiAliasing) type;
- (AntiAliasing) getAntiAliasing;
/**
 * Sets ambient occlusion options.
 *
 * @param options Options for ambient occlusion.
 */
- (void) setAmbientOcclusionOptions: (AmbientOcclusionOptions) options;
- (AmbientOcclusionOptions) getAmbientOcclusionOptions;


#warning Extend to most options
@end

#endif /* View_h */
