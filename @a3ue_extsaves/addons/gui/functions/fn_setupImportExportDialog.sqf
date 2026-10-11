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
        Server for registerSaveData, getSavesFromServer modes
        Client for all other modes
    
    Environment:
        Scheduled for onLoad and xxxLBSelChanged modes
        Unscheduled for all other modes unless specified
    
    Usage:
        ["importPythia", []] call a3ue_extsaves_gui_fnc_setupImportExportDialog;
    
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
private _saveDataBoxGroup = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_SAVEDATAGROUP;
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

        diag_log format ["Select datastore control: %1", _control];

        // TODO: set ctrl active color

        private ["_show", "_hide"];
        switch (ctrlIDC _control) do {
            case (A3A_IDC_SETUP_IMPORTEXPORT_NAMESPACE_BUTTON): {
                _show = A3A_IDC_SETUP_IMPORTEXPORT_SAVELISTGROUP;
                _hide = [A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_SAVELISTGROUP, A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_SAVELISTGROUP]
            };
            case (A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_BUTTON): {
                _show = A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_SAVELISTGROUP;
                _hide = [A3A_IDC_SETUP_IMPORTEXPORT_SAVELISTGROUP, A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_SAVELISTGROUP]
            };
            case (A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_BUTTON): {
                _show = A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_SAVELISTGROUP;
                _hide = [A3A_IDC_SETUP_IMPORTEXPORT_SAVELISTGROUP, A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_SAVELISTGROUP]
            };
        };
        diag_log format ["Hide controls: %1", _hide];
        { ctrlShow [_x, false] } forEach _hide;
        diag_log format ["Show control: %1", _show];
        ctrlShow [_show, true];
    };

    case ("exportPythia"):
    {
        // TODO: export save data to a JSON file via Pythia
        //private _pythiaExportBtn = _display displayCtrl A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_EXPORTBUTTON;
    };

    case ("exportInidbi2"):
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

        private _basePath = "a3u_exports/pythia";
        private _files = ["py3u.filesys.get_files", [_basePath, "^savedata.*\.json$"]] call py3_fnc_callExtension;
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
                private _name = (_x splitString "/\") select -1;
                private _itemPath = _control tvAdd [_parentPath, _name];
                _control tvSetData [_parentPath + [_itemPath], _x];
            } forEach _folderFiles;
        } forEach ["", "daily", "weekly", "monthly", "yearly"];

        tvExpandAll _control;
    };

    case ("pythiaTreeSelChanged"):
    {
        _params params ["_control", "_selectionPath"];

        private _filePath = _control tvData _selectionPath;
        private _saveDataJson = ["py3u.filesys.read_data", [_filePath]] call py3_fnc_callExtension;
        if (_saveDataJson isEqualTo "") exitWith {
            Error_1("File could not be read or returned empty data: %1",_filePath);
        };

        _saveDataBox ctrlSetText _saveDataJson;
        ["fitText"] call A3A_fnc_setupImportExportDialog;
        _saveDataBoxGroup ctrlSetScrollValues [0, -1];
    };
};

// Commented just for an example on the LLSTRING MACRO
// [LLSTRING(setup_import_export), LLSTRING(setup_ie_import_success)] call A3A_fnc_customHint;
