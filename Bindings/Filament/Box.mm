//
//  Box.mm
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/Box.h"
#import <filament/Box.h>

@implementation Box{
    filament::Box* nativeBox;
}

- (id) init:(void *)box{
    self->_box = box;
    self->nativeBox = (filament::Box*)box;
    return self;
}
# warning Implement Box

@end
