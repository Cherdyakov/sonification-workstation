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
    var newItems = []
    essences.forEach(function(essence) {
        var synthItem = createItem(essence["type"])
        synthItem.fromEssence(essence)
        var newItem = { "name" : essence["name"], "parents": essence["parents"] }
        newItems.push(newItem)
    })
//    patchTree(newItems)
}

// patch newly created items together
function patchTree(newItems) {
    newItems.forEach(function(newItem) {
        var parents = newItem["parents"]
        parents.forEach(function(parent) {

        })

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
    })

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
