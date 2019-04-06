////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2019 Marco Antognini (antognini.marco@gmail.com),
//                         Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Window/OSX/HIDInputManager.hpp>
#include <System/Err.hpp>
#include <AppKit/AppKit.h>

namespace tinySFML
{
namespace priv
{
////////////////////////////////////////////////////////////
HIDInputManager& HIDInputManager::getInstance()
{
    static HIDInputManager instance;
    return instance;
}


////////////////////////////////////////////////////////////
bool HIDInputManager::isKeyPressed(Keyboard::Key key)
{
    return isPressed(m_keys[key]);
}


////////////////////////////////////////////////////////////
long HIDInputManager::getLocationID(IOHIDDeviceRef device)
{
    long loc = 0;

    // Get a unique ID: its USB location ID
    CFTypeRef typeRef = IOHIDDeviceGetProperty(device,
                                               CFSTR(kIOHIDLocationIDKey));
    if (!typeRef || (CFGetTypeID(typeRef) != CFNumberGetTypeID()))
        return 0;

    CFNumberRef locRef = (CFNumberRef)typeRef;

    if (!CFNumberGetValue(locRef, kCFNumberLongType, &loc))
        return 0;

    return loc;
}


////////////////////////////////////////////////////////////
CFDictionaryRef HIDInputManager::copyDevicesMask(UInt32 page, UInt32 usage)
{
    // Create the dictionary.
    CFMutableDictionaryRef dict = CFDictionaryCreateMutable(kCFAllocatorDefault, 2,
                                                            &kCFTypeDictionaryKeyCallBacks,
                                                            &kCFTypeDictionaryValueCallBacks);

    // Add the page value.
    CFNumberRef value = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &page);
    CFDictionarySetValue(dict, CFSTR(kIOHIDDeviceUsagePageKey), value);
    CFRelease(value);

    // Add the usage value (which is only valid if page value exists).
    value = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usage);
    CFDictionarySetValue(dict, CFSTR(kIOHIDDeviceUsageKey), value);
    CFRelease(value);

    return dict;
}


////////////////////////////////////////////////////////////
HIDInputManager::HIDInputManager() :
m_isValid(true),
m_layoutData(0),
m_layout(0),
m_manager(0)
{
    // Get the current keyboard layout
    TISInputSourceRef tis = TISCopyCurrentKeyboardLayoutInputSource();
    m_layoutData = (CFDataRef)TISGetInputSourceProperty(tis,
                                                        kTISPropertyUnicodeKeyLayoutData);

    if (m_layoutData == 0)
    {
        tinySFML::err() << "Cannot get the keyboard layout" << std::endl;
        freeUp();
        return;
    }

    // Keep a reference for ourself
    CFRetain(m_layoutData);
    m_layout = (UCKeyboardLayout *)CFDataGetBytePtr(m_layoutData);

    // The TIS is no more needed
    CFRelease(tis);

    // Create an HID Manager reference
    m_manager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);

    // Open the HID Manager reference
    IOReturn openStatus = IOHIDManagerOpen(m_manager, kIOHIDOptionsTypeNone);

    if (openStatus != kIOReturnSuccess)
    {
        tinySFML::err() << "Error when opening the HID manager" << std::endl;
        freeUp();
        return;
    }

    // Initialize the keyboard
    initializeKeyboard();
}


////////////////////////////////////////////////////////////
HIDInputManager::~HIDInputManager()
{
    freeUp();
}


void HIDInputManager::initializeKeyboard()
{
    ////////////////////////////////////////////////////////////
    // The purpose of this function is to initialize m_keys so we can get
    // the associate IOHIDElementRef with a tinySFML::Keyboard::Key in ~constant~ time.

    // Get only keyboards
    CFSetRef keyboards = copyDevices(kHIDPage_GenericDesktop, kHIDUsage_GD_Keyboard);
    if (keyboards == NULL)
    {
        tinySFML::err() << "No keyboard detected by the HID manager!" << std::endl;
        freeUp();
        return;
    }

    CFIndex keyboardCount = CFSetGetCount(keyboards); // >= 1 (asserted by copyDevices)

    // Get an iterable array
    CFTypeRef devicesArray[keyboardCount];
    CFSetGetValues(keyboards, devicesArray);

    for (CFIndex i = 0; i < keyboardCount; ++i)
    {
        IOHIDDeviceRef keyboard = (IOHIDDeviceRef)devicesArray[i];
        loadKeyboard(keyboard);
    }

    // Release unused stuff
    CFRelease(keyboards);

    ////////////////////////////////////////////////////////////
    // At this point m_keys is filled with as many IOHIDElementRef as possible
}


