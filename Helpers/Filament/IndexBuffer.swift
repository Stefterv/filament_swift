//
//  IndexBuffer.swift
//
//  Created by Stef Tervelde on 10.08.22.
//
import Bindings


extension IndexBuffer{
    public static func fromArray(_ array: [Int], _ engine: Engine) -> IndexBuffer{
        let indexBuffer = IndexBuffer.Builder()
            .indexCount(array.count)
            .bufferType(.unsignedShort)
            .build(engine)
        
        var buffer = Array<UInt16>();
        for indx in array{
            buffer.append(UInt16(indx));
        }
        
        buffer.withUnsafeBytes{ bytes in
            indexBuffer.setBuffer(engine, Data(bytes))
        }
        
        
        return indexBuffer;
    }
}
