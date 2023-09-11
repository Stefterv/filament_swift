//
//  FilamatMaterialBuilder.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filamat/MaterialBuilder.h"
#import <filamat/MaterialBuilder.h>
@implementation FMaterialBuilder{
    filamat::MaterialBuilder* nativeBuilder;
}
- (id) init:(void *)builder{
    self->_builder = builder;
    self->nativeBuilder = (filamat::MaterialBuilder*)builder;
    return self;
}


@end
