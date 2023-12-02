#include <Arduino.h>
#include "version.h"
#include "buildinfo.h"

void setup() {
    Serial.begin(115200);
}

void loop() {
    version::setIsVersion();
    Serial.print("Version ");
    Serial.println(version::getIsVersionAsString());
    Serial.print(toString(buildInfo::theBuildEnvironment));
    Serial.print(" ");
    Serial.print(toString(buildInfo::theBuildType));
    Serial.print(" build, ");
    Serial.println(buildInfo::buildTimeStamp);
    Serial.print("\n\n");
    delay(3000);
}
