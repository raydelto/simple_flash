import bb.cascades 1.0

Page {
    property bool ligthOn: propertyManager.autoStart
    property bool intermitentOn: false
    // Add the application menu using a MenuDefinition
    Menu.definition: MenuDefinition {
        
        /*
        // Add a Help action
        helpAction: HelpActionItem {
            title: "Help"
            onTriggered: {
                console.log("HELP!");
            }
            
        }
        */
        // Add a Settings action
        settingsAction: SettingsActionItem {
            title: "Settings"
            onTriggered: {
                settingsSheet.open();
                console.log("Settings!");

            }
        }


    }

    onCreationCompleted: {
        console.log("Locking screen idle mode");
        Application.mainWindow.screenIdleMode = propertyManager.awake?1:0;
        console.log("end of Locking screen idle mode");        
    }
    Container {
        layout: DockLayout {
        }
        attachedObjects: [
            Sheet {
                id: settingsSheet
                content: SettingScreen {
                    actions: [
                        ActionItem {
                            title: "Exit"
                            onTriggered: {
                                settingsSheet.close();
                            }
                            ActionBar.placement: ActionBarPlacement.OnBar
                        }
                    ]
                }
            }
        ]

        ImageView {
            imageSource: "asset:///images/bg.png"

        }

        Container {
            layout: StackLayout {
            }
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
            Label {
                id: lblError
                text: qsTr("")
                textStyle.base: SystemDefaults.TextStyles.BigText
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.Red
                textStyle.fontSize: FontSize.Small
            }


            Label {
                text: qsTr("Simple Flash Light")
                textStyle.base: SystemDefaults.TextStyles.BigText
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                textStyle.fontWeight: FontWeight.Bold
                textStyle.color: Color.White
                textStyle.fontSize: FontSize.XXLarge
            }

            ImageButton {
                id: btnEncender
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center

                onClicked: {

                    console.log("btnEncenderclicked");
                    if (_backend.isIntermitent()) {
                        lblError.text = "Cannot turn on while intermitent is on";
                        console.log("Intermitent is ON, doing NOTHING");
                        return;
                    }
                    lblError.text = "";

                    if (ligthOn) {
                        btnEncender.defaultImageSource = "asset:///images/light_on.png";
                        console.log("Locking screen idle mode OFF");
                        //Application.mainWindow.screenIdleMode = 0;
                        console.log("end of Locking screen idle mode OFF");

                    } else {
                        btnEncender.defaultImageSource = "asset:///images/light_off.png";
                        console.log("Locking screen idle mode");
                        //Application.mainWindow.screenIdleMode = 1;
                        console.log("end of Locking screen idle mode");
                    }

                    _backend.lightFlash();
                    ligthOn = ! ligthOn;
                    console.log("After btnEncender cclicked");
                }
                defaultImageSource: propertyManager.autoStart?"asset:///images/light_off.png": "asset:///images/light_on.png";
                pressedImageSource:  "asset:///images/light_on.png";
                disabledImageSource: "asset:///images/light_on.png"

            }

            ImageButton {
                id: btnIntermitente
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center

                onClicked: {

                    console.log("intermitentFlash clicked");
                    if (ligthOn) {
                        console.log("Light is ON, doing NOTHING");
                        lblError.text = "Cannot turn on while light is on";
                        return;
                    }
                    lblError.text = "";

                    intermitentOn = ! intermitentOn;
                    if (intermitentOn) {
                        btnIntermitente.defaultImageSource = "asset:///images/light_off.png";
                    } else {
                        btnIntermitente.defaultImageSource = "asset:///images/intermitent_on.png";
                    }
                    _backend.intermitentFlash(true);

                    console.log("After intermitentFlash clicked");
                }
                defaultImageSource: "asset:///images/intermitent_on.png"
                pressedImageSource: "asset:///images/light_on.png"
                disabledImageSource: "asset:///images/light_off.png"

            }

        }
    }
}
