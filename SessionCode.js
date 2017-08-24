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
    var itemDict = {}
    for (var i = 0; i < arr.length; i++) {
        var essence = arr[i]
        var id = essence["identifier"]
        var synthItem = createItem(essence["type"])
        if(synthItem !== null) {
            synthItem.init(essence)
            var obj = {}
            obj["parents"] = essence["parents"]
            obj["synthItem"] = synthItem
            itemDict[id] = obj
        }
    }
    connectTree(itemDict)
}

// patch newly created items together
function connectTree(itemDict) {
    for(var key in itemDict) {
        if (itemDict.hasOwnProperty(key)) {
            var obj = itemDict[key];
            var item = obj["synthItem"]
            var parents = obj["parents"]
            for(var parent in parents) {
                var pID = parents[parent]
                var pObj = itemDict[pID]
                var pItem = pObj["synthItem"]
                pItem.addChild(item)
            }
        }

    }
}

// clear the existing tree
function destroyItems(items) {
    while (items.length > 0) {
        console.log("items.length: " + items.length)
        var item = items.pop()
        item.deleteThis()
    }
}

function createItem(type) {
    var componentFile
    switch(type) {
    case 0:
        componentFile = "OUT.qml"
        break
    case 1:
        componentFile = "OSC.qml"
        break
    case 2:
        componentFile = "AUD.qml"
        break
    case 3:
        componentFile = "MOD.qml"
        break
    case 4:
        componentFile = "PAN.qml"
        break
    case 5:
        componentFile = "ENV.qml"
        break
    case 6:
        componentFile = "VOL.qml"
        break
    case 7:
        componentFile = "NSE.qml"
        break
    case 8:
        componentFile = "EQ.qml"
        break
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
