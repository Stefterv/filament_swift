//
//  FilamentAsset.swift

//  Created by Stef Tervelde on 30.06.22.
//
import Bindings

extension glTFIO.FilamentAsset{
    public var entities: [Entity]{
        let ents = getEntities();
        return ents.map({$0.int32Value})
    }
}
