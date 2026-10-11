#include "..\script_component.hpp"
/* ----------------------------------------------------------------------------
Function: a3ue_extsaves_exportdata_pythia_fnc_onServerGameSaved

Description:
    CBA_EVENT_SERVER_GAME_SAVED event handler.

    Exports current game save data to JSON-formatted file on the server.

Parameters:
    0: useMPNamespace - whether to use the missionProfileNamespace (as opposed to legacy ProfileNamespace) <BOOL>
    1: serverID - the ID of the server that performed the save <BOOL> (false = profileNamespace save) OR <SCALAR> (missionProfileNamespace save)
    2: campaignID - the ID of the campaign that was active during the save <SCALAR>
    3: worldName - the name of the world where the save occurred <STRING>

Optional:

Returns:
    Nothing

Environment:
    Server, Unscheduled

Author:
    jwoodruff40/Creep'nCrunch
---------------------------------------------------------------------------- */
TRACE_1(QFUNC(onServerGameSaved),_this);

if !assert(params[
    ["_useMPNamespace", nil, [false]],
    ["_serverID", nil, [false, ""]],
    ["_campaignID", nil, [""]],
    ["_worldName", nil, [""]]
]) exitWith {};

private _namespace = [profileNamespace, missionProfileNamespace] select (_useMPNamespace);
private _saveDataKey = format ["A3A_saveData_%1", _campaignID];
private _saveDataHM = _namespace getVariable _saveDataKey;

if (isNil "_saveDataHM") exitWith {
    Info_1("Server attempted to export save data but it was not found: %1",_saveDataKey);
};

private _saveDataJson = ["HashmapToJson", [_saveDataHM]] call A3A_fnc_setupImportExportDialog;
["exportPythiaServer", [_campaignID, _saveDataJson]] remoteExec ["a3ue_extsaves_gui_fnc_setupImportExportDialog", 2];

nil;
