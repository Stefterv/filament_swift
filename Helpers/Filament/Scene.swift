//
//  Scene.swift

//  Created by Stef Tervelde on 05.07.22.
//
import Bindings

extension Scene{
#warning("interact with entities as an array scene.entities.add")
    public func addEntities(_ entities: [Entity]){
        for entity in entities{
            addEntity(entity)
        }
    }
    public func removeEntities(_ entities: [Entity]){
        for entity in entities{
            remove(entity)
        }
    }
    public var skybox: Skybox?{
        get{
            getSkybox()
        }
        set{
            setSkybox(newValue)
        }
    }
    public var renderableCount: Int{
        getRenderableCount()
    }
    public var lightCount: Int{
        getLightCount()
    }
    public var indirectLight: IndirectLight?{
        get{
            getIndirectLight()
        }
        set{
            setIndirectLight(newValue)
        }
    }
}
