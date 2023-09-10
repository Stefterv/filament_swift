//
//  ColorGrading.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef ColorGrading_h
#define ColorGrading_h

@interface ColorGrading : NSObject

@property (nonatomic, readonly, nonnull) void* grading  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) grading NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

#warning("TODO")

@end


#endif /* ColorGrading_h */
