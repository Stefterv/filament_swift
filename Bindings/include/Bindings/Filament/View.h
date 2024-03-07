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
#import "ColorGrading.h"

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
/**
 * List of available post-processing dithering techniques.
 */
typedef NS_ENUM(NSInteger, Dithering){
    NoDithering,       //!< No dithering
    TemporalDithering    //!< Temporal dithering (default)
};
/**
 * List of available shadow mapping techniques.
 * @see setShadowType
 */
typedef NS_ENUM(NSInteger, ShadowType) {
    PCF,        //!< percentage-closer filtered shadows (default)
    VSM,        //!< variance shadows
    DPCF,       //!< PCF with contact hardening simulation
    PCSS        //!< PCF with soft shadows and contact hardening
};
/**
 * Options for Temporal Multi-Sample Anti-aliasing (MSAA)
 * @see setMultiSampleAntiAliasingOptions()
 */
typedef struct{
    bool enabled;           //!< enables or disables msaa

    /**
     * sampleCount number of samples to use for multi-sampled anti-aliasing.\n
     *              0: treated as 1
     *              1: no anti-aliasing
     *              n: sample count. Effective sample could be different depending on the
     *                 GPU capabilities.
     */
    uint8_t sampleCount;

    /**
     * custom resolve improves quality for HDR scenes, but may impact performance.
     */
    bool customResolve;
} MultiSampleAntiAliasingOptions;
/**
 * Options for Temporal Anti-aliasing (TAA)
 * @see setTemporalAntiAliasingOptions()
 */
typedef struct TemporalAntiAliasingOptions {
    float filterWidth;   //!< reconstruction filter width typically between 0 (sharper, aliased) and 1 (smoother)
    float feedback;     //!< history feedback, between 0 (maximum temporal AA) and 1 (no temporal AA).
    bool enabled;       //!< enables or disables temporal anti-aliasing
} TemporalAntiAliasingOptions;
/**
 * Options for Screen-space Reflections.
 * @see setScreenSpaceReflectionsOptions()
 */
typedef struct ScreenSpaceReflectionsOptions {
    float thickness;     //!< ray thickness, in world units
    float bias;         //!< bias, in world units, to prevent self-intersections
    float maxDistance;   //!< maximum distance, in world units, to raycast
    float stride;        //!< stride, in texels, for samples along the ray.
    bool enabled;
} ScreenSpaceReflectionsOptions;
/**
 * Options for the  screen-space guard band.
 * A guard band can be enabled to avoid some artifacts towards the edge of the screen when
 * using screen-space effects such as SSAO. Enabling the guard band reduces performance slightly.
 * Currently the guard band can only be enabled or disabled.
 */
typedef struct GuardBandOptions {
    bool enabled;
} GuardBandOptions;
/**
 * Screen Space Cone Tracing (SSCT) options
 * Ambient shadows from dominant light
 */
typedef struct Ssct{
    float lightConeRad;       //!< full cone angle in radian, between 0 and pi/2
    float shadowDistance;     //!< how far shadows can be cast
    float contactDistanceMax; //!< max distance for contact
    float intensity;          //!< intensity
    simd_float3 lightDirection;    //!< light direction
    float depthBias;         //!< depth bias in world units (mitigate self shadowing)
    float depthSlopeBias;    //!< depth slope bias (mitigate self shadowing)
    uint8_t sampleCount;         //!< tracing sample count, between 1 and 255
    uint8_t rayCount;            //!< # of rays to trace, between 1 and 255
    bool enabled;            //!< enables or disables SSCT
} Ssct;
typedef struct AmbientOcclusionOptions{
    float radius;    //!< Ambient Occlusion radius in meters, between 0 and ~10.
    float power;     //!< Controls ambient occlusion's contrast. Must be positive.
    float bias;   //!< Self-occlusion bias in meters. Use to avoid self-occlusion. Between 0 and a few mm.
    float resolution;//!< How each dimension of the AO buffer is scaled. Must be either 0.5 or 1.0.
    float intensity; //!< Strength of the Ambient Occlusion effect.
    float bilateralThreshold; //!< depth distance that constitute an edge for filtering
    QualityLevel quality; //!< affects # of samples used for AO.
    QualityLevel lowPassFilter; //!< affects AO smoothness
    QualityLevel upsampling; //!< affects AO buffer upsampling quality
    bool enabled;    //!< enables or disables screen-space ambient occlusion
    bool bentNormals; //!< enables bent normals computation from AO, and specular AO
    float minHorizonAngleRad;  //!< min angle in radian to consider
    Ssct ssct;
} AmbientOcclusionOptions;
/**
 * Options to control the bloom effect
 *
 * enabled:     Enable or disable the bloom post-processing effect. Disabled by default.
 *
 * levels:      Number of successive blurs to achieve the blur effect, the minimum is 3 and the
 *              maximum is 12. This value together with resolution influences the spread of the
 *              blur effect. This value can be silently reduced to accommodate the original
 *              image size.
 *
 * resolution:  Resolution of bloom's minor axis. The minimum value is 2^levels and the
 *              the maximum is lower of the original resolution and 4096. This parameter is
 *              silently clamped to the minimum and maximum.
 *              It is highly recommended that this value be smaller than the target resolution
 *              after dynamic resolution is applied (horizontally and vertically).
 *
 * strength:    how much of the bloom is added to the original image. Between 0 and 1.
 *
 * blendMode:   Whether the bloom effect is purely additive (false) or mixed with the original
 *              image (true).
 *
 * anamorphism: Bloom's aspect ratio (x/y), for artistic purposes.
 *
 * threshold:   When enabled, a threshold at 1.0 is applied on the source image, this is
 *              useful for artistic reasons and is usually needed when a dirt texture is used.
 *
 * dirt:        A dirt/scratch/smudges texture (that can be RGB), which gets added to the
 *              bloom effect. Smudges are visible where bloom occurs. Threshold must be
 *              enabled for the dirt effect to work properly.
 *
 * dirtStrength: Strength of the dirt texture.
 */
