//
//  SwapChain.h
//
//  Created by Stef Tervelde on 29.06.22.
//

#import <Foundation/Foundation.h>

#ifndef SwapChain_h
#define SwapChain_h

/**
 * A <code>SwapChain</code> represents an Operating System's <b>native</b> renderable surface.
 *
 * <p>Typically it's a native window or a view. Because a <code>SwapChain</code> is initialized
 * from a native object, it is given to filament as an <code>Object</code>, which must be of the
 * proper type for each platform filament is running on.</p>
 *
 * <code>
 * let swapChain = engine.createSwapChain(nativeWindow);
 * </code>
 *
 */

@interface SwapChain : NSObject

@property (nonatomic, readonly, nonnull) void* swapchain NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) swapchain NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

@end


#endif /* SwapChain_h */
