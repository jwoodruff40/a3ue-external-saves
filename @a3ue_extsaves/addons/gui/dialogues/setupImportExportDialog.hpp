#include "ids.inc"
#include "\x\A3A\addons\gui\dialogues\ids.inc"
#include "\x\A3A\addons\gui\dialogues\defines.hpp"
#include "\x\A3A\addons\core\ui_define.hpp"

class A3A_ControlsGroupNoScrollbars;
class A3A_Button;
class A3A_Text;
class A3A_Tree;

class A3A_SetupImportExportDialog
{
    #define DIALOG_X CENTER_X(160)
    #define DIALOG_Y CENTER_Y(92)

    class Controls
    {
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
