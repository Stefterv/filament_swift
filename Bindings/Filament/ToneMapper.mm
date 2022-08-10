//
//  ToneMapper.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/ToneMapper.h"
#import <filament/ToneMapper.h>

@implementation ToneMapper{
    filament::ToneMapper* nativeMapper;
}

- (id) init:(void *)mapper{
    self->_mapper = mapper;
    self->nativeMapper = (filament::ToneMapper*)mapper;
    return self;
}

@end
