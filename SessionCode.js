function getItemNames(items) {
    var names = []
    items.forEach(function(item) {
        names.push(item.name)
    })
    return names
}

function treeToJson(items) {
    var synthTree = {};
    var synthItems = []
    synthTree.synthItems = synthItems

    items.forEach(function(item) {
        var json = item.toEssence()
        synthTree.synthItems.push(json)
    })
    return synthTree
}

// accepts json array of SynthItem descriptions
function jsonToTree(essences) {
    var newSynthItems = {}
    console.log("string that doesn't exist elsewhere")
    essences.forEach(function(essence) {
        var synthItem = createItem(essence["type"])
        synthItem.fromEssence(essence)
        newSynthItems[essence["name"]] = { "item" : synthItem, "parentNames" :essence["parentNames"] }
    })
    connectTree(newSynthItems)
}

// patch newly created items together
function connectTree(newSynthItems) {
    for (var childName in newSynthItems) {
        var parents = newSynthItems[childName]["parentNames"]
        if(parents) {
            for (var key in parents) {
                var parentName = parents[key]
                var parentSynthItem = newSynthItems[parentName]["item"]
                var childSynthItem = newSynthItems[childName]["item"]
                parentSynthItem.connectChild(childSynthItem)
            }
        }
    }
}

function createItem(type) {
    var componentFile
    switch(type) {
    case 0:
        componentFile = ""
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
    case 10:
        componentFile = "OUT.qml"
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