////////////////////////////////////////////////////////////
void HIDInputManager::loadKeyboard(IOHIDDeviceRef keyboard)
{
    CFArrayRef keys = IOHIDDeviceCopyMatchingElements(keyboard,
                                                      NULL,
                                                      kIOHIDOptionsTypeNone);
    if (keys == NULL)
    {
        tinySFML::err() << "We got a keyboard without any keys (1)" << std::endl;
        return;
    }

    // How many elements are there?
    CFIndex keysCount = CFArrayGetCount(keys);

    if (keysCount == 0)
    {
        tinySFML::err() << "We got a keyboard without any keys (2)" << std::endl;
        CFRelease(keys);
        return;
    }

    // Go through all connected elements.
    for (CFIndex i = 0; i < keysCount; ++i)
    {
        IOHIDElementRef aKey = (IOHIDElementRef) CFArrayGetValueAtIndex(keys, i);

        // Skip non-matching keys elements
        if (IOHIDElementGetUsagePage(aKey) != kHIDPage_KeyboardOrKeypad)
            continue;

        loadKey(aKey);
    }

    // Release unused stuff
    CFRelease(keys);
}


////////////////////////////////////////////////////////////
void HIDInputManager::loadKey(IOHIDElementRef key)
{
    // Get its virtual code
    UInt32 usageCode   = IOHIDElementGetUsage(key);
    UInt8  virtualCode = usageToVirtualCode(usageCode);

    if (virtualCode == 0xff)
        return; // no corresponding virtual code -> skip

    // Now translate the virtual code to Unicode according to
    // the current keyboard layout

    UInt32       deadKeyState = 0;
    // Unicode string length is usually less or equal to 4
    UniCharCount maxStringLength = 4;
    UniCharCount actualStringLength = 0;
    UniChar      unicodeString[maxStringLength];

    OSStatus     error;

    error = UCKeyTranslate(m_layout,                    // current layout
                           virtualCode,                 // our key
                           kUCKeyActionDown,            // or kUCKeyActionUp ?
                           0x100,                       // no modifiers
                           LMGetKbdType(),              // keyboard's type
                           kUCKeyTranslateNoDeadKeysBit,// some sort of option
                           &deadKeyState,               // unused stuff
                           maxStringLength,             // our memory limit
                           &actualStringLength,         // length of what we get
                           unicodeString);              // what we get

    if (error == noErr)
    {
        // Translation went fine

        // The corresponding SFML key code
        Keyboard::Key code = Keyboard::Unknown; // KeyCound means 'none'

        // First we look if the key down is from a list of characters
        // that depend on keyboard localization
        if (actualStringLength > 0)
            code = localizedKeys(unicodeString[0]);

        // The key is not a localized one so we try to find a
        // corresponding code through virtual key code
        if (code == Keyboard::Unknown)
            code = nonLocalizedKeys(virtualCode);

        // A code was found, wonderful!
        if (code != Keyboard::Unknown)
        {
            // Ok, everything went fine. Now we have a unique
            // corresponding tinySFML::Keyboard::Key to one IOHIDElementRef
            m_keys[code].push_back(key);

            // And don't forget to keep the reference alive for our usage
            CFRetain(m_keys[code].back());
        }

        ////////////////////////////////////////////////////////////
        // These are known to be unbound:
        //    Supposed Virtual | HID  | Supposed Key
        //    ===============================================
        //          0x1b       | 0x2d | Hyphen
        //          0x39       | 0x39 | CapsLock
        //          0x47       | 0x53 | NumLock
        //          0x6e       | 0x65 | Application
        //          0x4c       | 0x77 | Select

        //if (code == Keyboard::Unknown) { // The key is unknown.
        //    tinySFML::err() << "This is an unknown key. Virtual key code is 0x"
        //              << std::hex
        //              << (UInt32)virtualCode
        //              << " and HID usage code is 0x"
        //              << usageCode
        //              << std::dec
        //              << "."
        //              << std::endl;
        //}

    } /* if (error == noErr) */
    else
    {
        tinySFML::err() << "Cannot translate the virtual key code, error: "
                  << error
                  << std::endl;
    }
}


