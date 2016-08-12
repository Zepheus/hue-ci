# Hue-ci
Changes your light bulb color depending on the build status of your project. Built on top of Google FireBase, ESP8266 and Phillips Hue.
Currently, it only integrates with BitBucket Pipelines, but soon other CI platforms will follow.

## Software setup

1. Install [Arduino 1.6.10](https://www.arduino.cc/en/Main/Software)
1. Install [Arduino ESP8266 core](https://github.com/esp8266/Arduino#installing-with-boards-manager)
1. Download [FirebaseArduino library](https://github.com/googlesamples/firebase-arduino/archive/master.zip)
1. Start Arduino
1. Click `Sketch > Include Library > Add .ZIP Library...`
1. Choose `firebase-arduino-master.zip` downloaded in step `3.`

## FireBase Configuration

1. Create a new [FireBase](https://firebase.google.com/) project.
1. Create a new hierarchy `build-status > YOUR_REPO > success` with the value `true` or `false`.
1. Configure the access mentioned below.
1. Obtain a FireBase access key from the control panel.
```javascript
{
  "rules": {
    "build-status":
    {
      ".read": true,
      ".write": "auth != null"
    },
    ".read": "auth != null",
    ".write": "auth != null"
  }
}
```
## CI Configuration
Checkout following readme according to your platform:
- [BitBucket Pipelines](bitbucket/README.md)

## Client Configuration

1. Start Arduino
1. Open `hue-build-status.ino`
1. Replace `WIFI_SSID` and `WIFI_PASSWORD` with WiFi credentials
1. Replace `FIREBASE_HOST` and `FIREBASE_PATH` according to `YOUR_REPO` and project ID from your FireBase configuration
1. Replace `HUB_IP` and `LAMP_ID` according to your home Hue setup
1. Obtain a `USER_ID` from your Hue API panel. For more info checkout [Phillips developer docs](http://www.developers.meethue.com/documentation/getting-started).
1. Select the board `Board > ESP8266 Modules > NodeMCU 1.0`
1. Select the serial port  `Port > /dev/tty...`
1. Select the upload speed `Upload Speed > 115200`
1. Click `Sketch > Upload`