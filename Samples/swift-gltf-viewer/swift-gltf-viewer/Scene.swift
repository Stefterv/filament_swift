//
//  Scene.swift

//  Created by Stef Tervelde on 30.06.22.
//


import SwiftUI
import MetalKit
import SceneKit

import Filament

class FilaSceneProps : ObservableObject{
    @Published var size = CGSize(width: 0, height: 0)
    @Published var offset = 0.0
    
    let engine : Filament.Engine
    let renderer : Filament.Renderer
    var swapchain : Filament.SwapChain?


    let materialProvider: glTFIO.MaterialProvider
    let assetLoader: glTFIO.AssetLoader
    let resourceLoader: glTFIO.ResourceLoader

    let scene: Filament.Scene
    let view: Filament.View

    let camera: Filament.Camera
    let camEntity: Entity

    var link: CADisplayLink?
    var uiview: UIView?
    init(){
        engine = Filament.Engine.create()
        renderer = engine.createRenderer()

        scene = engine.createScene()
        view = engine.createView()

        let entManager = EntityManager.get()

        camEntity = entManager.create()
        camera = engine.createCamera(camEntity)

        view.scene = scene
        view.camera = camera

        materialProvider = glTFIO.MaterialProvider.createUberShaderProvider(engine)

        let config = glTFIO.AssetLoader.Configuration()
        config.engine = engine
        config.materials = materialProvider
        config.entities = entManager

        assetLoader = glTFIO.AssetLoader.create(config)

        let opt = glTFIO.ResourceConfiguration()
        opt.engine = engine
        resourceLoader = glTFIO.ResourceLoader(opt)


        let modelURL = Bundle.main.url(forResource: "Download", withExtension: ".glb")!
        guard let data = try? Data(contentsOf: modelURL) else { return }

        guard let asset = assetLoader.createAsset(data) else { return }
        resourceLoader.loadResources(asset);
        let ents = asset.entities
        scene.addEntities(ents);

        let sun = entManager.create();
        LightManager.Builder(.sun)
            .castShadows(true)
            .direction(simd_double3(0.0, -1.0, 0.0))
            .build(engine, sun)
        scene.addEntity(sun)

        let iblURL = Bundle.main.url(forResource: "ibl", withExtension: ".ktx")!
        guard let iblData = try? Data(contentsOf: iblURL) else { return }
        
        let skbURL = Bundle.main.url(forResource: "skybox", withExtension: ".ktx")!
        guard let skbData = try? Data(contentsOf: skbURL) else { return }

        scene.setIndirectLight(Ktx1Loader.createIndirectLight(engine, iblData, false))

        scene.skybox = Ktx1Loader.createSkybox(engine, skbData, false)
    }
    func setupSwapchain(_ view: UIView){
        uiview = view
        if let layer = view.layer as? CAMetalLayer{
            layer.pixelFormat = MTLPixelFormat.bgra8Unorm
            swapchain = engine.createSwapChain(layer)

            link = CADisplayLink(target: self as Any, selector: #selector(renderloop));
            link?.add(to: RunLoop.current, forMode: .common)
        }
    }
    @objc func renderloop(){
        guard let swapchain = swapchain else {
            return
        }
        let origin = SCNNode()
        offset -= 0.01
        let x = sin(offset)
        let y = cos(offset)
        origin.position = SCNVector3(x, 0.5, y)
        
        camera.setLensProjection(28, size.width/size.height, 0.05, 1000.0)
        camera.lookAt(origin.simdPosition, SCNNode().simdPosition, SCNNode().simdWorldUp)

        if(renderer.beginFrame(swapchain)){
            renderer.render(view);
            renderer.endFrame();
        }
    }
    func resize(_ newSize: CGSize){
        if let layer = uiview?.layer as? CAMetalLayer{
            let scale = UIScreen.main.nativeScale
            size = CGSize(width: newSize.width * scale, height: newSize.height * scale)
            layer.drawableSize = size

            view.viewport = Viewport(left: 0, bottom: 0, width: Int32(size.width), height: Int32(size.height))
        }
    }
}
struct FilaScene<Content: SwiftUI.View>: SwiftUI.View {
    let inside: () -> Content
    
    @StateObject var state = FilaSceneProps()
    
    @Environment(\.colorScheme) var colorScheme
    
    init(@ViewBuilder _ inside: @escaping () -> Content) {
        self.inside = inside
    }
    
    var body: some SwiftUI.View {
        inside()
            .overlay(GeometryReader{ reader in Spacer().onAppear{ state.resize(reader.size) }.onChange(of: reader.size){ state.resize($0) } }.ignoresSafeArea())
            .background(FilaSceneMetalLayer().ignoresSafeArea())
            .environmentObject(state)
    }
}


struct FilaSceneMetalLayer : UIViewControllerRepresentable{
    @EnvironmentObject var state: FilaSceneProps
    func updateUIViewController(_ uiViewController: UIViewControllerType, context: Context) {
        
    }
    func makeUIViewController(context: Context) -> some UIViewController {
        let controller = Controller()
        state.setupSwapchain(controller.view)
        return controller
    }
    class Controller: UIViewController{
        override func loadView() {
           view = View()
       }
    }
    class View: UIView{
        override class var layerClass: AnyClass{
            return CAMetalLayer.self;
        }
    }
}


