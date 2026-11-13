// COMPONENT should be defined in the script_component.hpp and included BEFORE this hpp

#define MAINPREFIX z
#define PREFIX a3ue_extsaves

#include "script_version.hpp"

#define VERSION MAJOR.MINOR
#define VERSION_AR MAJOR,MINOR,PATCHLVL,BUILD

#define A3UE_EXTSAVES_TAG A3UE_EXTSAVES

// MINIMAL Arma version required version for the Mod. Components can specify others..
#define REQUIRED_VERSION 2.22

#ifdef COMPONENT_BEAUTIFIED
    #define COMPONENT_NAME QUOTE(a3ue_extsaves - COMPONENT_BEAUTIFIED)
#else
    #define COMPONENT_NAME QUOTE(a3ue_extsaves - COMPONENT)
#endif