typedef struct BloomOptions {
    Texture*_Nullable dirt;                //!< user provided dirt texture %codegen_skip_json% %codegen_skip_javascript%
    float dirtStrength;              //!< strength of the dirt texture %codegen_skip_json% %codegen_skip_javascript%
    float strength;                 //!< bloom's strength between 0.0 and 1.0
    uint32_t resolution;              //!< resolution of vertical axis (2^levels to 2048)
    uint8_t levels;                     //!< number of blur levels (1 to 11)
    BlendMode blendMode;           //!< how the bloom effect is applied
    bool threshold;                  //!< whether to threshold the source
    bool enabled;                   //!< enable or disable bloom
    float highlight;              //!< limit highlights to this value before bloom [10, +inf]

    bool lensFlare;                 //!< enable screen-space lens flare
    bool starburst;                  //!< enable starburst effect on lens flare
    float chromaticAberration;     //!< amount of chromatic aberration
    uint8_t ghostCount;                 //!< number of flare "ghosts"
    float ghostSpacing;              //!< spacing of the ghost in screen units [0, 1[
    float ghostThreshold;           //!< hdr threshold for the ghosts
    float haloThickness;             //!< thickness of halo in vertical screen units, 0 to disable
    float haloRadius;                //!< radius of halo in vertical screen units [0, 0.5]
    float haloThreshold;            //!< hdr threshold for the halo
} BloomOptions;
/**
 * Options to control large-scale fog in the scene
 */
typedef struct FogOptions {
    /**
     * Distance in world units [m] from the camera to where the fog starts ( >= 0.0 )
     */
    float distance;

    /**
     * Distance in world units [m] after which the fog calculation is disabled.
     * This can be used to exclude the skybox, which is desirable if it already contains clouds or
     * fog. The default value is +infinity which applies the fog to everything.
     *
     * Note: The SkyBox is typically at a distance of 1e19 in world space (depending on the near
     * plane distance and projection used though).
     */
    float cutOffDistance;

    /**
     * fog's maximum opacity between 0 and 1
     */
    float maximumOpacity;

    /**
     * Fog's floor in world units [m]. This sets the "sea level".
     */
    float height;

    /**
     * How fast the fog dissipates with altitude. heightFalloff has a unit of [1/m].
     * It can be expressed as 1/H, where H is the altitude change in world units [m] that causes a
     * factor 2.78 (e) change in fog density.
     *
     * A falloff of 0 means the fog density is constant everywhere and may result is slightly
     * faster computations.
     */
    float heightFalloff;

    /**
     *  Fog's color is used for ambient light in-scattering, a good value is
     *  to use the average of the ambient light, possibly tinted towards blue
     *  for outdoors environments. Color component's values should be between 0 and 1, values
     *  above one are allowed but could create a non energy-conservative fog (this is dependant
     *  on the IBL's intensity as well).
     *
     *  We assume that our fog has no absorption and therefore all the light it scatters out
     *  becomes ambient light in-scattering and has lost all directionality, i.e.: scattering is
     *  isotropic. This somewhat simulates Rayleigh scattering.
     *
     *  This value is used as a tint instead, when fogColorFromIbl is enabled.
     *
     *  @see fogColorFromIbl
     */
    simd_float3 color;

    /**
     * Extinction factor in [1/m] at altitude 'height'. The extinction factor controls how much
     * light is absorbed and out-scattered per unit of distance. Each unit of extinction reduces
     * the incoming light to 37% of its original value.
     *
     * Note: The extinction factor is related to the fog density, it's usually some constant K times
     * the density at sea level (more specifically at fog height). The constant K depends on
     * the composition of the fog/atmosphere.
     *
     * For historical reason this parameter is called `density`.
     */
    float density;

    /**
     * Distance in world units [m] from the camera where the Sun in-scattering starts.
     */
    float inScatteringStart;

    /**
     * Very inaccurately simulates the Sun's in-scattering. That is, the light from the sun that
     * is scattered (by the fog) towards the camera.
     * Size of the Sun in-scattering (>0 to activate). Good values are >> 1 (e.g. ~10 - 100).
     * Smaller values result is a larger scattering size.
     */
    float inScatteringSize;

    /**
     * The fog color will be sampled from the IBL in the view direction and tinted by `color`.
     * Depending on the scene this can produce very convincing results.
     *
     * This simulates a more anisotropic phase-function.
     *
     * `fogColorFromIbl` is ignored when skyTexture is specified.
     *
     * @see skyColor
     */
    bool fogColorFromIbl;

    /**
     * skyTexture must be a mipmapped cubemap. When provided, the fog color will be sampled from
     * this texture, higher resolution mip levels will be used for objects at the far clip plane,
     * and lower resolution mip levels for objects closer to the camera. The skyTexture should
     * typically be heavily blurred; a typical way to produce this texture is to blur the base
     * level with a strong gaussian filter or even an irradiance filter and then generate mip
     * levels as usual. How blurred the base level is somewhat of an artistic decision.
     *
     * This simulates a more anisotropic phase-function.
     *
     * `fogColorFromIbl` is ignored when skyTexture is specified.
     *
     * @see Texture
     * @see fogColorFromIbl
     */
    Texture*_Nullable skyColor;    //!< %codegen_skip_json% %codegen_skip_javascript%

    /**
     * Enable or disable large-scale fog
     */
    bool enabled;
} FogOptions;
/**
 * Options to control Depth of Field (DoF) effect in the scene.
 *
 * cocScale can be used to set the depth of field blur independently from the camera
 * aperture, e.g. for artistic reasons. This can be achieved by setting:
 *      cocScale = cameraAperture / desiredDoFAperture
 *
 * @see Camera
 */

