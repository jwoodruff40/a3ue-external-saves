/*
    Handles the initialization and tab switching on the setup dialog.
    This function should only be called from setupDialog onLoad and control activation EHs.

Environment: Scheduled for onLoad mode / Unscheduled for everything else unless specified

Arguments:
    <STRING> Mode, e.g. "onLoad", "switchTab"
    <ARRAY<ANY>> Array of params for the mode when applicable. Params for specific modes are documented in the modes.

Return Value:
    Nothing

*/

#include "\x\A3A\addons\gui\dialogues\ids.inc"
#include "\x\A3A\addons\gui\dialogues\defines.hpp"
#include "\x\A3A\addons\gui\dialogues\textures.inc"
#include "..\script_component.hpp"

params["_mode", "_params"];

Debug_1("Loadgame dialog called with mode %1",_mode);

// Get display
private _display = findDisplay A3A_IDD_SETUPDIALOG;

private _listboxCtrl = _display displayCtrl A3A_IDC_SETUP_SAVESLISTBOX;

switch (_mode) do
{
    case ("saveListClick"): // ! overridden for this extender to use the overridden selectSave case
    {
        if (_params#1 != 0) exitWith {};                                            // ignore non-LMB clicks
        private _mpos = ctrlMousePosition _listBoxCtrl;
        if (_mpos#0 > (ctrlPosition _listBoxCtrl # 2) - 2*GRID_W) exitWith {};      // ignore scroll-bar region
        private _rowIndex = floor (_mpos#1 / (4*GRID_H));
        if (_rowIndex >= count A3A_setup_saveData) exitWith {};                      // ignore clicks below saves
        if (_rowIndex == _listboxCtrl getVariable "rowIndex") exitWith {};          // ignore if already selected
        ["selectSave", [_rowIndex]] call a3ue_extsaves_gui_fnc_setupLoadgameTab;
        ["enableParamsTab"] call A3A_fnc_setupDialog;
    };

    case ("selectSave"): // ! overridden for this extender; see below
    {
        _params params ["_rowIndex"];
        Debug_1("SelectSave called with index %1",_rowIndex);

        private _selectBar = _display displayCtrl A3A_IDC_SETUP_GAMESELECTBOX;
        _selectBar ctrlShow (_rowIndex != -1);
        _selectBar ctrlSetPositionY _rowIndex*GRID_H*4;
        _selectBar ctrlCommit 0;

        _listBoxCtrl setVariable ["rowIndex", _rowIndex];
        uiNamespace setVariable ["A3U_saveIndex", _rowIndex]; // ! put this in uiNamespace because we may need it for the import / export dialog, which lives in a separate display context
        ["updateSaveInfoText"] call A3A_fnc_setupLoadgameTab;
        ["update"] call A3A_fnc_setupLoadgameTab;
    };

    case ("renameGame"): // ! overridden for this extender to clear the rename box after using it
    {
        private _index = _listboxCtrl getVariable ["rowIndex", -1];
        if (_index == -1) exitWith {};
        private _nameBoxCtrl = _display displayCtrl A3A_IDC_SETUP_NAMEEDITBOX;
        private _newName = ctrlText _nameBoxCtrl;

        // Set name in save data
        private _saveData = A3A_setup_saveData select _index;
        _saveData set ["name", _newName];

        // Set immediately on server too
        private _saveTarget = [_saveData get "serverID", _saveData get "gameID", _saveData get "map"];
        ["name", _newName, _saveTarget] remoteExecCall ["A3A_fnc_writebackSaveVar", 2];

        // Set name in the displayed table
        private _nameCtrl = _listboxCtrl getVariable "nameCtrls" select _index;
        _nameCtrl ctrlSetText _newName;

        // Clear the name edit box
        _nameBoxCtrl ctrlSetText "";
    };

    case ("importExportGame"): // ! added for this extender
    {
        createDialog "A3A_SetupImportExportDialog";
    };
};
