//
//  Engine.swift
//
//
//  Created by Stef Tervelde on 12.09.23.
//
import Bindings

extension Engine{
    public var transformManager: TransformManager{
        getTransformManager()
    }
    public var lightManager: LightManager{
        getLightManager()
    }
    public var entityManager: EntityManager{
        getEntityManager()
    }
    public var renderableManager: RenderableManager{
        getRenderableManager()
    }
    public var backend: Backend{
        getBackend()
    }
}