typedef NS_ENUM(NSInteger, Filter){
    NoFilter,
    Unused,
    Median
};
typedef struct DepthOfFieldOptions {
    float cocScale;              //!< circle of confusion scale factor (amount of blur)
    float maxApertureDiameter;  //!< maximum aperture diameter in meters (zero to disable rotation)
    bool enabled;               //!< enable or disable depth of field effect
    Filter filter;     //!< filter to use for filling gaps in the kernel
    bool nativeResolution;      //!< perform DoF processing at native resolution
    /**
     * Number of of rings used by the gather kernels. The number of rings affects quality
     * and performance. The actual number of sample per pixel is defined
     * as (ringCount * 2 - 1)^2. Here are a few commonly used values:
     *       3 rings :   25 ( 5x 5 grid)
     *       4 rings :   49 ( 7x 7 grid)
     *       5 rings :   81 ( 9x 9 grid)
     *      17 rings : 1089 (33x33 grid)
     *
     * With a maximum circle-of-confusion of 32, it is never necessary to use more than 17 rings.
     *
     * Usually all three settings below are set to the same value, however, it is often
     * acceptable to use a lower ring count for the "fast tiles", which improves performance.
     * Fast tiles are regions of the screen where every pixels have a similar
     * circle-of-confusion radius.
     *
     * A value of 0 means default, which is 5 on desktop and 3 on mobile.
     *
     * @{
     */
    uint8_t foregroundRingCount; //!< number of kernel rings for foreground tiles
    uint8_t backgroundRingCount; //!< number of kernel rings for background tiles
    uint8_t fastGatherRingCount; //!< number of kernel rings for fast tiles
    /** @}*/

    /**
     * maximum circle-of-confusion in pixels for the foreground, must be in [0, 32] range.
     * A value of 0 means default, which is 32 on desktop and 24 on mobile.
     */
    uint16_t maxForegroundCOC;

    /**
     * maximum circle-of-confusion in pixels for the background, must be in [0, 32] range.
     * A value of 0 means default, which is 32 on desktop and 24 on mobile.
     */
    uint16_t maxBackgroundCOC;
} DepthOfFieldOptions;
/**
 * Options to control the vignetting effect.
 */
typedef struct VignetteOptions {
    float midPoint;                      //!< high values restrict the vignette closer to the corners, between 0 and 1
    float roundness;                     //!< controls the shape of the vignette, from a rounded rectangle (0.0), to an oval (0.5), to a circle (1.0)
    float feather;                       //!< softening amount of the vignette effect, between 0 and 1
    simd_float4 color; //!< color of the vignette effect, alpha is currently ignored
    bool enabled;                       //!< enables or disables the vignette effect
} VignetteOptions;
/**
 * Dynamic resolution can be used to either reach a desired target frame rate
 * by lowering the resolution of a View, or to increase the quality when the
 * rendering is faster than the target frame rate.
 *
 * This structure can be used to specify the minimum scale factor used when
 * lowering the resolution of a View, and the maximum scale factor used when
 * increasing the resolution for higher quality rendering. The scale factors
 * can be controlled on each X and Y axis independently. By default, all scale
 * factors are set to 1.0.
 *
 * enabled:   enable or disables dynamic resolution on a View
 *
 * homogeneousScaling: by default the system scales the major axis first. Set this to true
 *                     to force homogeneous scaling.
 *
 * minScale:  the minimum scale in X and Y this View should use
 *
 * maxScale:  the maximum scale in X and Y this View should use
 *
 * quality:   upscaling quality.
 *            LOW: 1 bilinear tap, Medium: 4 bilinear taps, High: 9 bilinear taps (tent)
 *
 * \note
 * Dynamic resolution is only supported on platforms where the time to render
 * a frame can be measured accurately. Dynamic resolution is currently only
 * supported on Android.
 *
 * @see Renderer::FrameRateOptions
 *
 */
