//
//  Scene.swift
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 05.07.22.
//
import FilamentBindings

extension Scene{
    public func addEntities(_ entities: [Entity]){
        for entity in entities{
            addEntity(entity)
        }
    }
    public func removeEntities(_ entities: [Entity]){
        for entity in entities{
            removeEntity(entity)
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
}
