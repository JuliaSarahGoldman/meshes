/** \file App.cpp */
#include "App.h"

// Tells C++ to invoke command-line main() function even on OS X and Win32.
G3D_START_AT_MAIN();

int main(int argc, const char* argv[]) {
    {
        G3DSpecification g3dSpec;
        g3dSpec.audio = false;
        initGLG3D(g3dSpec);
    }

    GApp::Settings settings(argc, argv);

    // Change the window and other startup parameters by modifying the
    // settings class.  For example:
    settings.window.caption             = argv[0];

    // Set enable to catch more OpenGL errors
    // settings.window.debugContext     = true;

    // Some common resolutions:
    // settings.window.width            =  854; settings.window.height       = 480;
    // settings.window.width            = 1024; settings.window.height       = 768;
    settings.window.width               = 1280; settings.window.height       = 720;
    //settings.window.width             = 1920; settings.window.height       = 1080;
    // settings.window.width            = OSWindow::primaryDisplayWindowSize().x; settings.window.height = OSWindow::primaryDisplayWindowSize().y;
    settings.window.fullScreen          = false;
    settings.window.resizable           = ! settings.window.fullScreen;
    settings.window.framed              = ! settings.window.fullScreen;

    // Set to true for a significant performance boost if your app can't render at 60fps, or if
    // you *want* to render faster than the display.
    settings.window.asynchronous        = false;

    settings.hdrFramebuffer.depthGuardBandThickness = Vector2int16(64, 64);
    settings.hdrFramebuffer.colorGuardBandThickness = Vector2int16(0, 0);
    settings.dataDir                    = FileSystem::currentDirectory();
    settings.screenshotDirectory        = "../journal/";

    settings.renderer.deferredShading = true;
    settings.renderer.orderIndependentTransparency = false;

    return App(settings).run();
}


App::App(const GApp::Settings& settings) : GApp(settings) {
}


void App::makeCylinder(float radius, float height, int numVertices){
    TextOutput file("../data-files/model/cylinder.off");
    file.printf(STR(OFF\n%d %d 1\n), 2*numVertices, numVertices+2);
        //loop to make vertices
    for(int i = 0; i < numVertices; ++i){
        file.printf(STR(%f %f %f\n), radius*(-sin(((2*pif()*i)/numVertices))), radius*height, radius*(cos((2*pif()*i)/numVertices)));
    }
    for(int i = 0; i < numVertices; ++i){
        file.printf(STR(%f 0.0 %f\n), radius*(-sin(((2*pif()*i)/numVertices))), radius*(cos((2*pif()*i)/numVertices)));
    }
    //Loop for sides
    for(int i = 0; i < numVertices; ++i){
        file.printf(STR(4 %d %d %d %d\n), i, (i+1)%numVertices, (i+1)%numVertices + numVertices, i+numVertices);
    }
    //Loop for top
    file.printf(STR(%d ), numVertices);
    for(int i = numVertices-1; i >= 0; --i){
        file.printf(" %d", i);
    }
    file.printf(STR(\n));
    //Loop for bottom
    file.printf(STR(%d), numVertices);
    for(int i = numVertices; i < 2*numVertices; ++i){
        file.printf(" %d", i);
    }
    file.printf(STR(\n));
    file.commit();
}

String App::makeTube(Array<float>& radii, Array<float>& heights, int slices){
     String tube = String("OFF\n");
     tube += format("%d %d 1\n", heights.size()*slices, (heights.size()-1)*slices);
     for (int i = 0; i < heights.size(); ++i){
        for(int j = 0; j < slices; ++j){
            tube += format(STR(%f %f %f\n), radii[i]*(-sin(((2*pif()*j)/slices))), heights[i], radii[i]*(cos((2*pif()*j)/slices)));
        }
    }
    for (int i = 0; i < heights.size()-1; ++i){
        for(int j = 0; j < slices; ++j){
            tube+= format(STR(4 %d %d %d %d\n), i*slices +slices + j, i*slices +slices + (j+1)%slices, i*slices + (j+1)%slices, i*slices + j );
        }
    }
    return tube;
}

void App::makeFountainPiece(){
    int slices = 40;
    Array<float> radii(0.0, 4.0, 4.25, 4, 3.5, 3.75);
    radii.append(3.75);
    radii.append(6.0);
    radii.append(6.25);
    radii.append(6.27);
    radii.append(6.5);
    radii.append(6.25);
    radii.append(6.25);
    radii.append(5.0);
    radii.append(4.7);
    radii.append(5.0);
    radii.append(0.0);
    
    Array<float> heights(0.0, 0.0, 0.5, 1.0, 2.0, 2.5);
    heights.append(3.0);
    heights.append(3.0);
    heights.append(4.0);
    heights.append(4.5);
    heights.append(5.0);
    heights.append(5.5);
    heights.append(4.5);
    heights.append(4);
    heights.append(3.5);
    heights.append(3.25);
    heights.append(3.25);
    TextOutput file("../data-files/model/fountain.off");
    String tube = makeTube(radii, heights, slices);
    file.writeSymbol(tube);
    file.commit();
}