typedef struct DynamicResolutionOptions {
    simd_float2 minScale;           //!< minimum scale factors in x and y %codegen_java_float%
    simd_float2 maxScale;           //!< maximum scale factors in x and y %codegen_java_float%
    float sharpness;                         //!< sharpness when QualityLevel::MEDIUM or higher is used [0 (disabled), 1 (sharpest)]
    bool enabled;                           //!< enable or disable dynamic resolution
    bool homogeneousScaling;                //!< set to true to force homogeneous scaling

    /**
     * Upscaling quality
     * LOW:    bilinear filtered blit. Fastest, poor quality
     * MEDIUM: AMD FidelityFX FSR1 w/ mobile optimizations
     * HIGH:   AMD FidelityFX FSR1 w/ mobile optimizations
     * ULTRA:  AMD FidelityFX FSR1
     *      FSR1 require a well anti-aliased (MSAA or TAA), noise free scene.
     *
     * The default upscaling quality is set to LOW.
     */
    QualityLevel quality;
} DynamicResolutionOptions;
/**
 * Structure used to set the precision of the color buffer and related quality settings.
 *
 * @see setRenderQuality, getRenderQuality
 */
typedef struct RenderQuality {
    /**
     * Sets the quality of the HDR color buffer.
     *
     * A quality of HIGH or ULTRA means using an RGB16F or RGBA16F color buffer. This means
     * colors in the LDR range (0..1) have a 10 bit precision. A quality of LOW or MEDIUM means
     * using an R11G11B10F opaque color buffer or an RGBA16F transparent color buffer. With
     * R11G11B10F colors in the LDR range have a precision of either 6 bits (red and green
     * channels) or 5 bits (blue channel).
     */
    QualityLevel hdrColorBuffer;
} RenderQuality;
/**
 * View-level options for VSM Shadowing.
 * @see setVsmShadowOptions()
 * @warning This API is still experimental and subject to change.
 */
typedef struct VsmShadowOptions {
    /**
     * Sets the number of anisotropic samples to use when sampling a VSM shadow map. If greater
     * than 0, mipmaps will automatically be generated each frame for all lights.
     *
     * The number of anisotropic samples = 2 ^ vsmAnisotropy.
     */
    uint8_t anisotropy;

    /**
     * Whether to generate mipmaps for all VSM shadow maps.
     */
    bool mipmapping;

    /**
     * The number of MSAA samples to use when rendering VSM shadow maps.
     * Must be a power-of-two and greater than or equal to 1. A value of 1 effectively turns
     * off MSAA.
     * Higher values may not be available depending on the underlying hardware.
     */
    uint8_t msaaSamples;

    /**
     * Whether to use a 32-bits or 16-bits texture format for VSM shadow maps. 32-bits
     * precision is rarely needed, but it does reduces light leaks as well as "fading"
     * of the shadows in some situations. Setting highPrecision to true for a single
     * shadow map will double the memory usage of all shadow maps.
     */
    bool highPrecision;

    /**
     * VSM minimum variance scale, must be positive.
     */
    float minVarianceScale;

    /**
     * VSM light bleeding reduction amount, between 0 and 1.
     */
    float lightBleedReduction;
} VsmShadowOptions;
/**
 * View-level options for DPCF and PCSS Shadowing.
 * @see setSoftShadowOptions()
 * @warning This API is still experimental and subject to change.
 */
typedef struct SoftShadowOptions {
    /**
     * Globally scales the penumbra of all DPCF and PCSS shadows
     * Acceptable values are greater than 0
     */
    float penumbraScale;

    /**
     * Globally scales the computed penumbra ratio of all DPCF and PCSS shadows.
     * This effectively controls the strength of contact hardening effect and is useful for
     * artistic purposes. Higher values make the shadows become softer faster.
     * Acceptable values are equal to or greater than 1.
     */
    float penumbraRatioScale;
} SoftShadowOptions;

/**
 * Options for stereoscopic (multi-eye) rendering.
 */
typedef struct StereoscopicOptions {
    bool enabled;
} StereoscopicOptions;

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
/**
* Sets the View's name. Only useful for debugging.
* @param name Pointer to the View's name. The string is copied.
*/
- (void) setName: (nonnull NSString*) name;

