#include "ids.inc"
#include "\x\A3A\addons\gui\dialogues\ids.inc"
#include "\x\A3A\addons\gui\dialogues\defines.hpp"
#include "\x\A3A\addons\core\ui_define.hpp"

class A3A_Text;
class A3A_Edit;
class A3A_Button;
class A3A_Background;
class A3A_ControlsGroupNoScrollbars;
class A3A_ControlsGroup;
class A3A_DefaultControlsGroup;
class A3A_SectionLabelRight;
class A3A_TabbedDialog;

class A3A_SetupDialog : A3A_TabbedDialog {
    class Controls {
        class LoadgameTab : A3A_DefaultControlsGroup {
            class Controls {
                class SavedGamesLabel : A3A_SectionLabelRight {
                    font = A3A_BUTTON_FONT;
                };
                class SavedGamesBackground : A3A_Background {
                    h = 88 * GRID_H;
                };
                class SavedGamesTable : A3A_ControlsGroup {
                    onMouseButtonUp = "['saveListClick', _this] call a3ue_extsaves_gui_fnc_setupLoadgameTab";
                    h = 84 * GRID_H;
                };

                delete SaveNameLabel;
                delete SaveNameEditBox;
                delete DeleteButton;
                delete RenameButton;

                class GameEditOptions : A3A_ControlsGroupNoScrollbars {
                    x = 126 * GRID_W;
                    y = 70 * GRID_H;
                    w = 30 * GRID_W;
                    h = 26 * GRID_H;

                    class Controls {
                        class SaveNameLabel: A3A_Text {
                            idc = -1;
                            text = $STR_antistasi_dialogs_setup_new_save_name;
                            style = ST_CENTER;
                            font = A3A_BUTTON_FONT;
                            colorBackground[] = {0,0,0,1};
                            x = 0 * GRID_W;
                            y = 0 * GRID_H;
                            w = 30 * GRID_W;
                            h = 4 * GRID_H;
                        };
                        class SaveNameEditBox: A3A_Edit {
                            idc = A3A_IDC_SETUP_NAMEEDITBOX;
                            x = 0 * GRID_W;
                            y = 4 * GRID_H;
                            w = 30 * GRID_W;
                            h = 4 * GRID_H;
                        };
                        class DeleteButton: A3A_Button {
                            idc = A3A_IDC_SETUP_DELETEBUTTON;
                            text = $STR_antistasi_dialogs_setup_delete_game;
                            onButtonClick = "['deleteGame'] call A3A_fnc_setupLoadgameTab";
                            x = 0 * GRID_W;
                            y = 10 * GRID_H;
                            w = 30 * GRID_W;
                            h = 4 * GRID_H;
                        };
                        class RenameButton: DeleteButton {
                            idc = A3A_IDC_SETUP_RENAMEBUTTON;
                            text = $STR_antistasi_dialogs_setup_rename_game;
                            onButtonClick = "['renameGame'] call a3ue_extsaves_gui_fnc_setupLoadgameTab";
                            y = 16 * GRID_H;
                        };
                        class ImportExportButton: DeleteButton {
                            idc = A3A_IDC_SETUP_IMPORTEXPORTBUTTON;
                            text = CSTRING(setup_import_export);
                            onButtonClick = "['importExportGame'] call a3ue_extsaves_gui_fnc_setupLoadgameTab";
                            y = 22 * GRID_H;
                        };
                    };
                };
            };
        };
    };
};

#include "setupImportExportDialog.hpp"