void App::makeTree(){
    int slices = 40;
    Array<float> radii(0.0, 3.5, 3.2, 3.0, 2.9, 2.7);
    radii.append(2.9);
    radii.append(2.5);
    radii.append(2.0);
    radii.append(2.6);
    radii.append(2.5);
    radii.append(2.4);
    radii.append(1.7);
    radii.append(1.9);
    radii.append(1.7);
    radii.append(1.4);
    radii.append(1.2);
    radii.append(0.0);
    
    Array<float> heights(0.0, 0.0, 1.0, 1.5, 2.0, 2.5);
    heights.append(3.0);
    heights.append(4.0);
    heights.append(4.5);
    heights.append(5.0);
    heights.append(6.0);
    heights.append(7.0);
    heights.append(8.0);
    heights.append(9.0);
    heights.append(9.5);
    heights.append(10.0);
    heights.append(11.0);
    heights.append(12.0);
    TextOutput file("../data-files/model/tree.off");
    file.writeSymbol(makeTube(radii, heights, slices));
    file.commit();
}


void App::makeSplash(){
    int slices = 40;
    Array<float> radii(.5, .5, .6, .75, .63, .8);
    radii.append(.95);
    radii.append(1.0);
    radii.append(1.5);
    radii.append(1.8);
    radii.append(2.0);
    radii.append(2.2);
    radii.append(2.0);
    radii.append(1.75);
    radii.append(0.0);
    
    Array<float> heights(0.0, 0.5, 0.75, 1.0, 1.25, 1.5);
    heights.append(1.75);
    heights.append(1.75);
    heights.append(1.5);
    heights.append(1.25);
    heights.append(1.0);
    heights.append(1.25);
    heights.append(1.75);
    heights.append(2.0);
    heights.append(1.85);
    TextOutput file("../data-files/model/splash.off");
    file.writeSymbol(makeTube(radii, heights, slices));
    file.commit();
}



void App::makeGlass(int slices){
    Array<float> radii(0.0, 1.0, 0.25, .25, 0.5, 0.7);
    radii.append(1.0);
    radii.append(1.5);
    radii.append(2.0);
    radii.append(1.4);
    radii.append(.5);
    radii.append(0.0);
    Array<float> heights(-1.1, -1.1, -1, .6, 0.8, 1.0);
    heights.append(1.3);
    heights.append(2.0);
    heights.append(3.1);
    heights.append(2.0);
    heights.append(1.7);
    heights.append(1.4);
    TextOutput file("../data-files/model/glass.off");
    file.writeSymbol(makeTube(radii, heights, slices));
 
    file.commit();
}


// Called before the application loop begins.  Load data here and
// not in the constructor so that common exceptions will be
// automatically caught.
void App::onInit() {
    GApp::onInit();
    makeFountainPiece();
    makeSplash();
    makeTree();
    setFrameDuration(1.0f / 120.0f);

    // Call setScene(shared_ptr<Scene>()) or setScene(MyScene::create()) to replace
    // the default scene here.
    
    showRenderingStats      = false;

    makeGUI();
    // For higher-quality screenshots:
    // developerWindow->videoRecordDialog->setScreenShotFormat("PNG");
    // developerWindow->videoRecordDialog->setCaptureGui(false);
    developerWindow->cameraControlWindow->moveTo(Point2(developerWindow->cameraControlWindow->rect().x0(), 0));
    loadScene(
        //"G3D Sponza"
        "G3D Cornell Box" // Load something simple
        //developerWindow->sceneEditorWindow->selectedSceneName()  // Load the first scene encountered 
        );
}


