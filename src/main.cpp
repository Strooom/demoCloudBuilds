#include <Arduino.h>
#include "version.h"
#include "buildinfo.h"

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println(version::getIsVersionAsString());
    Serial.print("Built on ");
    Serial.println(buildInfo::buildTimeStamp);
    Serial.print("\n\n");
    delay(3000);
}