/**
* Returns the View's name
*
* @return a pointer owned by the View instance to the View's name.
*
* @attention Do *not* free the pointer or modify its content.
*/
- (nonnull NSString*) getName;

/**
* Set this View instance's Scene.
*
* @param scene Associate the specified Scene to this View. A Scene can be associated to
*              several View instances.\n
*              \p scene can be nullptr to dissociate the currently set Scene
*              from this View.\n
*              The View doesn't take ownership of the Scene pointer (which
*              acts as a reference).
*
* @note
*  There is no reference-counting.
*  Make sure to dissociate a Scene from all Views before destroying it.
*/
- (void) setScene: (nullable Scene*) scene;

/**
* Returns the Scene currently associated with this View.
* @return A pointer to the Scene associated to this View. nullptr if no Scene is set.
*/
- (nullable Scene*) getScene;
/**
* Specifies an offscreen render target to render into.
*
* By default, the view's associated render target is nullptr, which corresponds to the
* SwapChain associated with the engine.
*
* A view with a custom render target cannot rely on Renderer::ClearOptions, which only apply
* to the SwapChain. Such view can use a Skybox instead.
*
* @param renderTarget Render target associated with view, or nullptr for the swap chain.
*/
- (void) setRenderTarget: (nullable RenderTarget*) renderTarget;

/**
* Gets the offscreen render target associated with this view.
*
* Returns nullptr if the render target is the swap chain (which is default).
*
* @see setRenderTarget
*/
- (nullable RenderTarget*) getRenderTarget;

/**
* Sets the rectangular region to render to.
*
* The viewport specifies where the content of the View (i.e. the Scene) is rendered in
* the render target. The Render target is automatically clipped to the Viewport.
*
* @param viewport  The Viewport to render the Scene into. The Viewport is a value-type, it is
*                  therefore copied. The parameter can be discarded after this call returns.
*/
- (void) setViewport: (Viewport) viewport;

/**
* Returns the rectangular region that gets rendered to.
* @return A constant reference to View's viewport.
*/
- (Viewport) getViewport;

/**
* Sets this View's Camera.
*
* @param camera    Associate the specified Camera to this View. A Camera can be associated to
*                  several View instances.\n
*                  \p camera can be nullptr to dissociate the currently set Camera from this
*                  View.\n
*                  The View doesn't take ownership of the Camera pointer (which
*                  acts as a reference).
*
* @note
*  There is no reference-counting.
*  Make sure to dissociate a Camera from all Views before destroying it.
*/
- (void) setCamera: (nullable Camera*) camera;

/**
* Returns the Camera currently associated with this View.
* @return A reference to the Camera associated to this View.
*/
- (nonnull Camera*) getCamera;

/**
* Sets the blending mode used to draw the view into the SwapChain.
*
* @param blendMode either BlendMode::OPAQUE or BlendMode::TRANSLUCENT
* @see getBlendMode
*/
- (void) setBlendMode: (BlendMode) blendMode;

/**
*
* @return blending mode set by setBlendMode
* @see setBlendMode
*/
- (BlendMode) getBlendMode;

/**
* Sets which layers are visible.
*
* Renderable objects can have one or several layers associated to them. Layers are
* represented with an 8-bits bitmask, where each bit corresponds to a layer.
*
* This call sets which of those layers are visible. Renderables in invisible layers won't be
* rendered.
*
* @param select    a bitmask specifying which layer to set or clear using \p values.
* @param values    a bitmask where each bit sets the visibility of the corresponding layer
*                  (1: visible, 0: invisible), only layers in \p select are affected.
*
* @see RenderableManager::setLayerMask().
*
* @note By default only layer 0 (bitmask 0x01) is visible.
* @note This is a convenient way to quickly show or hide sets of Renderable objects.
*/
- (void) setVisibleLayers: (uint8_t) select :(uint8_t) values;

/**
* Helper function to enable or disable a visibility layer.
* @param layer     layer between 0 and 7 to enable or disable
* @param enabled   true to enable the layer, false to disable it
* @see RenderableManager::setVisibleLayers()
*/
- (void) setLayerEnabled: (size_t) layer :(bool) enabled;

/**
* Get the visible layers.
*
* @see View::setVisibleLayers()
*/
- (uint8_t) getVisibleLayers;

/**
* Enables or disables shadow mapping. Enabled by default.
*
* @param enabled true enables shadow mapping, false disables it.
*
* @see LightManager::Builder::castShadows(),
*      RenderableManager::Builder::receiveShadows(),
*      RenderableManager::Builder::castShadows(),
*/
- (void) setShadowingEnabled: (bool) enabled;

/**
* @return whether shadowing is enabled
*/
- (bool) isShadowingEnabled;

/**
* Enables or disables screen space refraction. Enabled by default.
*
* @param enabled true enables screen space refraction, false disables it.
*/
- (void) setScreenSpaceRefractionEnabled: (bool) enabled;

