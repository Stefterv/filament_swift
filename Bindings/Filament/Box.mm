//
//  Box.mm
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Box.h"
#import <filament/Box.h>

@implementation Box

- (id)initWithVector:(simd_double3)center Extent:(simd_double3)halfExtent{
    self = [self init];
    self->_center = center;
    self->_halfExtent = halfExtent;
    return self;
}



@end
