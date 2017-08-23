// create unique id for all SynthItems
// needed before reading tree to save session
function setIdentifiers(items) {
    for(var i = 0; i < items.length; i++) {
        var item = items[i]
        item.identifier = i
    }
}

function readTree(items) {
    setIdentifiers(items)
    var synthTree = {};
    var synthItems = []
    synthTree.synthItems = synthItems

    for (var i = 0; i < items.length; i++) {
        var item = items[i]
        var jsonItem = item.read()
        synthTree.synthItems.push(jsonItem)
    }
    return synthTree
}

// accepts json array of SynthItem descriptions
function createTree(arr) {
        for (var i = 0; i < arr.length; i++) {
        var essence = arr[i]
        var synthItem = createItem(essence["type"])
        if(synthItem !== null) {
            synthItem.init(essence)
        }
    }
}

// clear the existing tree
function destroyItems(items) {
    while (items.length > 0) {
        var item = items.pop()
        item.deleteThis()
    }
}

function createItem(type) {
    switch(type) {
    case 1:
        var componentFile = "OSC.qml"
        break;
    default:
        return null
    }
    var component = Qt.createComponent(componentFile);
    if(component.status === Component.Ready) {
        var item = component.createObject(root)
    }
    return item
}

function indexesToString(arr) {
    var stringArr = ""
    for(var i = 0; i < arr.length; i++) {
        arr[i] = arr[i] + 1
        stringArr += String(arr[i]) + ","
    }
    return stringArr
}
