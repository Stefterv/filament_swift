//
//  Skybox.swift

//  Created by Stef Tervelde on 30.06.22.
//
import Bindings

extension Skybox{
    public var layerMask: UInt8{
        getLayerMask()
    }
    public var intensity: Float{
        getIntensity()
    }
    public var texture: Texture?{
        getTexture()
    }
}
