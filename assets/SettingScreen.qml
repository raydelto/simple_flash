import bb.cascades 1.0

Page {
    Container {
        layout: StackLayout {
            
        }

        DropDown {
            id: ddIntermittent
            title: "Intermitent period"
            // text + description
            Option {
                text: "100 ms"
                description: "100 milliseconds"
                value: "0"
            }

            Option {
                text: "250 ms"
                description: "250 milliseconds"
                value: "1"
            }
            Option {
                text: "500 ms"
                description: "500 milliseconds"
                value: "2"
            }
            Option {
                text: "750 ms"
                description: "750 milliseconds"
                value: "3"
            }
            Option {
                text: "1000 ms"
                description: "1000 milliseconds (1 second)"
                value: "4"
            }


            selectedIndex: propertyManager.intermittentPeriod

            onSelectedIndexChanged: {
                console.log("Value changed from CASCADES");
                propertyManager.intermittentPeriod = ddIntermittent.selectedValue;
            }

        }

        Divider {

        }
        CheckBox {
            id: chkAutoOn
            text: "Autostart Flashlight"
            onCheckedChanged: {
                console.log("Autostart Value changed from CASCADES");
                propertyManager.autoStart = chkAutoOn.checked;

            }
            checked: propertyManager.autoStart
        }

        Divider {

        }
        CheckBox {
            id: chkAwake
            text: "Keep device awake"
            onCheckedChanged: {
                console.log(" awake Value changed from CASCADES");
                if(chkAwake.checked){
                    Application.mainWindow.screenIdleMode = 1;
                }else{
                    Application.mainWindow.screenIdleMode = 0;
                }
                propertyManager.awake = chkAwake.checked;

            }
            checked: propertyManager.awake
        }

    }

}
