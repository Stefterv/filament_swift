//
//  Box.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>
#import <simd/simd.h>

#ifndef Box_h
#define Box_h

@interface Box : NSObject

@property simd_double3 center;
@property simd_double3 halfExtent;
- (nonnull id) initWithVector: (simd_double3) center Extent:(simd_double3) halfExtent;

@end


@interface AAB: NSObject

@property (nonatomic) simd_double3 min;
@property (nonatomic) simd_double3 max;

@end

#endif /* Box_h */