////////////////////////////////////////////////////////////
void HIDInputManager::freeUp()
{
    m_isValid = false;

    if (m_layoutData != 0)
        CFRelease(m_layoutData);
    m_layoutData = 0;
    // Do not release m_layout! It is owned by m_layoutData.
    if (m_manager != 0)
        CFRelease(m_manager);
    m_manager = 0;

    for (unsigned int i = 0; i < Keyboard::KeyCount; ++i)
    {
        for (IOHIDElements::iterator it = m_keys[i].begin(); it != m_keys[i].end(); ++it)
            CFRelease(*it);

        m_keys[i].clear();
    }
}


////////////////////////////////////////////////////////////
CFSetRef HIDInputManager::copyDevices(UInt32 page, UInt32 usage)
{
    // Filter and keep only the requested devices
    CFDictionaryRef mask = copyDevicesMask(page, usage);

    IOHIDManagerSetDeviceMatching(m_manager, mask);

    CFRelease(mask);
    mask = 0;

    CFSetRef devices = IOHIDManagerCopyDevices(m_manager);
    if (devices == NULL)
        return NULL;

    // Is there at least one device?
    CFIndex deviceCount = CFSetGetCount(devices);
    if (deviceCount < 1)
    {
        CFRelease(devices);
        return NULL;
    }

    return devices;
}

bool HIDInputManager::isPressed(IOHIDElements& elements)
{
    if (!m_isValid) 
        return false;

    // state = true if at least one corresponding HID button is pressed
    bool state = false;

    for (IOHIDElements::iterator it = elements.begin(); it != elements.end(); /* noop */)
    {
        IOHIDValueRef value = 0;

        IOHIDDeviceRef device = IOHIDElementGetDevice(*it);
        IOHIDDeviceGetValue(device, *it, &value);

        if (!value)
        {
            // This means some kind of error / disconnection so we remove this
            // element from our buttons
            CFRelease(*it);
            it = elements.erase(it);
        }
        else if (IOHIDValueGetIntegerValue(value) == 1)
        {
            // This means the button is pressed
            state = true;
            break; // Stop here
        }
        else
        {
            // This means the button is released
            ++it;
        }
    }

    return state;
}