void App::makeGUI() {
    // Initialize the developer HUD
    createDeveloperHUD();

    debugWindow->setVisible(true);
    developerWindow->videoRecordDialog->setEnabled(true);

    /*Begin commenting out to remove pane here
    GuiPane* glassPane = debugPane->addPane("Chalice");
    glassPane->setNewChildSize(240);
    glassPane->addNumberBox("Slices", &m_slices,"m", GuiTheme::NO_SLIDER, 0, 100)->setUnitsSize(1);
    glassPane->addButton("Generate", [this](){
        drawMessage("Chalice is loading.");
        makeGlass(m_slices);
        ArticulatedModel::clearCache();
        loadScene(developerWindow->sceneEditorWindow->selectedSceneName());

    });


    GuiPane* cylinderPane = debugPane->addPane("Cylinder");
    cylinderPane->setNewChildSize(240);
    cylinderPane->addNumberBox("Radius", &m_radius,"m", GuiTheme::NO_SLIDER, 0.0f, 100.0f)->setUnitsSize(.2);
    cylinderPane->addNumberBox("Height", &m_height,"m", GuiTheme::NO_SLIDER, 0.0f, 100.0f)->setUnitsSize(1);
    cylinderPane->addButton("Generate", [this](){
        drawMessage("Cylinder is loading.");
        makeCylinder(m_radius, m_height, 40);
        ArticulatedModel::clearCache();
        loadScene(developerWindow->sceneEditorWindow->selectedSceneName());

    });
    
    GuiPane* heightfieldPane = debugPane->addPane("Heightfield");
 
    heightfieldPane->setNewChildSize(240);
    heightfieldPane->addNumberBox("Max Y", &m_heightfieldYScale, "m", GuiTheme::LOG_SLIDER, 0.0f, 100.0f)->setUnitsSize(30);
    heightfieldPane->addNumberBox("XZ Scale", &m_heightfieldXZScale, "m", GuiTheme::LOG_SLIDER, 0.001f, 10.0f)->setUnitsSize(30);


    heightfieldPane->beginRow(); {
        heightfieldPane->addTextBox("Input Image", &m_heightfieldSource)->setWidth(210);
        heightfieldPane->addButton("...", [this](){
            FileDialog::getFilename(m_heightfieldSource, "png", false);
        })->setWidth(30);
    } heightfieldPane->endRow();

    heightfieldPane->addButton("Generate", [this](){
        drawMessage("Heightfield is loading");
        shared_ptr<Image> image;
        try{
            image = Image::fromFile(m_heightfieldSource);
            TextOutput file("../data-files/model/heightfield.off");
            file.printf(STR(OFF\n%d %d 1\n), image->width()*image->height(), (image->width()-1)*(image->height()-1));
            Color3 color = Color3();
            for (int i = 0; i < image->width(); ++i){
                for (int j = 0; j< image->height(); ++j){
                    const Point2int32 point = Point2int32(i,j);
                    image->get(point, color);
                    float grayValue = color.average();
                    file.printf("%f %f %f\n", ((float)j)*m_heightfieldXZScale, grayValue*m_heightfieldYScale, ((float) i)*m_heightfieldXZScale);
                }
            }

            for (int i = 0; i < image->width()-1; ++i){
                for (int j = 0; j < image->height()-1; ++j){
                    file.printf("4 %d %d %d %d\n", j + i*image->height(), j + (i+1)*image->height(), j+1 + (i+1)*image->height(), j+1 + i*image->height());
                }
            }
            file.commit();

            ArticulatedModel::clearCache();
            loadScene(developerWindow->sceneEditorWindow->selectedSceneName());
        }catch(...){
            msgBox("Unable to load the image.", m_heightfieldSource);
        }
    });



    GuiPane* infoPane = debugPane->addPane("Info", GuiTheme::ORNATE_PANE_STYLE);
    
    // Example of how to add debugging controls
    infoPane->addLabel("You can add GUI controls");
    infoPane->addLabel("in App::onInit().");
    infoPane->addButton("Exit", [this]() { m_endProgram = true; });
    infoPane->pack();

    End commenting to remove pane here*/

    // More examples of debugging GUI controls:
    // debugPane->addCheckBox("Use explicit checking", &explicitCheck);
    // debugPane->addTextBox("Name", &myName);
    // debugPane->addNumberBox("height", &height, "m", GuiTheme::LINEAR_SLIDER, 1.0f, 2.5f);
    // button = debugPane->addButton("Run Simulator");
    // debugPane->addButton("Generate Heightfield", [this](){ generateHeightfield(); });
    // debugPane->addButton("Generate Heightfield", [this](){ makeHeightfield(imageName, scale, "model/heightfield.off"); });

    debugWindow->pack();
    debugWindow->setRect(Rect2D::xywh(0, 0, (float)window()->width(), debugWindow->rect().height()));
}


