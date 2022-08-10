//
//  IndexBuffer.swift
//
//  Created by Stef Tervelde on 10.08.22.
//
import FilamentBindings


extension IndexBuffer{
    public static func fromArray(_ array: [Int], _ engine: Engine) -> IndexBuffer{
        let indexBuffer = IndexBuffer.Builder()
            .bufferType(.UINT)
            .indexCount(UInt32(array.count))
            .build(engine)
        
        var buffer = Array<UInt8>();
        for indx in array{
            buffer.append(UInt8(indx));
        }
        
        buffer.withUnsafeBytes{ bytes in
            indexBuffer.setBuffer(engine, Data(bytes))
        }
        
        
        return indexBuffer;
    }
}
