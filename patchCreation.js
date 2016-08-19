var component;
var patch;

function createPatch() {
    component = Qt.createComponent("Connection.qml");
    if (component.status === Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation() {
    if (component.status === Component.Ready) {
        patch = component.createObject(workspace, {"x": 100, "y": 100});
        patchManager.patches.push(patch)
        if (patch === null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status === Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
