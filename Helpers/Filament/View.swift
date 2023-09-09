//
//  View.swift

//  Created by Stef Tervelde on 30.06.22.
//
import Bindings

extension View{
    public var scene: Scene?{
        get{
            getScene()
        }
        set{
            setScene(newValue)
        }
    }
    public var camera: Camera?{
        get{
            getCamera()
        }
        set{
            setCamera(newValue)
        }
    }
    public var viewport: Viewport{
        get{
            getViewport()
        }
        set{
            setViewport(newValue)
        }
    }
    public var blendMode: BlendMode{
        get{
            getBlendMode()
        }
        set{
            setBlendMode(newValue)
        }
    }
    public var shadowing: Bool{
        get{
            isShadowingEnabled()
        }
        set{
            setShadowingEnabled(newValue)
        }
    }
    public var screenSpaceRefraction: Bool{
        get{
            isScreenSpaceRefractionEnabled()
        }
        set{
            setScreenSpaceRefractionEnabled(newValue)
        }
    }
    public var target: RenderTarget?{
        get{
            getRenderTarget()
        }
        set{
            setRenderTarget(newValue)
        }
    }
    public var antiAliasing: AntiAliasing{
        get{
            getAntiAliasing()
        }
        set{
            setAntiAliasing(newValue)
        }
    }
}
