#define FFI_LIB "/System/Library/Frameworks/ApplicationServices.framework/Frameworks/SpeechSynthesis.framework/Versions/Current/SpeechSynthesis"
#define kCFStringEncodingUTF8 0x08000100
typedef int OSStatus;
typedef int Fixed; // Fixed-point 16.16

typedef const void *CFTypeRef;
typedef CFTypeRef CFStringRef;
typedef const void *CFAllocatorRef;
typedef unsigned int CFStringEncoding;



typedef struct OpaqueSpeechChannel *SpeechChannel;

OSStatus NewSpeechChannel(void *refCon, SpeechChannel *chan);
OSStatus SpeakCFString(SpeechChannel chan, CFStringRef text, void *options);
OSStatus SetSpeechRate(SpeechChannel chan, Fixed rate);
OSStatus SetSpeechPitch(SpeechChannel chan, short pitch);
int SpeechBusy();
CFStringRef CFStringCreateWithCString(CFAllocatorRef alloc, const char *cStr, CFStringEncoding encoding);
