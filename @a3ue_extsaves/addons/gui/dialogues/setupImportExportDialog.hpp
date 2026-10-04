#include "ids.inc"

class A3A_SetupImportExportDialog
{
    idd = A3A_IDD_SETUP_IMPORTEXPORTDIALOG;
    onLoad = "['onLoad'] spawn a3ue_extsaves_gui_fnc_setupImportExportDialog";
    onUnload = "['onUnload'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";

    #define DIALOG_X CENTER_X(120) // Global x pos of dialog
    #define DIALOG_Y CENTER_Y(92) // Global y pos of dialog

    class Controls
    {
        class Titlebar : A3A_Text {
            idc = -1;
            moving = true;
            colorBackground[] = A3A_COLOR_TITLEBAR_BACKGROUND;
            text = CSTRING(setup_import_export);
            style = ST_CENTER + ST_UPPER;
            font = A3A_BUTTON_FONT;
            x = DIALOG_X;
            y = DIALOG_Y;
            w = 160 * GRID_W;
            h = 4 * GRID_H;
        };
        class CloseButton : A3A_Button {
            idc = -1;
            text = CSTRING(setup_ie_close);
            onButtonClick = "closeDialog 0";
            x = DIALOG_X + 140 * GRID_W;
            y = DIALOG_Y;
            w = 18 * GRID_W;
            h = 4 * GRID_H;
        };
        class Background : A3A_Background {
            idc = -1;
            x = DIALOG_X;
            y = DIALOG_Y + 4 * GRID_H;
            w = 160 * GRID_W;
            h = 88 * GRID_H;
        };

        class SaveDataBoxGroup : A3A_ControlsGroupNoScrollbars {
            x = DIALOG_X;
            y = DIALOG_Y + 6 * GRID_H;
            w = 80 * GRID_W;
            h = 86 * GRID_H;

            class Controls {
                class SaveDataTitle : A3A_Text {
                    idc = -1;
                    text = CSTRING(setup_ie_savedata);
                    colorBackground[] = A3A_COLOR_BLACK;
                    style = ST_CENTER + ST_UPPERCASE;
                    font = A3A_BUTTON_FONT;
                    x = 0;
                    y = 0;
                    w = 60 * GRID_W;
                    h = 4 * GRID_H;
                };
                class EditButton : A3A_Button {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_EDITBUTTON;
                    text = CSTRING(setup_ie_edit);
                    onButtonClick = "['toggleEdit'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    x = 60 * GRID_W;
                    y = 0;
                    w = 10 * GRID_W;
                    h = 4 * GRID_H;
                };
                class ClearButton : EditButton {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_CLEARBUTTON;
                    text = CSTRING(setup_ie_clear);
                    onButtonClick = "['clearData'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    x = 70 * GRID_W;
                };
                class SaveDataBox : A3A_Edit {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_SAVEDATABOX;
                    style = ST_LEFT + ST_MULTI;
                    colorDisabled[] = A3A_COLOR_TEXT;
                    x = 0;
                    y = 4 * GRID_H;
                    w = 80 * GRID_W;
                    h = 82 * GRID_H;
                };
            };
        };
        
        class BasicImportExportGroup : A3A_ControlsGroupNoScrollbars {
            x = DIALOG_X + 82 * GRID_W;
            y = DIALOG_Y + 10 * GRID_H;
            w = 28 * GRID_W;
            h = 12 * GRID_H;

            class Controls {
                class ImportButton : A3A_Button {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_IMPORTBUTTON;
                    text = CSTRING(setup_ie_import);
                    tooltip = CSTRING(setup_ie_import_tooltip);
                    onButtonClick = "['importData'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    x = 0;
                    y = 0;
                    w = 28 * GRID_W;
                    h = 5 * GRID_H;
                };
                class ExportButton : ImportButton {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_EXPORTBUTTON;
                    text = CSTRING(setup_ie_export);
                    tooltip = CSTRING(setup_ie_export_tooltip);
                    onButtonClick = "['exportData'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    y = 7 * GRID_H;
                };
            };
        };

        class PythiaImportExportGroup : A3A_ControlsGroupNoScrollbars {
            x = DIALOG_X + 82 * GRID_W;
            y = DIALOG_Y + 26 * GRID_H;
            w = 28 * GRID_W;
            h = 12 * GRID_H;

            class Controls {
                class PythiaImportButton : A3A_Button {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_IMPORTBUTTON;
                    text = CSTRING(setup_ie_pythia_import);
                    tooltip = CSTRING(setup_ie_pythia_import_tooltip);
                    onButtonClick = "['importPythia'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    x = 0;
                    y = 0;
                    w = 28 * GRID_W;
                    h = 5 * GRID_H;
                };
                class PythiaExportButton : PythiaImportButton {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_PYTHIA_EXPORTBUTTON;
                    text = CSTRING(setup_ie_pythia_export);
                    tooltip = CSTRING(setup_ie_pythia_export_tooltip);
                    onButtonClick = "['exportPythia'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    y = 7 * GRID_H;
                };
            };
        };

        class Inidbi2ImportExportGroup : A3A_ControlsGroupNoScrollbars {
            x = DIALOG_X + 82 * GRID_W;
            y = DIALOG_Y + 42 * GRID_H;
            w = 28 * GRID_W;
            h = 12 * GRID_H;

            class Controls {
                class Inidbi2ImportButton : A3A_Button {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_IMPORTBUTTON;
                    text = CSTRING(setup_ie_inidbi2_import);
                    tooltip = CSTRING(setup_ie_inidbi2_import_tooltip);
                    onButtonClick = "['importInidbi2'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    x = 0;
                    y = 0;
                    w = 28 * GRID_W;
                    h = 5 * GRID_H;
                };
                class Inidbi2ExportButton : Inidbi2ImportButton {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_INIDBI2_EXPORTBUTTON;
                    text = CSTRING(setup_ie_inidbi2_export);
                    tooltip = CSTRING(setup_ie_inidbi2_export_tooltip);
                    onButtonClick = "['exportInidbi2'] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                    y = 7 * GRID_H;
                };
            };
        };

        class FileSystemGroup : A3A_ControlsGroupNoScrollbars {
            x = DIALOG_X + 110 * GRID_W;
            y = DIALOG_Y + 2 * GRID_H;
            w = 50 * GRID_W;
            h = 92 * GRID_H;

            class Controls {
                class FileSystemText : A3A_Text {
                    idc = -1;
                    text = CSTRING(setup_ie_filesystem_text);
                    colorBackground[] = A3A_COLOR_BLACK;
                    style = ST_CENTER + ST_UPPERCASE;
                    font = A3A_BUTTON_FONT;
                    x = 2 * GRID_W;
                    y = 4 * GRID_H;
                    w = 46 * GRID_W;
                    h = 4 * GRID_H;
                };
                class FileSystemTree : A3A_Tree {
                    idc = A3A_IDC_SETUP_IMPORTEXPORT_FILETREE;
                    x = 2 * GRID_W;
                    y = 8 * GRID_H;
                    w = 46 * GRID_W;
                    h = 82 * GRID_H;
                    onTreeSelChanged = "['treeSelChanged', _this] call a3ue_extsaves_gui_fnc_setupImportExportDialog";
                };
            };
        };
    };
};
