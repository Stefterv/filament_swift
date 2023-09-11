//
//  FilamatMaterialBuilder.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef FilamatMaterialBuilder_h
#define FilamatMaterialBuilder_h

@interface FMaterialBuilder : NSObject

@property (nonatomic, readonly, nonnull) void* builder  NS_SWIFT_UNAVAILABLE("Don't access the raw pointers");
- (nonnull id) init: (nonnull void*) builder NS_SWIFT_UNAVAILABLE("Instances are created internally");
- (nonnull id) init NS_UNAVAILABLE;

NS_ASSUME_NONNULL_BEGIN

NS_ASSUME_NONNULL_END
#warning  Implement, Very long

@end


#endif /* FilamatMaterialBuilder_h */
