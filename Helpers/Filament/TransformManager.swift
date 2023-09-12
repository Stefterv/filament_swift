//
//  TransformManager.swift
//
//  Created by Stef Tervelde on 14.07.22.
//
import Bindings

extension TransformManager{
    public func setTransform(_ instance: EntityInstance, _ localTransform: simd_float4x4){
        setTransform(instance, localTransform.toDouble())
    }
    public var accurateTranslations: Bool{
        get{
            isAccurateTranslationsEnabled()
        }
        set{
            setAccurateTranslationsEnabled(newValue)
        }
    }
}
