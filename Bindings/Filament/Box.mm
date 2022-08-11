//
//  Box.mm
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Box.h"
#import <filament/Box.h>

@implementation Box{
    
}
- (id)initWithVector:(simd_double3)center :(simd_double3)halfExtent{
    self = [self init];
    [self setCenter:center];
    [self setHalfExtent:halfExtent];
}

@end
