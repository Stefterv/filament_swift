//
//  Animator.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/GLTFIO/Animator.h"
#import <gltfio/Animator.h>

@implementation Animator{
    filament::gltfio::Animator* nativeAnimator;
}

- (id) init:(void *)animator{
    self->_animator = animator;
    self->nativeAnimator = (filament::gltfio::Animator*)animator;
    return self;
}

- (void)applyAnimation:(int)animationIndex :(double)time{
    nativeAnimator->applyAnimation(animationIndex, time);
}
- (void)applyCrossFade:(int)previousAnimIndex :(double)previousAnimTime :(double)alpha{
    nativeAnimator->applyCrossFade(previousAnimIndex, previousAnimTime, alpha);
}
- (size_t)getAnimationCount{
    return nativeAnimator->getAnimationCount();
}
- (double)getAnimationDuration:(int)animationIndex{
    return nativeAnimator->getAnimationDuration(animationIndex);
}
- (NSString *)getAnimationName:(int)animationIndex{
    return [[NSString alloc] initWithUTF8String:nativeAnimator->getAnimationName(animationIndex)];
}
- (void)resetBoneMatrices{
    nativeAnimator->resetBoneMatrices();
}
- (void)updateBoneMatrices{
    nativeAnimator->updateBoneMatrices();
}

@end
