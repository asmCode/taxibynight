//
//  ViewController.m
//  Taxi by Night
//
//  Created by Majak on 12/03/14.
//  Copyright (c) 2014 Semi-Serious Games. All rights reserved.
//

#import "ViewController.h"
#include "../../../Bunnies/InfectedBunniesFactory.h"
#include "../../../Bunnies/Environment.h"
#include <Graphics/GraphicsEngineFactory.h>
#include <string>

#import <UIKit/UIDevice.h>
#import "GADBannerView.h"

@interface ViewController ()
{
	GADBannerView *m_bannerView;
}

@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self view].multipleTouchEnabled = YES;
	self.preferredFramesPerSecond = 300;
	
	m_bannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerLandscape];
	m_bannerView.adUnitID = @"ca-app-pub-7651431092078292/6036357967";
	
	GADRequest *request = [GADRequest request];
	
	// Make the request for a test ad. Put in an identifier for
	// the simulator as well as any devices you want to receive test ads.
	request.testDevices = [NSArray arrayWithObjects:
						   GAD_SIMULATOR_ID,
                           nil];
	
	m_bannerView.rootViewController = self;
	[self.view addSubview:m_bannerView];
	
	[m_bannerView loadRequest:request];
	
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

IGameController *m_game;

- (void) InitializeGame
{
	std::string basePath = [[[NSBundle mainBundle] bundlePath] UTF8String];
	basePath = basePath + "/";
	
	NSFileManager *fileMng = [NSFileManager defaultManager];
	NSError *err = nil;
	NSURL *appropriateForUrl = [NSURL fileURLWithPath:@"." isDirectory:YES];
	NSURL *docPathUrl = [fileMng URLForDirectory:NSDocumentDirectory
										inDomain:NSUserDomainMask
							   appropriateForURL:appropriateForUrl
										  create:YES
										   error:&err];
	
	std::string docPath = [[docPathUrl path] UTF8String];
	
	TaxiGame::Environment::GetInstance()->SetBasePath(basePath);
	TaxiGame::Environment::GetInstance()->SetWritePath(docPath);
	
	TaxiGame::Environment::GetInstance()->SetScreenSize(self.view.bounds.size.height * self.view.contentScaleFactor,
														self.view.bounds.size.width * self.view.contentScaleFactor);
	NSLog(@"screen size = %.4f x %.4f", self.view.bounds.size.width, self.view.bounds.size.height);
	NSLog(@"scale factor = %.4f", self.view.contentScaleFactor);
	
	IGraphicsEngine *graphicsEngine = GraphicsEngineFactory::Create();
	m_game = InfectedBunniesFactory::Create(graphicsEngine);
	m_game->Initialize(NULL);
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
	
	[self InitializeGame];
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
	m_game->Update(self.timeSinceFirstResume, self.timeSinceLastUpdate);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	m_game->Draw(self.timeSinceFirstResume, self.timeSinceLastUpdate);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{	
	[super touchesBegan:touches withEvent:event];
	
	for (UITouch* touch in touches)
	{
		CGPoint location = [touch locationInView:[self view]];
		location.x *= [self view].contentScaleFactor;
		location.y *= [self view].contentScaleFactor;
		
		m_game->HandlePress(reinterpret_cast<uint32_t>(touch), sm::Vec2(location.x, location.y));
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	[super touchesMoved:touches withEvent:event];
	
	for (UITouch* touch in touches)
	{
		CGPoint location = [touch locationInView:[self view]];
		location.x *= [self view].contentScaleFactor;
		location.y *= [self view].contentScaleFactor;
		
		m_game->HandleMove(reinterpret_cast<uint32_t>(touch), sm::Vec2(location.x, location.y));
	}
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	[super touchesEnded:touches withEvent:event];
	
	for (UITouch* touch in touches)
	{
		CGPoint location = [touch locationInView:[self view]];
		location.x *= [self view].contentScaleFactor;
		location.y *= [self view].contentScaleFactor;
		
		m_game->HandleRelease(reinterpret_cast<uint32_t>(touch), sm::Vec2(location.x, location.y));
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	[super touchesCancelled:touches withEvent:event];
	
	for (UITouch* touch in touches)
	{
		CGPoint location = [touch locationInView:[self view]];
		location.x *= [self view].contentScaleFactor;
		location.y *= [self view].contentScaleFactor;
		
		m_game->HandleRelease(reinterpret_cast<uint32_t>(touch), sm::Vec2(location.x, location.y));
	}
}


@end
