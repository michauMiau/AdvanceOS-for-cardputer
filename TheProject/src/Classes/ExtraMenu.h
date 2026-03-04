#pragma once
#include "./GlobalParentClass.h"
#include <M5Cardputer.h>
class Extra : public GlobalParentClass
{
private:
    /* data */
public:
   // M5Canvas sprite;
    std::vector<String>* SlectedString;

    Extra(MyOS *os) : GlobalParentClass(os){}
        

    ~Extra(){}

   // std::vector<String> menuItems= {"Brightness", "RESET FONT (if select from file manager)","test1","test2"};
        std::vector<String> menuItems= {
            "Theme Manager",
            #if defined(COMPILE_WIFI_THINGS)
             /* "WIFI",  */
            #endif
            #if defined(COMPILE_EMULATOR)
            "emulator",
            #endif
            #if defined(COMPILE_WIFI_THINGS)
            "Esp Projects Remote Control",
            #endif
            "Painter",
            "Step's Counter",
            /* "ESPnow Chat", */
            "Color Picker",
            "Timer",
            "Calculator",
            "GPIO Control",
            "MIC Record to SD Card",
            "Partition Viewer",
            "Wifi Spectrum",
            
        };

    // std::vector<String> Brightness= {"Brightness100%","Brightness90%","Brightness70%", "Brightness50%","Brightness40%","Brightness10%"};
     //   std::vector<String> DimTimer= {"Turn Off In 100 Second","Turn Off In 50 Second","Turn Off In 30 Second","Turn Off In 20 Second","Turn Off In 10 Second"};

   // String menuItems[4] = {"Brightness", "RESET FONT (if select from file manager)"};
    //int menuCount = 2;
    int MenuIdFocus=0;
    float cameraY = 0;
    float targetCameraY= 0;
        int DistanceBetweenTXT = 25;

    void Begin() override;

    void Loop() override;
        void Draw() override;
};