////////////////////////////////////////////////////////////
UInt8 HIDInputManager::usageToVirtualCode(UInt32 usage)
{
    // Some usage key doesn't have any corresponding virtual
    // code or it was not found (return 0xff).
    switch (usage)
    {
        case kHIDUsage_KeyboardErrorRollOver:       return 0xff;
        case kHIDUsage_KeyboardPOSTFail:            return 0xff;
        case kHIDUsage_KeyboardErrorUndefined:      return 0xff;

        case kHIDUsage_KeyboardA:                   return 0x00;
        case kHIDUsage_KeyboardB:                   return 0x0b;
        case kHIDUsage_KeyboardC:                   return 0x08;
        case kHIDUsage_KeyboardD:                   return 0x02;
        case kHIDUsage_KeyboardE:                   return 0x0e;
        case kHIDUsage_KeyboardF:                   return 0x03;
        case kHIDUsage_KeyboardG:                   return 0x05;
        case kHIDUsage_KeyboardH:                   return 0x04;
        case kHIDUsage_KeyboardI:                   return 0x22;
        case kHIDUsage_KeyboardJ:                   return 0x26;
        case kHIDUsage_KeyboardK:                   return 0x28;
        case kHIDUsage_KeyboardL:                   return 0x25;
        case kHIDUsage_KeyboardM:                   return 0x2e;
        case kHIDUsage_KeyboardN:                   return 0x2d;
        case kHIDUsage_KeyboardO:                   return 0x1f;
        case kHIDUsage_KeyboardP:                   return 0x23;
        case kHIDUsage_KeyboardQ:                   return 0x0c;
        case kHIDUsage_KeyboardR:                   return 0x0f;
        case kHIDUsage_KeyboardS:                   return 0x01;
        case kHIDUsage_KeyboardT:                   return 0x11;
        case kHIDUsage_KeyboardU:                   return 0x20;
        case kHIDUsage_KeyboardV:                   return 0x09;
        case kHIDUsage_KeyboardW:                   return 0x0d;
        case kHIDUsage_KeyboardX:                   return 0x07;
        case kHIDUsage_KeyboardY:                   return 0x10;
        case kHIDUsage_KeyboardZ:                   return 0x06;

        case kHIDUsage_Keyboard1:                   return 0x12;
        case kHIDUsage_Keyboard2:                   return 0x13;
        case kHIDUsage_Keyboard3:                   return 0x14;
        case kHIDUsage_Keyboard4:                   return 0x15;
        case kHIDUsage_Keyboard5:                   return 0x17;
        case kHIDUsage_Keyboard6:                   return 0x16;
        case kHIDUsage_Keyboard7:                   return 0x1a;
        case kHIDUsage_Keyboard8:                   return 0x1c;
        case kHIDUsage_Keyboard9:                   return 0x19;
        case kHIDUsage_Keyboard0:                   return 0x1d;

        case kHIDUsage_KeyboardReturnOrEnter:       return 0x24;
        case kHIDUsage_KeyboardEscape:              return 0x35;
        case kHIDUsage_KeyboardDeleteOrBackspace:   return 0x33;
        case kHIDUsage_KeyboardTab:                 return 0x30;
        case kHIDUsage_KeyboardSpacebar:            return 0x31;
        case kHIDUsage_KeyboardHyphen:              return 0x1b;
        case kHIDUsage_KeyboardEqualSign:           return 0x18;
        case kHIDUsage_KeyboardOpenBracket:         return 0x21;
        case kHIDUsage_KeyboardCloseBracket:        return 0x1e;
        case kHIDUsage_KeyboardBackslash:           return 0x2a;
        case kHIDUsage_KeyboardNonUSPound:          return 0xff;
        case kHIDUsage_KeyboardSemicolon:           return 0x29;
        case kHIDUsage_KeyboardQuote:               return 0x27;
        case kHIDUsage_KeyboardGraveAccentAndTilde: return 0x32;
        case kHIDUsage_KeyboardComma:               return 0x2b;
        case kHIDUsage_KeyboardPeriod:              return 0x2F;
        case kHIDUsage_KeyboardSlash:               return 0x2c;
        case kHIDUsage_KeyboardCapsLock:            return 0x39;

        case kHIDUsage_KeyboardF1:                  return 0x7a;
        case kHIDUsage_KeyboardF2:                  return 0x78;
        case kHIDUsage_KeyboardF3:                  return 0x63;
        case kHIDUsage_KeyboardF4:                  return 0x76;
        case kHIDUsage_KeyboardF5:                  return 0x60;
        case kHIDUsage_KeyboardF6:                  return 0x61;
        case kHIDUsage_KeyboardF7:                  return 0x62;
        case kHIDUsage_KeyboardF8:                  return 0x64;
        case kHIDUsage_KeyboardF9:                  return 0x65;
        case kHIDUsage_KeyboardF10:                 return 0x6d;
        case kHIDUsage_KeyboardF11:                 return 0x67;
        case kHIDUsage_KeyboardF12:                 return 0x6f;

        case kHIDUsage_KeyboardPrintScreen:         return 0xff;
        case kHIDUsage_KeyboardScrollLock:          return 0xff;
        case kHIDUsage_KeyboardPause:               return 0xff;
        case kHIDUsage_KeyboardInsert:              return 0x72;
        case kHIDUsage_KeyboardHome:                return 0x73;
        case kHIDUsage_KeyboardPageUp:              return 0x74;
        case kHIDUsage_KeyboardDeleteForward:       return 0x75;
        case kHIDUsage_KeyboardEnd:                 return 0x77;
        case kHIDUsage_KeyboardPageDown:            return 0x79;

        case kHIDUsage_KeyboardRightArrow:          return 0x7c;
        case kHIDUsage_KeyboardLeftArrow:           return 0x7b;
        case kHIDUsage_KeyboardDownArrow:           return 0x7d;
        case kHIDUsage_KeyboardUpArrow:             return 0x7e;

        case kHIDUsage_KeypadNumLock:               return 0x47;
        case kHIDUsage_KeypadSlash:                 return 0x4b;
        case kHIDUsage_KeypadAsterisk:              return 0x43;
        case kHIDUsage_KeypadHyphen:                return 0x4e;
        case kHIDUsage_KeypadPlus:                  return 0x45;
        case kHIDUsage_KeypadEnter:                 return 0x4c;

        case kHIDUsage_Keypad1:                     return 0x53;
        case kHIDUsage_Keypad2:                     return 0x54;
        case kHIDUsage_Keypad3:                     return 0x55;
        case kHIDUsage_Keypad4:                     return 0x56;
        case kHIDUsage_Keypad5:                     return 0x57;
        case kHIDUsage_Keypad6:                     return 0x58;
        case kHIDUsage_Keypad7:                     return 0x59;
        case kHIDUsage_Keypad8:                     return 0x5b;
        case kHIDUsage_Keypad9:                     return 0x5c;
        case kHIDUsage_Keypad0:                     return 0x52;

        case kHIDUsage_KeypadPeriod:                return 0x41;
        case kHIDUsage_KeyboardNonUSBackslash:      return 0xff;
        case kHIDUsage_KeyboardApplication:         return 0x6e;
        case kHIDUsage_KeyboardPower:               return 0xff;
        case kHIDUsage_KeypadEqualSign:             return 0x51;

        case kHIDUsage_KeyboardF13:                 return 0x69;
        case kHIDUsage_KeyboardF14:                 return 0x6b;
        case kHIDUsage_KeyboardF15:                 return 0x71;
        case kHIDUsage_KeyboardF16:                 return 0xff;
        case kHIDUsage_KeyboardF17:                 return 0xff;
        case kHIDUsage_KeyboardF18:                 return 0xff;
        case kHIDUsage_KeyboardF19:                 return 0xff;
        case kHIDUsage_KeyboardF20:                 return 0xff;
        case kHIDUsage_KeyboardF21:                 return 0xff;
        case kHIDUsage_KeyboardF22:                 return 0xff;
        case kHIDUsage_KeyboardF23:                 return 0xff;
        case kHIDUsage_KeyboardF24:                 return 0xff;

        case kHIDUsage_KeyboardExecute:             return 0xff;
        case kHIDUsage_KeyboardHelp:                return 0xff;
        case kHIDUsage_KeyboardMenu:                return 0x7F;
        case kHIDUsage_KeyboardSelect:              return 0x4c;
        case kHIDUsage_KeyboardStop:                return 0xff;
        case kHIDUsage_KeyboardAgain:               return 0xff;
        case kHIDUsage_KeyboardUndo:                return 0xff;
        case kHIDUsage_KeyboardCut:                 return 0xff;
        case kHIDUsage_KeyboardCopy:                return 0xff;
        case kHIDUsage_KeyboardPaste:               return 0xff;
        case kHIDUsage_KeyboardFind:                return 0xff;

        case kHIDUsage_KeyboardMute:                return 0xff;
        case kHIDUsage_KeyboardVolumeUp:            return 0xff;
        case kHIDUsage_KeyboardVolumeDown:          return 0xff;

        case kHIDUsage_KeyboardLockingCapsLock:     return 0xff;
        case kHIDUsage_KeyboardLockingNumLock:      return 0xff;
        case kHIDUsage_KeyboardLockingScrollLock:   return 0xff;

        case kHIDUsage_KeypadComma:                 return 0xff;
        case kHIDUsage_KeypadEqualSignAS400:        return 0xff;
        case kHIDUsage_KeyboardInternational1:      return 0xff;
        case kHIDUsage_KeyboardInternational2:      return 0xff;
        case kHIDUsage_KeyboardInternational3:      return 0xff;
        case kHIDUsage_KeyboardInternational4:      return 0xff;
        case kHIDUsage_KeyboardInternational5:      return 0xff;
        case kHIDUsage_KeyboardInternational6:      return 0xff;
        case kHIDUsage_KeyboardInternational7:      return 0xff;
        case kHIDUsage_KeyboardInternational8:      return 0xff;
        case kHIDUsage_KeyboardInternational9:      return 0xff;

        case kHIDUsage_KeyboardLANG1:               return 0xff;
        case kHIDUsage_KeyboardLANG2:               return 0xff;
        case kHIDUsage_KeyboardLANG3:               return 0xff;
        case kHIDUsage_KeyboardLANG4:               return 0xff;
        case kHIDUsage_KeyboardLANG5:               return 0xff;
        case kHIDUsage_KeyboardLANG6:               return 0xff;
        case kHIDUsage_KeyboardLANG7:               return 0xff;
        case kHIDUsage_KeyboardLANG8:               return 0xff;
        case kHIDUsage_KeyboardLANG9:               return 0xff;

        case kHIDUsage_KeyboardAlternateErase:      return 0xff;
        case kHIDUsage_KeyboardSysReqOrAttention:   return 0xff;
        case kHIDUsage_KeyboardCancel:              return 0xff;
        case kHIDUsage_KeyboardClear:               return 0xff;
        case kHIDUsage_KeyboardPrior:               return 0xff;
        case kHIDUsage_KeyboardReturn:              return 0xff;
        case kHIDUsage_KeyboardSeparator:           return 0xff;
        case kHIDUsage_KeyboardOut:                 return 0xff;
        case kHIDUsage_KeyboardOper:                return 0xff;
        case kHIDUsage_KeyboardClearOrAgain:        return 0xff;
        case kHIDUsage_KeyboardCrSelOrProps:        return 0xff;
        case kHIDUsage_KeyboardExSel:               return 0xff;

            /* 0xa5-0xdf Reserved */

        case kHIDUsage_KeyboardLeftControl:         return 0x3b;
        case kHIDUsage_KeyboardLeftShift:           return 0x38;
        case kHIDUsage_KeyboardLeftAlt:             return 0x3a;
        case kHIDUsage_KeyboardLeftGUI:             return 0x37;
        case kHIDUsage_KeyboardRightControl:        return 0x3e;
        case kHIDUsage_KeyboardRightShift:          return 0x3c;
        case kHIDUsage_KeyboardRightAlt:            return 0x3d;
        case kHIDUsage_KeyboardRightGUI:            return 0x36;

            /* 0xe8-0xffff Reserved */

        case kHIDUsage_Keyboard_Reserved:           return 0xff;
        default:                                    return 0xff;
    }
}


