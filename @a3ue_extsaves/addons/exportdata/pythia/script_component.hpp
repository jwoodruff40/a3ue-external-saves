#define SUBCOMPONENT pythia
#include "..\script_component.hpp"

#ifndef SUBADDON
    #define SUBADDON QUOTE(DOUBLES(COMPONENT,SUBCOMPONENT))
#endif // SUBADDON
#ifndef QSUBADDON
    #define QSUBADDON QUOTE(SUBADDON)
#endif // QSUBADDON