/**
* @return whether screen space refraction is enabled
*/
- (bool) isScreenSpaceRefractionEnabled;

/**
* Enables or disables anti-aliasing in the post-processing stage. Enabled by default.
* MSAA can be enabled in addition, see setSampleCount().
*
* @param type FXAA for enabling, NONE for disabling anti-aliasing.
*
* @note For MSAA anti-aliasing, see setSamplerCount().
*
* @see setSampleCount
*/
- (void) setAntiAliasing: (AntiAliasing) type;

/**
* Queries whether anti-aliasing is enabled during the post-processing stage. To query
* whether MSAA is enabled, see getSampleCount().
*
* @return The post-processing anti-aliasing method.
*/
- (AntiAliasing) getAntiAliasing;

/**
* Enables or disable temporal anti-aliasing (TAA). Disabled by default.
*
* @param options temporal anti-aliasing options
*/
- (void) setTemporalAntiAliasingOptions: (TemporalAntiAliasingOptions) options;

/**
* Returns temporal anti-aliasing options.
*
* @return temporal anti-aliasing options
*/
- (TemporalAntiAliasingOptions) getTemporalAntiAliasingOptions;

/**
* Enables or disable screen-space reflections. Disabled by default.
*
* @param options screen-space reflections options
*/
- (void) setScreenSpaceReflectionsOptions: (ScreenSpaceReflectionsOptions) options;

/**
* Returns screen-space reflections options.
*
* @return screen-space reflections options
*/
- (ScreenSpaceReflectionsOptions) getScreenSpaceReflectionsOptions;

/**
* Enables or disable screen-space guard band. Disabled by default.
*
* @param options guard band options
*/
- (void) setGuardBandOptions: (GuardBandOptions) options;

/**
* Returns screen-space guard band options.
*
* @return guard band options
*/
- (GuardBandOptions) getGuardBandOptions;

/**
* Enables or disable multi-sample anti-aliasing (MSAA). Disabled by default.
*
* @param options multi-sample anti-aliasing options
*/
- (void) setMultiSampleAntiAliasingOptions: (MultiSampleAntiAliasingOptions) options;

/**
* Returns multi-sample anti-aliasing options.
*
* @return multi-sample anti-aliasing options
*/
- (MultiSampleAntiAliasingOptions) getMultiSampleAntiAliasingOptions;

/**
* Sets this View's color grading transforms.
*
* @param colorGrading Associate the specified ColorGrading to this View. A ColorGrading can be
*                     associated to several View instances.\n
*                     \p colorGrading can be nullptr to dissociate the currently set
*                     ColorGrading from this View. Doing so will revert to the use of the
*                     default color grading transforms.\n
*                     The View doesn't take ownership of the ColorGrading pointer (which
*                     acts as a reference).
*
* @note
*  There is no reference-counting.
*  Make sure to dissociate a ColorGrading from all Views before destroying it.
*/
- (void) setColorGrading: (nonnull ColorGrading*) colorGrading;

/**
* Returns the color grading transforms currently associated to this view.
* @return A pointer to the ColorGrading associated to this View.
*/
- (nonnull ColorGrading*) getColorGrading;

/**
* Sets ambient occlusion options.
*
* @param options Options for ambient occlusion.
*/
- (void) setAmbientOcclusionOptions: (AmbientOcclusionOptions) options;

/**
* Gets the ambient occlusion options.
*
* @return ambient occlusion options currently set.
*/
- (AmbientOcclusionOptions) getAmbientOcclusionOptions;

/**
* Enables or disables bloom in the post-processing stage. Disabled by default.
*
* @param options options
*/
- (void) setBloomOptions: (BloomOptions) options;

/**
* Queries the bloom options.
*
* @return the current bloom options for this view.
*/
- (BloomOptions) getBloomOptions;

/**
* Enables or disables fog. Disabled by default.
*
* @param options options
*/
- (void) setFogOptions: (FogOptions) options;

/**
* Queries the fog options.
*
* @return the current fog options for this view.
*/
- (FogOptions) getFogOptions;

/**
* Enables or disables Depth of Field. Disabled by default.
*
* @param options options
*/
- (void) setDepthOfFieldOptions: (DepthOfFieldOptions) options;

/**
* Queries the depth of field options.
*
* @return the current depth of field options for this view.
*/
- (DepthOfFieldOptions) getDepthOfFieldOptions;

/**
* Enables or disables the vignetted effect in the post-processing stage. Disabled by default.
*
* @param options options
*/
- (void) setVignetteOptions: (VignetteOptions) options;

/**
* Queries the vignette options.
*
* @return the current vignette options for this view.
*/
- (VignetteOptions) getVignetteOptions;

/**
* Enables or disables dithering in the post-processing stage. Enabled by default.
*
* @param dithering dithering type
*/
- (void) setDithering: (Dithering) dithering;

