//
//  IndirectLight.swift

//  Created by Stef Tervelde on 30.06.22.
//
import Bindings

extension IndirectLight{
    public var intensity: Double{
        get{
            getIntensity()
        }
        set{
            setIntensity(newValue)
        }
    }
    public var reflectionsTexture: Texture{
        getReflectionsTexture()
    }
    public var irradianceTexture: Texture{
        getIrradianceTexture()
    }
}
