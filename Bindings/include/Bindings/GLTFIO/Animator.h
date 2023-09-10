//
//  Animator.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef Animator_h
#define Animator_h

NS_SWIFT_NAME(glTFIO.Animator)
@interface Animator : NSObject

@property (nonatomic, readonly, nonnull) void* animator  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) animator NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

/**
 * Applies rotation, translation, and scale to entities that have been targeted by the given
 * animation definition. Uses <code>TransformManager</code>.
 *
 * @param animationIndex Zero-based index for the <code>animation</code> of interest.
 * @param time Elapsed time of interest in seconds.
 *
 * @see #getAnimationCount
 */
- (void) applyAnimation: (int) animationIndex :(double) time;
/**
 * Computes root-to-node transforms for all bone nodes, then passes the results into
 * {@link com.google.android.filament.RenderableManager#setBonesAsMatrices(int, Buffer, int, int)}.
 * Uses <code>TransformManager</code> and <code>RenderableManager</code>.
 *
 * <p>NOTE: this operation is independent of <code>animation</code>.</p>
 */
- (void) updateBoneMatrices;
/**
 * Applies a blended transform to the union of nodes affected by two animations.
 * Used for cross-fading from a previous skinning-based animation or rigid body animation.
 *
 * First, this stashes the current transform hierarchy into a transient memory buffer.
 *
 * Next, this applies previousAnimIndex / previousAnimTime to the actual asset by internally
 * calling applyAnimation().
 *
 * Finally, the stashed local transforms are lerped (via the scale / translation / rotation
 * components) with their live counterparts, and the results are pushed to the asset.
 *
 * To achieve a cross fade effect with skinned models, clients will typically call animator
 * methods in this order: (1) applyAnimation (2) applyCrossFade (3) updateBoneMatrices. The
 * animation that clients pass to applyAnimation is the "current" animation corresponding to
 * alpha=1, while the "previous" animation passed to applyCrossFade corresponds to alpha=0.
 */
- (void) applyCrossFade: (int) previousAnimIndex :(double) previousAnimTime :(double) alpha;

- (void) resetBoneMatrices;

- (size_t) getAnimationCount;

/**
 * Returns the duration of the specified glTF <code>animation</code> in seconds.
 *
 * @param animationIndex Zero-based index for the <code>animation</code> of interest.
 *
 * @see #getAnimationCount
 * */
- (double) getAnimationDuration: (int) animationIndex;

/**
 * Returns a weak reference to the string name of the specified <code>animation</code>, or an
 * empty string if none was specified.
 *
 * @param animationIndex Zero-based index for the <code>animation</code> of interest.
 *
 * @see #getAnimationCount
 */
- (nonnull NSString*) getAnimationName: (int) animationIndex;

@end


#endif /* Animator_h */
