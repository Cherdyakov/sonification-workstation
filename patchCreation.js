var component;
var patch;

function createPatch() {
    component = Qt.createComponent("Patch.qml");
    patch = component.createObject(canvas, {"x": workspaceMouseArea.mouseX,
                                       "y": workspaceMouseArea.mouseY});

    if( patch === null) {
        console.log("Error creating patch");
    }

//    console.log("patch created in js: " + patch)
    return patch;
}
