#include "headers/Renderer.h"
#include "headers/IRenderProject.h"


/* Main Loop using CADisplayLink */

typedef void (^block_t)();
@interface RendererCaller : NSObject
{
    CADisplayLink *_displayLink;
}
@property (nonatomic, copy) block_t updateBlock;
@end

@implementation RendererCaller

- (void)start:(block_t)block
{
    self.updateBlock = block;
    // check whether the loop is already running
    if(_displayLink == nil)
    {
        // specify update method
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
        
        // add the display link to the run loop (will be called 60 times per second)
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
}

- (void)stop
{
    // check whether the loop is already stopped
    if (_displayLink != nil) {
        // if the display link is present, it gets invalidated (loop stops)
        [_displayLink invalidate];
        _displayLink = nil;
    }
}

- (void)update
{
    _updateBlock();
}

@end

/* Renderer */

/* Public functions */

void Renderer::runRenderer()
{
    if(!isRunning()){
        if (_rendererCaller == nil) _rendererCaller = [[RendererCaller alloc] init];
        
        [_rendererCaller start:^()
            {
                this->update();
            }
         ];
        
        _initialTime += (CACurrentMediaTime() - _initialTime) - _stopTime;
        
        _running = true;
        bRenderer::log("Renderer started", bRenderer::LM_SYS);
    }
}

void Renderer::stopRenderer()
{
    if(isRunning()){
        [_rendererCaller stop];
        
        _stopTime = CACurrentMediaTime() - _initialTime;

        _running = false;
        bRenderer::log("Renderer stopped", bRenderer::LM_SYS);
    }
}

void Renderer::terminateRenderer()
{
    if(isInitialized()){
        [_rendererCaller stop];
        _rendererCaller = nil;
        
        _running = false;
        _initialized = false;
        
        if (_terminateFunction)
            _terminateFunction();
        
        if (_renderProject)
            _renderProject->terminateFunction();
        
        _view->terminateView();

        reset();
        
        bRenderer::log("Renderer terminated", bRenderer::LM_SYS);
    }
}

/* Private functions */

void Renderer::update()
{
     // get time
    double currentTime = CACurrentMediaTime() - _initialTime;
    
    _view->bindFramebuffer();
    
    // clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // render here
    if (_loopFunction)
        _loopFunction(currentTime - _elapsedTime, currentTime);
    
    if (_renderProject)
        _renderProject->loopFunction(currentTime - _elapsedTime, currentTime);
    
    // adjust time
    _elapsedTime = currentTime;
    
    // display
    _view->setContextCurrent();
    _view->presentBuffer();
}
