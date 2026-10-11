/*
    Author:
        Creep'nCrunch / jwoodruff40
    
    Description:
        Handles the display and import / export functionality of saved game data.
        This function should only be called from setupImportExportDialog onLoad and control activation EHs.
    
    Params:
        _params <ARRAY> <Default: None>
    
    Dependencies:
        N/A
    
    Scope:
        Server for exportPythiaServer, exportInidbi2Server modes
        Client for all other modes
    
    Environment:
        Unscheduled for all modes unless otherwise specified
    
    Usage:
        ["clearData", []] call a3ue_extsaves_gui_fnc_setupImportExportDialog;
    
    Return:
        None
*/

#include "\x\A3A\addons\gui\dialogues\ids.inc"
#include "..\dialogues\ids.inc"
#include "\x\A3A\addons\gui\dialogues\defines.hpp"
#include "..\script_component.hpp"

params ["_mode", "_params"];

Debug_1("Setup Import/Export dialog called with mode %1",_mode);

private _display = findDisplay A3A_IDD_SETUP_IMPORTEXPORTDIALOG;
private _saveDataBox = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_SAVEDATABOX;

switch (_mode) do
{
    case ("onLoad"):
    {
        // ! instead of this, should be using CBA_EVENT_CLIENT_IMPORTEXPORT_DIALOG_OPENED / fn_onClientImportExportDialogOpened
    };

    case ("onUnload"):
    {
        // ! Stub in case we need to do any cleanup when the dialog is closed
        // we don't have an event fired for this, huh
    };

    case ("clearData"):
    {
        _saveDataBox ctrlSetText "";
        lbSetCurSel [A3A_IDC_SETUP_IMPORTEXPORT_SAVELB, -1];
        tvSetCurSel [A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_TREE, [-1]];
        ["fitText"] call A3A_fnc_setupImportExportDialog;
    };

    case ("selectDatastore"):
    {
        _params params [["_control", controlNull, [controlNull]]];

        // TODO: set ctrl active color

        private ["_show", "_hide"];
        switch (ctrlIDC _control) do {
            case (A3A_IDC_SETUP_IMPORTEXPORT_NAMESPACE_BUTTON): {
                _show = A3A_IDC_SETUP_IMPORTEXPORT_SAVELISTGROUP;
                _hide = [A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_SAVELISTGROUP, A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_SAVELISTGROUP]
            };
            case (A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_BUTTON): {
                ["pythiaTreePopulate", (_display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_TREE)] call a3ue_extsaves_gui_fnc_setupImportExportDialog;
                _show = A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_SAVELISTGROUP;
                _hide = [A3A_IDC_SETUP_IMPORTEXPORT_SAVELISTGROUP, A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_SAVELISTGROUP]
            };
            case (A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_BUTTON): {
                _show = A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_SAVELISTGROUP;
                _hide = [A3A_IDC_SETUP_IMPORTEXPORT_SAVELISTGROUP, A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_SAVELISTGROUP]
            };
        };
        { ctrlShow [_x, false] } forEach _hide;
        ctrlShow [_show, true];
    };

    case ("exportPythiaClient"):
    {
        _params params [["_control", controlNull, [controlNull]]];

        private _saveDataJson = ctrlText _saveDataBox;
        if (_saveDataJson isEqualTo "") exitWith {};
        
        private _saveDataHM = ["jsonToHashmap", [_saveDataJson]] call A3A_fnc_setupImportExportDialog; // py3u: private _saveDataDict = ["py3u.savedata.json_to_dict", [_saveDataJson]] call py3_fnc_callExtension;
        private _campaignID = _saveDataHM get "campaignID"; // py3u: private _campaignID = ["py3u.savedata.get_saved", [_saveDataDict, "campaignID"]] call py3_fnc_callExtension;
        if (isNil "_campaignID") exitWith {};

        ["exportPythiaServer", [_campaignID, _saveDataJson]] remoteExec ["a3ue_extsaves_gui_fnc_setupImportExportDialog", 2];
    };

    case ("exportPythiaServer"):
    {
        if (!isServer) exitWith { ["exportPythiaServer", _params] remoteExec ["a3ue_extsaves_gui_fnc_setupImportExportDialog", 2] };
        _params params [["_campaignID", nil, [""]], ["_saveDataJson", nil, [""]]];

        private _saveDataKey = format ["A3A_saveData_%1", _campaignID];
        private _exportSuccess = [_saveDataKey, _saveDataJson, "json"] call a3ue_extsaves_exportdata_pythia_fnc_exportData;
        if (_exportSuccess) then {
            Info_2("Server exported save data to file: %1.%2",_saveDataKey,"json");
            [LLSTRING(setup_ie_import_export), format [LLSTRING(setup_ie_hints_pythia_export_success), _saveDataKey, "json"]] call A3A_fnc_customHint;
        } else {
            Error_2("Server failed to export save data for %1.%2. Check logs for more information.",_saveDataKey,"json");
            [LLSTRING(setup_ie_import_export), LLSTRING(setup_ie_hints_pythia_export_failure)] call A3A_fnc_customHint;
        };
    };

    case ("exportInidbi2Client"):
    {
        // TODO: export save data to an inidbi2 database
        //private _inidbi2ExportBtn = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_EXPORTBUTTON;
    };

    case ("pythiaTreePopulate"):
    {
        _params params [["_control", controlNull, [controlNull]]];

        if (!isClass (configFile >> "CfgPatches" >> "PY3_Pythia")) exitWith {};

        // Clear and repopulate the file tree with available Pythia export files
        tvClear _control;

        private _basePath = "a3ue_extsaves/pythia";
        private _files = ["py3u.filesys.get_files", [_basePath, "^A3A_saveData_.*\.json$"]] call py3_fnc_callExtension;
        if (isNil "_files" || {!(_files isEqualType [])}) exitWith {};

        // Group by subfolder; files directly in the base folder use ""
        private _baseDepth = count (_basePath splitString "/\");
        private _byFolder = createHashMap;
        {
            private _relative = (_x splitString "/\") select [_baseDepth];
            private _folder = ["", _relative#0] select (count _relative > 1);
            (_byFolder getOrDefault [_folder, [], true]) pushBack _x;
        } forEach _files;

        {
            private _folder = _x;
            private _folderFiles = _byFolder getOrDefault [_folder, []];
            if (_folderFiles isEqualTo []) then { continue };
            _folderFiles sort false;                    // timestamped names, newest first

            private _parentPath = [];
            if (_folder != "") then {
                _parentPath = [_control tvAdd [[], _folder]];
            };
            {
                private _tooltip = (_x splitString "/\") select -1;
                private _saveDataJson = ["py3u.filesys.read_data", [_x]] call py3_fnc_callExtension;
                if (_saveDataJson isEqualTo "") then {
                    Error_1("File could not be read or returned empty data: %1",_x);
                    continue
                };
                private _saveDataHM = ["jsonToHashmap", [_saveDataJson]] call A3A_fnc_setupImportExportDialog;
                private _name = _saveDataHM getOrDefault ["name", _tooltip];
                private _formattedName = if (_folder isEqualTo "") then { _name } else {
                    format ["%1 [%2]", _name, (_x splitString "_.") select -2];
                };
                
                private _itemPath = _control tvAdd [_parentPath, _formattedName];
                _control tvSetData [_parentPath + [_itemPath], _saveDataJson];
                _control tvSetTooltip [_parentPath + [_itemPath], _tooltip];
            } forEach _folderFiles;
        } forEach ["", "daily", "weekly", "monthly", "yearly"];

        tvExpandAll _control;
    };

    case ("pythiaTreeSelChanged"):
    {
        _params params ["_control", "_selectionPath"];

        private _saveDataJson = _control tvData _selectionPath;
        _saveDataBox ctrlSetText _saveDataJson;
        ["fitText"] call A3A_fnc_setupImportExportDialog;
        (_display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_SAVEDATAGROUP) ctrlSetScrollValues [0, -1];
    };
};