////////////////////////////////////////////////////////
Keyboard::Key HIDInputManager::localizedKeys(UniChar ch)
{
    switch (ch)
    {
        case 'a':
        case 'A':                   return tinySFML::Keyboard::A;

        case 'b':
        case 'B':                   return tinySFML::Keyboard::B;

        case 'c':
        case 'C':                   return tinySFML::Keyboard::C;

        case 'd':
        case 'D':                   return tinySFML::Keyboard::D;

        case 'e':
        case 'E':                   return tinySFML::Keyboard::E;

        case 'f':
        case 'F':                   return tinySFML::Keyboard::F;

        case 'g':
        case 'G':                   return tinySFML::Keyboard::G;

        case 'h':
        case 'H':                   return tinySFML::Keyboard::H;

        case 'i':
        case 'I':                   return tinySFML::Keyboard::I;

        case 'j':
        case 'J':                   return tinySFML::Keyboard::J;

        case 'k':
        case 'K':                   return tinySFML::Keyboard::K;

        case 'l':
        case 'L':                   return tinySFML::Keyboard::L;

        case 'm':
        case 'M':                   return tinySFML::Keyboard::M;

        case 'n':
        case 'N':                   return tinySFML::Keyboard::N;

        case 'o':
        case 'O':                   return tinySFML::Keyboard::O;

        case 'p':
        case 'P':                   return tinySFML::Keyboard::P;

        case 'q':
        case 'Q':                   return tinySFML::Keyboard::Q;

        case 'r':
        case 'R':                   return tinySFML::Keyboard::R;

        case 's':
        case 'S':                   return tinySFML::Keyboard::S;

        case 't':
        case 'T':                   return tinySFML::Keyboard::T;

        case 'u':
        case 'U':                   return tinySFML::Keyboard::U;

        case 'v':
        case 'V':                   return tinySFML::Keyboard::V;

        case 'w':
        case 'W':                   return tinySFML::Keyboard::W;

        case 'x':
        case 'X':                   return tinySFML::Keyboard::X;

        case 'y':
        case 'Y':                   return tinySFML::Keyboard::Y;

        case 'z':
        case 'Z':                   return tinySFML::Keyboard::Z;

            // The key is not 'localized'.
        default:                    return tinySFML::Keyboard::Unknown;
    }
}


