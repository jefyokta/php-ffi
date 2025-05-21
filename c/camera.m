#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AppKit/AppKit.h>  
#import "camera.h"

@interface CaptureDelegate : NSObject <AVCapturePhotoCaptureDelegate>
@property (nonatomic, strong) NSData *imageData;
@property (nonatomic, strong) dispatch_semaphore_t semaphore;
@end

@implementation CaptureDelegate
- (instancetype)init {
    if (self = [super init]) {
        _semaphore = dispatch_semaphore_create(0);
    }
    return self;
}

- (void)captureOutput:(AVCapturePhotoOutput *)output
didFinishProcessingPhoto:(AVCapturePhoto *)photo
                error:(NSError *)error {
    if (error == nil) {
        self.imageData = [photo fileDataRepresentation];
    } else {
        NSLog(@"Error capturing photo: %@", error);
    }
    dispatch_semaphore_signal(self.semaphore);
}
@end

void capture_image(const char *output_path) {
    @autoreleasepool {
        (void)NSApplicationLoad();

        NSString *filename = [NSString stringWithUTF8String:output_path];

        AVCaptureSession *session = [[AVCaptureSession alloc] init];
        AVCaptureDevice *device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
        NSError *error = nil;
        AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:device error:&error];
        if (error || !input) {
            NSLog(@"Failed to create AVCaptureDeviceInput: %@", error);
            return;
        }
        if ([session canAddInput:input]) {
            [session addInput:input];
        }

        AVCapturePhotoOutput *photoOutput = [[AVCapturePhotoOutput alloc] init];
        if ([session canAddOutput:photoOutput]) {
            [session addOutput:photoOutput];
        }

        [session startRunning];

        // Jalankan runloop sebentar untuk stabilisasi session
        [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.5]];

        CaptureDelegate *delegate = [[CaptureDelegate alloc] init];
        AVCapturePhotoSettings *settings = [AVCapturePhotoSettings photoSettings];

        [photoOutput capturePhotoWithSettings:settings delegate:delegate];

        // Run loop lagi selama capture selesai
        while (dispatch_semaphore_wait(delegate.semaphore, DISPATCH_TIME_NOW)) {
            [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate dateWithTimeIntervalSinceNow:0.1]];
        }

        BOOL success = [delegate.imageData writeToFile:filename atomically:YES];
        if (!success) {
            NSLog(@"Failed to write image to %@", filename);
        }

        [session stopRunning];
    }
}
