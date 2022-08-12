//
//  Scene.swift

//  Created by Stef Tervelde on 30.06.22.
//


import SwiftUI
import MetalKit
import Filament
import SceneKit

class FilaSceneProps : ObservableObject{
    @Published var size = CGSize(width: 0, height: 0)
    
    let engine : Filament.Engine
    let renderer : Filament.Renderer
    var swapchain : Filament.SwapChain?
    

    let materialProvider: glTFIO.MaterialProvider
    let assetLoader: glTFIO.AssetLoader
    let resourceLoader: glTFIO.ResourceLoader
    
    let scene: Filament.Scene
    let view: Filament.View
    
    let camera: Filament.Camera
    
    var link: CADisplayLink?
    var uiview: UIView?
    init(){
        engine = Filament.Engine.create()
        renderer = engine.createRenderer()
        
        scene = engine.createScene()
        view = engine.createView()
        
        view.viewport = Viewport(left: 0, bottom: 0, width: 256, height: 256)
        let entManager = Utils.EntityManager.get()
        
        camera = engine.createCamera(entManager.create())
        
        view.scene = scene
        view.camera = camera
        
        materialProvider = glTFIO.MaterialProvider.createUberShaderProvider(engine)

        let config = glTFIO.AssetLoader.Configuration()
        config.engine = engine
        config.materials = materialProvider
        config.entities = entManager
        
        assetLoader = glTFIO.AssetLoader.create(config)

        let opt = glTFIO.ResourceLoader.Options()
        resourceLoader = glTFIO.ResourceLoader(engine, opt)
        
    
        let modelURL = Bundle.main.url(forResource: "Download", withExtension: ".glb")!
        guard let data = try? Data(contentsOf: modelURL) else { return }
        
        guard let asset = assetLoader.createAsset(fromBinary: data) else { return }
        resourceLoader.loadResources(asset);
        let ents = asset.entities
        scene.addEntities(ents);
        
        let sun = entManager.create();
        LightManager.Builder(.sun)
            .castShadows(true)
            .direction(simd_double3(0.0, -1.0, 0.0))
            .build(engine, sun)
        scene.addEntity(sun)
        
//        let iblURL = Bundle.main.url(forResource: "default_env_ibl", withExtension: ".ktx")!
//        guard let iblData = try? Data(contentsOf: iblURL) else { return }
//
//        scene.setIndirectLight(Ktx1Loader.createIndirectLight(engine, iblData, false))
//
//        let skbURL = Bundle.main.url(forResource: "default_env_ibl", withExtension: ".ktx")!
//        guard let skbData = try? Data(contentsOf: skbURL) else { return }
//
//        let skybox = Ktx1Loader.createSkybox(engine, skbData, false)
//        scene.skybox = skybox
        
        let triangle = entManager.create()
        let mesh = createTriangleMesh();
        createRenderable(entity: triangle, mesh: mesh, material: nil)
        scene.addEntity(triangle)
    }
    
    func createTriangleMesh() -> Mesh{
        let vertices: [Vertex] = [
            Vertex(x: -0.1, y: -0.1, z: 0.0, w: 1.0, u: 0.0, v: 1.0),
            Vertex(x: 0.3, y: -0.1, z: 0.0, w: 1.0, u: 2.0, v: 1.0),
            Vertex(x: -0.1, y: 0.3, z: 0.0, w: 1.0, u: 0, v: -1.0)
        ]
        
        let indices: [Int] = [0,1,2];
        
        return Mesh(vertices: vertices, indices: indices)
    }
    struct Vertex{
        let x: Float
        let y: Float
        let z: Float
        let w: Float
        let u: Float
        let v: Float
    }
    struct Mesh{
        var vertices: [Vertex]
        var indices: [Int]
    }
    func createRenderable(entity: Entity, mesh: Mesh, material: MaterialInstance?){
        let vertexBuffer = VertexBuffer.Builder()
            .vertexCount(mesh.vertices.count)
            .bufferCount(1)
            .attribute(.position, 0, .float4, 0, 24)
            .attribute(.uv0, 0, .float2, 16, 24)
            .build(engine)
        mesh.vertices.withUnsafeBytes{ bytes in
            vertexBuffer.setBufferAt(engine, 0, Data(bytes))
        }
        let indexBuffer = IndexBuffer.fromArray(mesh.indices, engine);
        
        
        RenderableManager.Builder(1)
            .geometry(0, .triangles, vertexBuffer, indexBuffer, 0, 3, engine)
            .receiveShadows(false)
            .castShadows(false)
            .culling(false)
            .build(engine, entity);
    }
    
    func setClear(color: CIColor){
        let opt = Renderer.ClearOptions()
        opt.clearColor = color
        opt.clear = true
        opt.discard = true
        renderer.setClearOptions(opt)
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
            
            let origin = SCNNode()
            origin.position = SCNVector3(0, 1, 1)
            
            // TODO: Move to own entity
            camera.setLensProjection(50, size.width/size.height, 0.01, 10)
            camera.lookAt(origin.simdPosition, SCNNode().simdPosition, SCNNode().simdWorldUp)
        }
    }
    static func getFile(forResource resource: String, withExtension fileExt: String?) -> [UInt8]? {
        guard let fileUrl: URL = Bundle.main.url(forResource: resource, withExtension: fileExt) else {
            return nil
        }
        
        do {
            let rawData: Data = try Data(contentsOf: fileUrl)
            return [UInt8](rawData)
        } catch {
            return nil
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
            .task(id: colorScheme){ state.setClear(color: colorScheme == .light ? .white : .black) }
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