/**
* Queries whether dithering is enabled during the post-processing stage.
*
* @return the current dithering type for this view.
*/
- (Dithering) getDithering;

/**
* Sets the dynamic resolution options for this view. Dynamic resolution options
* controls whether dynamic resolution is enabled, and if it is, how it behaves.
*
* @param options The dynamic resolution options to use on this view
*/
- (void) setDynamicResolutionOptions: (DynamicResolutionOptions) options;

/**
* Returns the dynamic resolution options associated with this view.
* @return value set by setDynamicResolutionOptions().
*/
- (DynamicResolutionOptions) getDynamicResolutionOptions;

/**
* Sets the rendering quality for this view. Refer to RenderQuality for more
* information about the different settings available.
*
* @param renderQuality The render quality to use on this view
*/
- (void) setRenderQuality: (RenderQuality) renderQuality;

/**
* Returns the render quality used by this view.
* @return value set by setRenderQuality().
*/
- (RenderQuality) getRenderQuality;

/**
* Sets options relative to dynamic lighting for this view.
*
* @param zLightNear Distance from the camera where the lights are expected to shine.
*                   This parameter can affect performance and is useful because depending
*                   on the scene, lights that shine close to the camera may not be
*                   visible -- in this case, using a larger value can improve performance.
*                   e.g. when standing and looking straight, several meters of the ground
*                   isn't visible and if lights are expected to shine there, there is no
*                   point using a short zLightNear. (Default 5m).
*
* @param zLightFar Distance from the camera after which lights are not expected to be visible.
*                  Similarly to zLightNear, setting this value properly can improve
*                  performance. (Default 100m).
*
*
* Together zLightNear and zLightFar must be chosen so that the visible influence of lights
* is spread between these two values.
*
*/
- (void) setDynamicLightingOptions: (float) zLightNear :(float) zLightFar;

/*
* Set the shadow mapping technique this View uses.
*
* The ShadowType affects all the shadows seen within the View.
*
* ShadowType::VSM imposes a restriction on marking renderables as only shadow receivers (but
* not casters). To ensure correct shadowing with VSM, all shadow participant renderables should
* be marked as both receivers and casters. Objects that are guaranteed to not cast shadows on
* themselves or other objects (such as flat ground planes) can be set to not cast shadows,
* which might improve shadow quality.
*
* @warning This API is still experimental and subject to change.
*/
- (void) setShadowType: (ShadowType) shadow;

/**
* Sets VSM shadowing options that apply across the entire View.
*
* Additional light-specific VSM options can be set with LightManager::setShadowOptions.
*
* Only applicable when shadow type is set to ShadowType::VSM.
*
* @param options Options for shadowing.
*
* @see setShadowType
*
* @warning This API is still experimental and subject to change.
*/
- (void) setVsmShadowOptions: (VsmShadowOptions) options;

/**
* Returns the VSM shadowing options associated with this View.
*
* @return value set by setVsmShadowOptions().
*/
- (VsmShadowOptions) getVsmShadowOptions;

/**
* Sets soft shadowing options that apply across the entire View.
*
* Additional light-specific soft shadow parameters can be set with LightManager::setShadowOptions.
*
* Only applicable when shadow type is set to ShadowType::DPCF or ShadowType::PCSS.
*
* @param options Options for shadowing.
*
* @see setShadowType
*
* @warning This API is still experimental and subject to change.
*/
- (void) setSoftShadowOptions: (SoftShadowOptions) options;

/**
* Returns the soft shadowing options associated with this View.
*
* @return value set by setSoftShadowOptions().
*/
- (SoftShadowOptions) getSoftShadowOptions;

/**
* Enables or disables post processing. Enabled by default.
*
* Post-processing includes:
*  - Depth-of-field
*  - Bloom
*  - Vignetting
*  - Temporal Anti-aliasing (TAA)
*  - Color grading & gamma encoding
*  - Dithering
*  - FXAA
*  - Dynamic scaling
*
* Disabling post-processing forgoes color correctness as well as some anti-aliasing techniques
* and should only be used for debugging, UI overlays or when using custom render targets
* (see RenderTarget).
*
* @param enabled true enables post processing, false disables it.
*
* @see setBloomOptions, setColorGrading, setAntiAliasing, setDithering, setSampleCount
*/
- (void) setPostProcessingEnabled: (bool) enabled;

//! Returns true if post-processing is enabled. See setPostProcessingEnabled() for more info.
- (bool) isPostProcessingEnabled;

/**
* Inverts the winding order of front faces. By default front faces use a counter-clockwise
* winding order. When the winding order is inverted, front faces are faces with a clockwise
* winding order.
*
* Changing the winding order will directly affect the culling mode in materials
* (see Material::getCullingMode()).
*
* Inverting the winding order of front faces is useful when rendering mirrored reflections
* (water, mirror surfaces, front camera in AR, etc.).
*
* @param inverted True to invert front faces, false otherwise.
*/
- (void) setFrontFaceWindingInverted: (bool) inverted;

