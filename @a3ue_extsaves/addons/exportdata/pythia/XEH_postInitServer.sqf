#include "script_component.hpp"

INFO("Hooking pythia handler into CBA game saved event");

[CBA_EVENT_SERVER_GAME_SAVED, LINKFUNC(onEventServerGameSaved)] call A3A_fnc_addEventHandler;

nil;