////////////////////////////////////////////////////////
Keyboard::Key HIDInputManager::nonLocalizedKeys(UniChar virtualKeycode)
{
    // (Some) 0x code based on https://forums.macrumors.com/showthread.php?t=780577
    // Some tinySFML::Keyboard::Key are present twice.
    switch (virtualKeycode)
    {
            // These cases should not be used but anyway...
        case 0x00:                      return tinySFML::Keyboard::A;
        case 0x0b:                      return tinySFML::Keyboard::B;
        case 0x08:                      return tinySFML::Keyboard::C;
        case 0x02:                      return tinySFML::Keyboard::D;
        case 0x0e:                      return tinySFML::Keyboard::E;
        case 0x03:                      return tinySFML::Keyboard::F;
        case 0x05:                      return tinySFML::Keyboard::G;
        case 0x04:                      return tinySFML::Keyboard::H;
        case 0x22:                      return tinySFML::Keyboard::I;
        case 0x26:                      return tinySFML::Keyboard::J;
        case 0x28:                      return tinySFML::Keyboard::K;
        case 0x25:                      return tinySFML::Keyboard::L;
        case 0x2e:                      return tinySFML::Keyboard::M;
        case 0x2d:                      return tinySFML::Keyboard::N;
        case 0x1f:                      return tinySFML::Keyboard::O;
        case 0x23:                      return tinySFML::Keyboard::P;
        case 0x0c:                      return tinySFML::Keyboard::Q;
        case 0x0f:                      return tinySFML::Keyboard::R;
        case 0x01:                      return tinySFML::Keyboard::S;
        case 0x11:                      return tinySFML::Keyboard::T;
        case 0x20:                      return tinySFML::Keyboard::U;
        case 0x09:                      return tinySFML::Keyboard::V;
        case 0x0d:                      return tinySFML::Keyboard::W;
        case 0x07:                      return tinySFML::Keyboard::X;
        case 0x10:                      return tinySFML::Keyboard::Y;
        case 0x06:                      return tinySFML::Keyboard::Z;

            // These cases should not be used but anyway...
        case 0x1d:                      return tinySFML::Keyboard::Num0;
        case 0x12:                      return tinySFML::Keyboard::Num1;
        case 0x13:                      return tinySFML::Keyboard::Num2;
        case 0x14:                      return tinySFML::Keyboard::Num3;
        case 0x15:                      return tinySFML::Keyboard::Num4;
        case 0x17:                      return tinySFML::Keyboard::Num5;
        case 0x16:                      return tinySFML::Keyboard::Num6;
        case 0x1a:                      return tinySFML::Keyboard::Num7;
        case 0x1c:                      return tinySFML::Keyboard::Num8;
        case 0x19:                      return tinySFML::Keyboard::Num9;

        case 0x35:                      return tinySFML::Keyboard::Escape;

            // Modifier keys : never happen with keyDown/keyUp methods (?)
        case 0x3b:                      return tinySFML::Keyboard::LControl;
        case 0x38:                      return tinySFML::Keyboard::LShift;
        case 0x3a:                      return tinySFML::Keyboard::LAlt;
        case 0x37:                      return tinySFML::Keyboard::LSystem;
        case 0x3e:                      return tinySFML::Keyboard::RControl;
        case 0x3c:                      return tinySFML::Keyboard::RShift;
        case 0x3d:                      return tinySFML::Keyboard::RAlt;
        case 0x36:                      return tinySFML::Keyboard::RSystem;

        case 0x7f:                      return tinySFML::Keyboard::Menu;
        case NSMenuFunctionKey:         return tinySFML::Keyboard::Menu;

        case 0x21:                      return tinySFML::Keyboard::LBracket;
        case 0x1e:                      return tinySFML::Keyboard::RBracket;
        case 0x29:                      return tinySFML::Keyboard::Semicolon;
        case 0x2b:                      return tinySFML::Keyboard::Comma;
        case 0x41: /* keypad         */ return tinySFML::Keyboard::Period;
        case 0x2f: /* keyboard       */ return tinySFML::Keyboard::Period;
        case 0x27:                      return tinySFML::Keyboard::Quote;
        case 0x2c:                      return tinySFML::Keyboard::Slash;
        case 0x2a:                      return tinySFML::Keyboard::Backslash;

            // tinySFML::Keyboard::Tilde might be in conflict with some other key.
            // 0x0a is for "Non-US Backslash" according to HID Calibrator,
            // a sample provided by Apple.
        case 0x0a:                      return tinySFML::Keyboard::Tilde;

        case 0x51: /* keypad         */ return tinySFML::Keyboard::Equal;
        case 0x18: /* keyboard       */ return tinySFML::Keyboard::Equal;
        case 0x32:                      return tinySFML::Keyboard::Hyphen;
        case 0x31:                      return tinySFML::Keyboard::Space;
        case 0x4c: /* keypad         */ return tinySFML::Keyboard::Enter;
        case 0x24: /* keyboard       */ return tinySFML::Keyboard::Enter;
        case 0x33:                      return tinySFML::Keyboard::Backspace;
        case 0x30:                      return tinySFML::Keyboard::Tab;

            // Duplicates (see next section).
        case 0x74:                      return tinySFML::Keyboard::PageUp;
        case 0x79:                      return tinySFML::Keyboard::PageDown;
        case 0x77:                      return tinySFML::Keyboard::End;
        case 0x73:                      return tinySFML::Keyboard::Home;

        case NSPageUpFunctionKey:       return tinySFML::Keyboard::PageUp;
        case NSPageDownFunctionKey:     return tinySFML::Keyboard::PageDown;
        case NSEndFunctionKey:          return tinySFML::Keyboard::End;
        case NSHomeFunctionKey:         return tinySFML::Keyboard::Home;

        case 0x72:                      return tinySFML::Keyboard::Insert;
        case NSInsertFunctionKey:       return tinySFML::Keyboard::Insert;
        case 0x75:                      return tinySFML::Keyboard::Delete;
        case NSDeleteFunctionKey:       return tinySFML::Keyboard::Delete;

        case 0x45:                      return tinySFML::Keyboard::Add;
        case 0x4e:                      return tinySFML::Keyboard::Subtract;
        case 0x43:                      return tinySFML::Keyboard::Multiply;
        case 0x4b:                      return tinySFML::Keyboard::Divide;

            // Duplicates (see next section).
        case 0x7b:                      return tinySFML::Keyboard::Left;
        case 0x7c:                      return tinySFML::Keyboard::Right;
        case 0x7e:                      return tinySFML::Keyboard::Up;
        case 0x7d:                      return tinySFML::Keyboard::Down;

        case NSLeftArrowFunctionKey:    return tinySFML::Keyboard::Left;
        case NSRightArrowFunctionKey:   return tinySFML::Keyboard::Right;
        case NSUpArrowFunctionKey:      return tinySFML::Keyboard::Up;
        case NSDownArrowFunctionKey:    return tinySFML::Keyboard::Down;

        case 0x52:                      return tinySFML::Keyboard::Numpad0;
        case 0x53:                      return tinySFML::Keyboard::Numpad1;
        case 0x54:                      return tinySFML::Keyboard::Numpad2;
        case 0x55:                      return tinySFML::Keyboard::Numpad3;
        case 0x56:                      return tinySFML::Keyboard::Numpad4;
        case 0x57:                      return tinySFML::Keyboard::Numpad5;
        case 0x58:                      return tinySFML::Keyboard::Numpad6;
        case 0x59:                      return tinySFML::Keyboard::Numpad7;
        case 0x5b:                      return tinySFML::Keyboard::Numpad8;
        case 0x5c:                      return tinySFML::Keyboard::Numpad9;

            // Duplicates (see next section).
        case 0x7a:                      return tinySFML::Keyboard::F1;
        case 0x78:                      return tinySFML::Keyboard::F2;
        case 0x63:                      return tinySFML::Keyboard::F3;
        case 0x76:                      return tinySFML::Keyboard::F4;
        case 0x60:                      return tinySFML::Keyboard::F5;
        case 0x61:                      return tinySFML::Keyboard::F6;
        case 0x62:                      return tinySFML::Keyboard::F7;
        case 0x64:                      return tinySFML::Keyboard::F8;
        case 0x65:                      return tinySFML::Keyboard::F9;
        case 0x6d:                      return tinySFML::Keyboard::F10;
        case 0x67:                      return tinySFML::Keyboard::F11;
        case 0x6f:                      return tinySFML::Keyboard::F12;
        case 0x69:                      return tinySFML::Keyboard::F13;
        case 0x6b:                      return tinySFML::Keyboard::F14;
        case 0x71:                      return tinySFML::Keyboard::F15;

        case NSF1FunctionKey:           return tinySFML::Keyboard::F1;
        case NSF2FunctionKey:           return tinySFML::Keyboard::F2;
        case NSF3FunctionKey:           return tinySFML::Keyboard::F3;
        case NSF4FunctionKey:           return tinySFML::Keyboard::F4;
        case NSF5FunctionKey:           return tinySFML::Keyboard::F5;
        case NSF6FunctionKey:           return tinySFML::Keyboard::F6;
        case NSF7FunctionKey:           return tinySFML::Keyboard::F7;
        case NSF8FunctionKey:           return tinySFML::Keyboard::F8;
        case NSF9FunctionKey:           return tinySFML::Keyboard::F9;
        case NSF10FunctionKey:          return tinySFML::Keyboard::F10;
        case NSF11FunctionKey:          return tinySFML::Keyboard::F11;
        case NSF12FunctionKey:          return tinySFML::Keyboard::F12;
        case NSF13FunctionKey:          return tinySFML::Keyboard::F13;
        case NSF14FunctionKey:          return tinySFML::Keyboard::F14;
        case NSF15FunctionKey:          return tinySFML::Keyboard::F15;

        case NSPauseFunctionKey:        return tinySFML::Keyboard::Pause;

            // keycode 0x1b is not bound to any key.
            // This key is ' on CH-FR, ) on FR and - on US layouts.

            // An unknown key.
        default:                        return tinySFML::Keyboard::Unknown;
    }
}


} // namespace priv

} // namespace sf

