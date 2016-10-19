var itemComponent = null;
var draggedItem = null;
var startingMouse;
var posnInWindow;

function startDrag(mouse)
{
    posnInWindow = paletteItem.mapToItem(workspace.contentItem, 0, 0);
    startingMouse = { x: mouse.x, y: mouse.y }
    loadComponent();
}

//Creation is split into two functions due to an asynchronous wait while
//possible external files are loaded.

function loadComponent() {
    if (itemComponent != null) { // component has been previously loaded
        createItem();
        return;
    }

    itemComponent = Qt.createComponent(paletteItem.componentFile);
    if (itemComponent.status === Component.Loading)  //Depending on the content, it can be ready or error immediately
        component.statusChanged.connect(createItem);
    else
        createItem();
}

function createItem() {
    if (itemComponent.status === Component.Ready && draggedItem == null) {
        //creates an object instance of this component with the given parent and properties
        draggedItem = itemComponent.createObject(root, {"image": paletteItem.image, "x": posnInWindow.x, "y": posnInWindow.y, "z": 3});
    } else if (itemComponent.status === Component.Error) {
        draggedItem = null;
        console.log("error creating component");
        console.log(itemComponent.errorString());
    }
}

function continueDrag(mouse)
{
    if (draggedItem == null)
        return;

    draggedItem.x = mouse.x + posnInWindow.x - startingMouse.x;
    draggedItem.y = mouse.y + posnInWindow.y - startingMouse.y;
}

function endDrag(mouse)
{
    if (draggedItem == null)
        return;

    if (draggedItem.y < 0 || draggedItem.x < 0) { //Don't drop it in the toolbox
        draggedItem.destroy();
        draggedItem = null;
    } else {
        draggedItem.create();
        draggedItem = null;
    }
}

