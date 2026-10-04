#include "script_component.hpp"

INFO("Hooking pythia handler into CBA game saved event");

//[CBA_EVENT_SERVER_GAME_SAVED, LINKFUNC(onServerGameSaved)] call A3A_fnc_addEventHandler; // ! not sure why LINKFUNC doesn't evaluate properly
[CBA_EVENT_SERVER_GAME_SAVED, { call FUNC(onServerGameSaved) }] call A3A_fnc_addEventHandler;

nil;