// This default implementation is a direct copy of GApp::onGraphics3D to make it easy
// for you to modify. If you aren't changing the hardware rendering strategy, you can
// delete this override entirely.
void App::onGraphics3D(RenderDevice* rd, Array<shared_ptr<Surface> >& allSurfaces) {
    if (!scene()) {
        if ((submitToDisplayMode() == SubmitToDisplayMode::MAXIMIZE_THROUGHPUT) && (!rd->swapBuffersAutomatically())) {
            swapBuffers();
        }
        rd->clear();
        rd->pushState(); {
            rd->setProjectionAndCameraMatrix(activeCamera()->projection(), activeCamera()->frame());
            drawDebugShapes();
        } rd->popState();
        return;
    }

    GBuffer::Specification gbufferSpec = m_gbufferSpecification;
    extendGBufferSpecification(gbufferSpec);
    m_gbuffer->setSpecification(gbufferSpec);
    m_gbuffer->resize(m_framebuffer->width(), m_framebuffer->height());
    m_gbuffer->prepare(rd, activeCamera(), 0, -(float)previousSimTimeStep(), m_settings.hdrFramebuffer.depthGuardBandThickness, m_settings.hdrFramebuffer.colorGuardBandThickness);

    m_renderer->render(rd, m_framebuffer, scene()->lightingEnvironment().ambientOcclusionSettings.enabled ? m_depthPeelFramebuffer : shared_ptr<Framebuffer>(),
        scene()->lightingEnvironment(), m_gbuffer, allSurfaces);

    // Debug visualizations and post-process effects
    rd->pushState(m_framebuffer); {
        // Call to make the App show the output of debugDraw(...)
        rd->setProjectionAndCameraMatrix(activeCamera()->projection(), activeCamera()->frame());
        drawDebugShapes();
        const shared_ptr<Entity>& selectedEntity = (notNull(developerWindow) && notNull(developerWindow->sceneEditorWindow)) ? developerWindow->sceneEditorWindow->selectedEntity() : shared_ptr<Entity>();
        scene()->visualize(rd, selectedEntity, allSurfaces, sceneVisualizationSettings(), activeCamera());

        // Post-process special effects
        m_depthOfField->apply(rd, m_framebuffer->texture(0), m_framebuffer->texture(Framebuffer::DEPTH), activeCamera(), m_settings.hdrFramebuffer.depthGuardBandThickness - m_settings.hdrFramebuffer.colorGuardBandThickness);

        m_motionBlur->apply(rd, m_framebuffer->texture(0), m_gbuffer->texture(GBuffer::Field::SS_EXPRESSIVE_MOTION),
            m_framebuffer->texture(Framebuffer::DEPTH), activeCamera(),
            m_settings.hdrFramebuffer.depthGuardBandThickness - m_settings.hdrFramebuffer.colorGuardBandThickness);
    } rd->popState();

    // We're about to render to the actual back buffer, so swap the buffers now.
    // This call also allows the screenshot and video recording to capture the
    // previous frame just before it is displayed.
    if (submitToDisplayMode() == SubmitToDisplayMode::MAXIMIZE_THROUGHPUT) {
        swapBuffers();
    }

    // Clear the entire screen (needed even though we'll render over it, since
    // AFR uses clear() to detect that the buffer is not re-used.)
    rd->clear();

    // Perform gamma correction, bloom, and SSAA, and write to the native window frame buffer
    m_film->exposeAndRender(rd, activeCamera()->filmSettings(), m_framebuffer->texture(0), settings().hdrFramebuffer.colorGuardBandThickness.x + settings().hdrFramebuffer.depthGuardBandThickness.x, settings().hdrFramebuffer.depthGuardBandThickness.x);
}


void App::onAI() {
    GApp::onAI();
    // Add non-simulation game logic and AI code here
}


void App::onNetwork() {
    GApp::onNetwork();
    // Poll net messages here
}


void App::onSimulation(RealTime rdt, SimTime sdt, SimTime idt) {
    GApp::onSimulation(rdt, sdt, idt);

    // Example GUI dynamic layout code.  Resize the debugWindow to fill
    // the screen horizontally.
    debugWindow->setRect(Rect2D::xywh(0, 0, (float)window()->width(), debugWindow->rect().height()));
}


bool App::onEvent(const GEvent& event) {
    // Handle super-class events
    if (GApp::onEvent(event)) { return true; }

    // If you need to track individual UI events, manage them here.
    // Return true if you want to prevent other parts of the system
    // from observing this specific event.
    //
    // For example,
    // if ((event.type == GEventType::GUI_ACTION) && (event.gui.control == m_button)) { ... return true; }
    // if ((event.type == GEventType::KEY_DOWN) && (event.key.keysym.sym == GKey::TAB)) { ... return true; }
    // if ((event.type == GEventType::KEY_DOWN) && (event.key.keysym.sym == 'p')) { ... return true; }

    return false;
}


void App::onUserInput(UserInput* ui) {
    GApp::onUserInput(ui);
    (void)ui;
    // Add key handling here based on the keys currently held or
    // ones that changed in the last frame.
}


void App::onPose(Array<shared_ptr<Surface> >& surface, Array<shared_ptr<Surface2D> >& surface2D) {
    GApp::onPose(surface, surface2D);

    // Append any models to the arrays that you want to later be rendered by onGraphics()
}


void App::onGraphics2D(RenderDevice* rd, Array<shared_ptr<Surface2D> >& posed2D) {
    // Render 2D objects like Widgets.  These do not receive tone mapping or gamma correction.
    Surface2D::sortAndRender(rd, posed2D);
}


void App::onCleanup() {
    // Called after the application loop ends.  Place a majority of cleanup code
    // here instead of in the constructor so that exceptions can be caught.
}
