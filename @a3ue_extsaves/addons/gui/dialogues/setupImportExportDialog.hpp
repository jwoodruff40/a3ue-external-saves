#include "ids.inc"
#include "\x\A3A\addons\gui\dialogues\ids.inc"
#include "\x\A3A\addons\gui\dialogues\defines.hpp"
#include "\x\A3A\addons\core\ui_define.hpp"

class A3A_ControlsGroupNoScrollbars;
class A3A_Background;
class A3A_Button;
class A3A_Text;
class A3A_ListBox;
class A3A_Tree;

class A3A_SetupImportExportDialog
{
    #define DIALOG_X CENTER_X(160)
    #define DIALOG_Y CENTER_Y(92)

    class Controls
    {
        class EditButton;
        class ClearButton : EditButton {
            onButtonClick = "[""clearData""] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
        };

        class ExtendedImportGroup : A3A_ControlsGroupNoScrollbars {
            x = DIALOG_X + 82 * GRID_W;
            y = DIALOG_Y + 26 * GRID_H;
            w = 28 * GRID_W;
            h = 22 * GRID_H;

            class Controls {
                class ExtendedImportBackground : A3A_Background {
                    idc = -1;
                    x = 0;
                    y = 0;
                    w = 28 * GRID_W;
                    h = 22 * GRID_H;
                };
                class ExtendedImportTitle : A3A_Text {
                    idc = -1;
                    text = CSTRING(setup_ie_datastore_text);
                    tooltip = CSTRING(setup_ie_datastore_tooltip);
                    colorBackground[] = A3A_COLOR_BLACK;
                    style = ST_CENTER + ST_UPPERCASE;
                    font = A3A_BUTTON_FONT;
                    x = 0;
                    y = 0;
                    w = 28 * GRID_W;
                    h = 5 * GRID_H;
                };
                class NamespaceButton : A3A_Button {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_NAMESPACE_BUTTON;
                    text = CSTRING(setup_ie_datastore_namespace_text);
                    tooltip = CSTRING(setup_ie_datastore_namespace_tooltip);
                    onButtonClick = "[""selectDatastore"", _this] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    x = 0;
                    y = 7 * GRID_H;
                    w = 28 * GRID_W;
                    h = 5 * GRID_H;
                };
                class PythiaButton : NamespaceButton {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_BUTTON;
                    text = CSTRING(setup_ie_datastore_pythia_text);
                    tooltip = CSTRING(setup_ie_datastore_pythia_tooltip);
                    onLoad = "(_this select 0) ctrlEnable isClass (configFile >> ""CfgPatches"" >> ""PY3_Pythia"")";
                    y = 12 * GRID_H;
                };
                class Inidbi2Button : PythiaButton {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_BUTTON;
                    text = CSTRING(setup_ie_datastore_inidbi2_text);
                    tooltip = CSTRING(setup_ie_datastore_inidbi2_tooltip);
                    onLoad = "(_this select 0) ctrlEnable isClass (configFile >> ""CfgPatches"" >> ""inidbi2"")";
                    y = 17 * GRID_H;
                };
            };
        };

        class ExtendedExportGroup : ExtendedImportGroup {
            y = DIALOG_Y + 52 * GRID_H;
            h = 17 * GRID_H;

            class Controls : Controls {
                class ExtendedExportBackground : ExtendedImportBackground {
                    h = 17 * GRID_H;
                };
                class ExtendedExportTitle : ExtendedImportTitle {
                    text = CSTRING(setup_ie_ext_export_title);
                    tooltip = CSTRING(setup_ie_ext_export_tooltip);
                };
                delete NamespaceButton;
                class PythiaExportButton : PythiaButton {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_EXPORTBUTTON;
                    text = CSTRING(setup_ie_ext_export_pythia_text);
                    tooltip = CSTRING(setup_ie_ext_export_pythia_tooltip);
                    onButtonClick = "[""exportPythiaClient"", _this] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    y = 7 * GRID_H;
                };
                class Inidbi2ExportButton : Inidbi2Button {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_EXPORTBUTTON;
                    text = CSTRING(setup_ie_ext_export_inidbi2_text);
                    tooltip = CSTRING(setup_ie_ext_export_inidbi2_tooltip);
                    onButtonClick = "[""exportInidbi2Client"", _this] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    y = 12 * GRID_H;
                };
            };
        };

        class SaveListGroup : A3A_ControlsGroupNoScrollbars {
            idc = A3A_IDC_SETUP_IMPORTEXPORT_SAVELISTGROUP;
            class Controls {
                class SaveListText : A3A_Text {
                    text = CSTRING(setup_ie_namespace_savelist_text);
                    tooltip = CSTRING(setup_ie_namespace_savelist_tooltip);
                };
            };
        };

        class PythiaSavesGroup : SaveListGroup {
            idc = A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_SAVELISTGROUP;
            show = 0;
            class Controls : Controls {
                class PythiaSavesText : SaveListText {
                    text = CSTRING(setup_ie_pythia_savelist_text);
                    tooltip = CSTRING(setup_ie_pythia_savelist_tooltip);
                };
                delete SaveListBox;
                class PythiaSavesTree : A3A_Tree {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_TREE;
                    x = 2 * GRID_W;
                    y = 8 * GRID_H;
                    w = 46 * GRID_W;
                    h = 80 * GRID_H;
                    onLoad = "[""pythiaTreePopulate"", [_this select 0]] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    onTreeSelChanged = "[""pythiaTreeSelChanged"", _this] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                };
            };
        };

        class Inidbi2SavesGroup : SaveListGroup {
            idc = A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_SAVELISTGROUP;
            show = 0;
            class Controls : Controls {
                class Inidbi2SavesText : SaveListText {
                    text = CSTRING(setup_ie_inidbi2_savelist_text);
                    tooltip = CSTRING(setup_ie_inidbi2_savelist_tooltip);
                };
                class SaveListBox;
                class Inidbi2SaveListBox : SaveListBox {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_SAVELB;
                    onLoad = "";
                    onLBSelChanged = "";
                };
            };
        };
    };
};