/**
* Returns true if the winding order of front faces is inverted.
* See setFrontFaceWindingInverted() for more information.
*/
- (bool) isFrontFaceWindingInverted;

/**
* Enables use of the stencil buffer.
*
* The stencil buffer is an 8-bit, per-fragment unsigned integer stored alongside the depth
* buffer. The stencil buffer is cleared at the beginning of a frame and discarded after the
* color pass.
*
* Each fragment's stencil value is set during rasterization by specifying stencil operations on
* a Material. The stencil buffer can be used as a mask for later rendering by setting a
* Material's stencil comparison function and reference value. Fragments that don't pass the
* stencil test are then discarded.
*
* Post-processing must be enabled in order to use the stencil buffer.
*
* A renderable's priority (see RenderableManager::setPriority) is useful to control the order
* in which primitives are drawn.
*
* @param enabled True to enable the stencil buffer, false disables it (default)
*/
- (void) setStencilBufferEnabled: (bool) enabled;

/**
* Returns true if the stencil buffer is enabled.
* See setStencilBufferEnabled() for more information.
*/
- (bool) isStencilBufferEnabled;

/**
* Sets the stereoscopic rendering options for this view.
*
* Currently, only one type of stereoscopic rendering is supported: side-by-side.
* Side-by-side stereo rendering splits the viewport into two halves: a left and right half.
* Eye 0 will render to the left half, while Eye 1 will render into the right half.
*
* Currently, the following features are not supported with stereoscopic rendering:
* - post-processing
* - shadowing
* - punctual lights
*
* Stereo rendering depends on device and platform support. To check if stereo rendering is
* supported, use Engine::isStereoSupported().
*
* @param options The stereoscopic options to use on this view
*/
//- (void) setStereoscopicOptions: (StereoscopicOptions) options;
//
///**
//* Returns the stereoscopic options associated with this View.
//*
//* @return value set by setStereoscopicOptions().
//*/
//- (StereoscopicOptions) getStereoscopicOptions;

//! debugging: allows to entirely disable frustum culling. (culling enabled by default).
- (void) setFrustumCullingEnabled: (bool) culling;

//! debugging: returns whether frustum culling is enabled.
- (bool) isFrustumCullingEnabled;

//! debugging: sets the Camera used for rendering. It may be different from the culling camera.
- (void) setDebugCamera: (nonnull Camera*) camera;

//! debugging: returns a Camera from the point of view of *the* dominant directional light used for shadowing.
- (nonnull Camera*) getDirectionalShadowCamera;


/** Result of a picking query */
typedef struct PickingQueryResult {
    Entity renderable;     //! RenderableManager Entity at the queried coordinates
    float depth;                  //! Depth buffer value (1 (near plane) to 0 (infinity))
    /**
     * screen space coordinates in GL convention, this can be used to compute the view or
     * world space position of the picking hit. For e.g.:
     *   clip_space_position  = (fragCoords.xy / viewport.wh, fragCoords.z) * 2.0 - 1.0
     *   view_space_position  = inverse(projection) * clip_space_position
     *   world_space_position = model * view_space_position
     *
     * The viewport, projection and model matrices can be obtained from Camera. Because
     * pick() has some latency, it might be more accurate to obtain these values at the
     * time the View::pick() call is made.
     *
     * Note: if the Engine is running at FEATURE_LEVEL_0, the precision or `depth` and
     *       `fragCoords.z` is only 8-bits.
     */
    simd_float3 fragCoords;        //! screen space coordinates in GL convention
} PickingQueryResult;
#warning Implement picking
/**
* Set the value of material global variables. There are up-to four such variable each of
* type float4. These variables can be read in a user Material with
* `getMaterialGlobal{0|1|2|3}()`. All variable start with a default value of { 0, 0, 0, 1 }
*
* @param index index of the variable to set between 0 and 3.
* @param value new value for the variable.
* @see getMaterialGlobal
*/
- (void) setMaterialGlobal: (uint32_t) index :(simd_float4) value;

/**
* Get the value of the material global variables.
* All variable start with a default value of { 0, 0, 0, 1 }
*
* @param index index of the variable to set between 0 and 3.
* @return current value of the variable.
* @see setMaterialGlobal
*/
- (simd_float4) getMaterialGlobal: (uint32_t) index;

/**
* Get an Entity representing the large scale fog object.
* This entity is always inherited by the View's Scene.
*
* It is for example possible to create a TransformManager component with this
* Entity and apply a transformation globally on the fog.
*
* @return an Entity representing the large scale fog object.
*/
- (Entity) getFogEntity;



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
- (void) setViewport: (Viewport) viewport;
- (Viewport) getViewport;

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
//- (void) setAmbientOcclusionOptions: (AmbientOcclusionOptions) options;
//- (AmbientOcclusionOptions) getAmbientOcclusionOptions;
@end

#endif /* View_h */
